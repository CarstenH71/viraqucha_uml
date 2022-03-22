//---------------------------------------------------------------------------------------------------------------------
// UmlProject.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlProject.
// Compiles with: MSVC 15.2 (2017) or newer, GNU GCC 5.1 or newer
//
// *******************************************************************************************************************
// *                                                                                                                 *
// * This file is part of ViraquchaUML.                                                                              *
// *                                                                                                                 *
// * ViraquchaUML is free software; you can redistribute it and/or modify it under the terms of the GNU General      *
// * Public License as published by the Free Software Foundation; either version 3.0 of the License, or (at your     *
// * option) any later version.                                                                                      *
// *                                                                                                                 *
// * ViraquchaUML is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the      *
// * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License     *
// * for more details.                                                                                               *
// *                                                                                                                 *
// * You should have received a copy of the GNU General Public License along with ViraquchaUML; if not, see          *
// * http://www.gnu.org/licenses/gpl                                                                                 *
// *                                                                                                                 *
// *******************************************************************************************************************
//
// See https://github.com/CarstenH71/viraqucha_uml for the latest version of this software.
//---------------------------------------------------------------------------------------------------------------------
#include "UmlProject.h"
#include "UmlCompositeElement.h"
#include "UmlElementFactory.h"
#include "UmlLink.h"
#include "UmlRoot.h"
#include "ErrorTools.h"
#include "INamedElement.h"
#include "PropertyStrings.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHash>
#include <QHashIterator>
#include <QSaveFile>

/**
 * @class UmlProject
 * @brief The UmlProject class is the entry point of the ViraquchaUML database.
 * @since 0.1.0
 * @ingroup UmlCommon
 *
 * The class UmlProject implements the project management of the data model. All memory objects (objects of class 
 * UmlElement) of the data model must be registered in an object of this class in order to be serialized. UmlProject 
 * uses the unique identifiers of the UmlElement objects to identify the objects both in memory and in mass storage.
 *
 * UmlProject writes and reads the files of the memory objects into a folder with the following structure:
 *
 * A JSON file with the extension UPRJ (UML Project) contains an array of UmlElement objects that are assigned (known) 
 * to the project. The array contains the class name and the identifier of each object. This enables the reconstruction 
 * of the objects from class information. The UPRJ file also contains the name of the author(s) and a comment.
 * 
 * In addition to the UPRJ file, the class UmlProject expects the following subdirectories in which further project 
 * data is stored:
 * - /artifacts: Contains artifacts, i.e. files that are associated with the project but are created or edited by other 
 *   programs. This includes, e.g., PDF documents with requirement specifications, image files from GUI prototypes, or
 *   other database files.
 * - /code: Contains text files with code snippets that describe, e.g., the behavior of operations of classifiers.
 * - /diagrams: Contains the diagram files in JSON format. See also UmlDiagram.
 * - /elements: Contains the JSON files of the UmlElement objects. Each JSON file contains the stored properties of a 
 *   UmlElement object.
 *
 * Each JSON file also contains a version attribute ("version") to allow version-dependent extensions of the storage 
 * format. The current version number is always stored in the ISerializable.h file.
 *
 * UmlProject uses intrusive pointer (see description of template class IntrusivePtr) to manage the lifetime of the 
 * UmlElement objects. 
 *
 * ### Creating a new project
 *
 * The following lines create and initialize a new project:
 * ~~~{.c} 
 * auto project = new UmlProject();
 * bool result = project->create("/home/projects/", "myNewProject.uprj");
 * if (result == false)
 * {
 *    // Error handling:
      std::cout << "Error on creation: " << project->errorString(); 
 * }
 * ~~~
 * This will create a new folder "myNewProject" in folder "/home/projects/" with all necessary subfolders as well as
 * an empty UPRJ file with the same name. Note that you must always call function create() before using the project!
 * Otherwise, the project cannot be saved (function save() returns false).
 * If something goes wrong, the function returns false. Then property errorString() contains a description of the error.
 *
 * ### Adding and removing objects
 *
 * UmlElement objects can be added to the project in two ways: either by creating the UmlElement object with new and
 * then adding it using function insert() or by calling function insertNew() with the class name of the UmlElement 
 * object to be added. In the latter case a dynamic cast to the appropriate class may be necessary:
 * ~~~{.c}
 * auto diagram = dynamic_cast<UmlDiagram*>(project->insertNew("UmlDiagram"));
 * // Use diagram...
 * ~~~
 * Removing is straightforward: if you have a (intrusive) pointer to the object to be removed, simply pass it to the 
 * remove() function and then call the dispose() function of the object:
 * ~~~{.c}
 * project->remove(obj);
 * obj->dispose()
 * ~~~
 * Please note that this not necessarily deletes the object! If it is still referenced by another object, it will not
 * be destroyed.
 *
 * ### Loading and saving projects
 *
 * Existing projects should always be loaded into an empty UmlProject object. Therefore, it makes sense to create one
 * first and then call its load() function with the absolute file path (including file name) of the UPRJ file:
 * ~~~{.c}
 * auto project = new UmlProject();
 * bool result = project->load("/home/projects/myExistingProject.uprj");
 * if (result == false)
 * {
 *    // Error handling like above...
 * }
 * ~~~
 * In this case, it is not necessary to call create(). Instead function load() assumes that all subdirectories are 
 * present. If not, it returns false and sets property errorString() accordingly.
 *
 * Saving a project is easy: once create() is called, all subdirectories are present. Then it is enough to call the 
 * save() function with the file name of the UPRJ file:
 * ~~~{.c}
 * bool result = project->save("myNewProject.uprj");
 * if (result == false)
 * {
 *    // Error handling like above...
 * }
 * ~~~
 *
 * ### Deleting a project
 *
 * Before you delete an UmlProject object, you *must* call dispose():
 * ~~~{.c}
 * project->dispose();
 * delete project;
 * ~~~
 * After calling dispose(), the project cannot be used any more, all files removed from the project are removed, all
 * elements are diposed and - provided no other objects hold references (intrusive pointers) to them - deleted.
 */

const QString KArtifactsFolder = "artifacts";
const QString KCodeFolder      = "code";
const QString KDiagramsFolder  = "diagrams";
const QString KElementsFolder  = "elements";
const QString KDirSep          = "/";
const QString KUPRJExt         = ".uprj";
const QUuid   KRootIdentifier  = QUuid("{4CD3CF41-E522-4101-B57D-402CD2E8DF50}");

 //---------------------------------------------------------------------------------------------------------------------
 // Internal struct hiding implementation details
 //---------------------------------------------------------------------------------------------------------------------
 /// @cond
struct UmlProject::Data
{
   Data() 
   : root(nullptr)
   , isModified(false)
   , isDisposed(false)
   {}

   UmlRoot*                    root;
   QString                     author;
   QString                     name;
   QString                     comment;
   QHash<QUuid, UmlElementPtr> elements;
   QString                     artifactsFolder;
   QString                     codeFolder;
   QString                     diagramsFolder;
   QString                     elementsFolder;
   QString                     projectFolder;
   bool                        isModified;
   QStringList                 primitiveTypes;
   QStringList                 stereoTypes;
   QStringList                 removedFiles;
   bool                        isDisposed;
   QString                     errorString;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the UmlProject class.
 */
UmlProject::UmlProject()
: data(new Data())
{
   data->root = new UmlRoot(KRootIdentifier);
   insert(data->root);
}

UmlProject::~UmlProject()
{
   Q_ASSERT_X(data->isDisposed, "destructor", "UmlProject not disposed!");
   delete data;

#ifdef _DEBUG
   assertClean();
#endif
}

/**
 * Gets the author(s) of the project.
 */
QString UmlProject::author() const
{
   return data->author;
}

/**
 * Sets the author(s) of the project.
 */
void UmlProject::setAuthor(QString value)
{
   data->author = value;
}

/**
 * Gets the name of the project.
 */
QString UmlProject::name() const
{
   return data->name;
}

/**
 * Sets the name of the project.
 */
void UmlProject::setName(QString value)
{
   data->name = value;
}

/**
 * Gets the comment of the project.
 */
QString UmlProject::comment() const
{
   return data->comment;
}

/**
 * Sets the comment of the project.
 */
void UmlProject::setComment(QString value)
{
   data->comment = value;
}

/**
 * Gets a list of elements contained in the project.
 */
QList<UmlElement*> UmlProject::elements() const
{
   QList<UmlElement*> list;

   QHashIterator<QUuid, UmlElementPtr> iter(data->elements);
   while (iter.hasNext())
   {
      iter.next();
      list.append(iter.value());
   }

   return list;
}

/**
 * Gets the root element of the project.
 */
UmlRoot* UmlProject::root() const
{
   return data->root;
}

/**
 * Gets the count of elements in the project.
 */
int UmlProject::count() const
{
   return data->elements.size();
}

/**
 * Gets the path of the subfolder containing artifact files of the ViraquchaUML project.
 *
 * The /artifacts subfolder contains additional files of arbitrary format associated with the project. This can be e.g.
 * text documents with requirement specifications or image files or whatever. ViraquchaUML does not process such files 
 * itself but provides functions for opening these files in the appropriate applications. The files are stored as-is 
 * with their own file names.<br/><br/>
 * See also function create().
 */
QString UmlProject::artifactsFolder() const
{
   return data->artifactsFolder;
}

/**
 * Gets the path of the subfolder containing code files of the ViraquchaUML project.
 *
 * The /code subfolder contains files with snippets of code defining the behavior of an operation (class UmlOperation).
 * The name of such a file is the same as the name of the UmlOperation object file it is associated with. The language
 * of the code is stored along with the code itself in the first line of the file.<br/><br/>
 * See also function create(). 
 */
QString UmlProject::codeFolder() const
{
   return data->codeFolder;
}

/**
 * Gets the path of the subfolder containing diagram files of the ViraquchaUML project.
 *
 * The /diagrams subfolder contains the diagram files of the project. Each diagram file is tightly associated with a
 * UmlDiagram object. It has the same file name and file extension as the UmlDiagram object file and will be loaded
 * by the UmlDiagram object when calling function open() of that object.<br/><br/>
 * See also function create().
 */
QString UmlProject::diagramsFolder() const
{
   return data->diagramsFolder;
}

/**
 * Gets the path of the subfolder containing element files of the ViraquchaUML project.
 *
 * See also function create().
 */
QString UmlProject::elementsFolder() const
{
   return data->elementsFolder;
}

/**
 * Gets the project folder path.
 *
 * See function create() for details.
 */
QString UmlProject::projectFolder() const
{
   return data->projectFolder;
}

/** Gets a value indicating whether the project is modified. */
bool UmlProject::isModified() const
{
   return data->isModified;
}

/** Sets a value indicating whether the project is modified. */
void UmlProject::isModified(bool value)
{
   data->isModified = value;
}

/** 
 * Gets the list of standard primitive types of ViraquchaUML. 
 *
 * If called for the first time, the list contains the following default primitive types for languages like C++, C#, D 
 * or Java:
 * - bool (Boolean, any length >= 1Bit)
 * - char (Character, e.g. ASCII of 8Bit or Unicode of > 8Bit)
 * - double (IEEE double, 64Bit)
 * - float (IEEE float, 32Bit)
 * - int (Integer: 16, 24, 32Bit)
 * - long (Long integer: 32, 64Bit)
 * - short (Short integer: 8Bit)
 * - string (An ASCII or Unicode string, e.g. std::string in C++, String class in C# or string type in FreePascal)
 * - uint (Unsigned integer)
 * - ulong (Unsigned long integer)
 * - ushort (Unsigned short integer)
 * - void
 * 
 * Primitive types for other languages can be added using function addPrimitiveType(). The list is stored in the project
 * file.
 */
QStringList UmlProject::primitiveTypes() const
{
   if (data->primitiveTypes.isEmpty())
   {
      data->primitiveTypes << ""
         << tr("bool")
         << tr("char")
         << tr("double")
         << tr("float")
         << tr("int")
         << tr("long")
         << tr("short")
         << tr("string")
         << tr("uint")
         << tr("ulong")
         << tr("ushort")
         << tr("void");
   }

   return data->primitiveTypes;
}

/** 
 * Gets the list of stereotypes of the project. 
 *
 * If called for the first time, the list contains all stereotypes of the UML standard profile.
 */
QStringList UmlProject::stereoTypes() const
{
   if (data->stereoTypes.isEmpty())
   {
      data->stereoTypes << ""
         << tr("Auxiliary")
         << tr("BuildComponent")
         << tr("Call")
         << tr("Create")
         << tr("Derive")
         << tr("Destroy")
         << tr("Document")
         << tr("Entity")
         << tr("Executable")
         << tr("File")
         << tr("Focus")
         << tr("Framework")
         << tr("Implement")
         << tr("ImplementationClass")
         << tr("Instantiate")
         << tr("Library")
         << tr("Metaclass")
         << tr("Metamodel")
         << tr("ModelLibrary")
         << tr("Pocess")
         << tr("Realization")
         << tr("Refine")
         << tr("Responsibility")
         << tr("Script")
         << tr("Send")
         << tr("Service")
         << tr("Source")
         << tr("Specification")
         << tr("Subsystem")
         << tr("SystemModel")
         << tr("Trace")
         << tr("Type")
         << tr("Utility");
   }

   return data->stereoTypes;
}

/** Gets the error string if a file IO error was detected. */
QString UmlProject::errorString() const
{
   return data->errorString;
}

/**
 * Inserts a new UmlElement object of a given class name into the project and returns a pointer to it.
 *
 * @param className Concrete name of a class derived from UmlElement.
 * @returns Nullptr if the class name is not recognized by the element factory.
 */
UmlElement* UmlProject::insertNew(QString className)
{
   auto& factory = UmlElementFactory::instance();
   if (factory.isSubscribed(className))
   {
      auto* elem = factory.build(className, QUuid::createUuid());
      insert(elem);
      return elem;
   }

   return nullptr;
}

/**
 * Inserts an UmlElement object into the project.
 *
 * If there is already an object with the same identifier as the new object, the new object will not be inserted and 
 * the function returns false.
 *
 * @param elem UmlElement object to be inserted. Must not be nullptr.
 * @returns True, if the object could be inserted; otherwise false.
 */
bool UmlProject::insert(UmlElement* elem)
{
   if (elem != nullptr && !data->elements.contains(elem->identifier()))
   {
      elem->setProject(this);
      data->elements.insert(elem->identifier(), UmlElementPtr(elem));
      return true;
   }

   return false;
}

/**
 * Removes an object of the UmlElement class from the project.
 *
 * The root element cannot be removed. If you try nevertheless, the function will do nothing.
 * @param elem UmlElement object to be removed.
 */
void UmlProject::remove(UmlElement* elem)
{
   if (elem != nullptr && elem != data->root)
   {
      elem->setProject(nullptr);
      data->elements.remove(elem->identifier());
   }
}

/**
 * Checks whether the project contains an UmlElement object of a given identifier.
 *
 * @param id Identifier to be checked.
 * @returns True, if the project already contains an UmlElement object of the given identifier; otherwise false.
 */
bool UmlProject::contains(QUuid id)
{
   return data->elements.contains(id);
}

/**
 * Finds an UmlElement object by its identifier.
 *
 * @param id Identifier of the UmlElement object to be found.
 * @param elem Pointer to a pointer pointing to the object found.
 * @returns True if the object was found; otherwise false.
 */
bool UmlProject::find(QUuid id, UmlElement** elem)
{
   if (elem == nullptr) return false;
   if (data->elements.contains(id))
   {
      *elem = data->elements[id];
      return true;
   }

   *elem = nullptr;
   return false;
}

/**
 * Looks up a UmlElement by its identifier without checking whether it is contained in the project.
 *
 * This function is a bit faster than find() and easier to use because it does not check whether the project contains
 * a UmlElement of the given identifier or whether the identifier itself is valid. Use this function ONLY if you are 
 * certain that the UmlElement exists - if it does not exist, it will insert a nullptr into the project!
 */
UmlElement* UmlProject::take(QUuid id)
{
   return data->elements[id];
}

/**
 * Creates the project folder and its subfolders on disk.
 *
 * Call this function one time after initializing a new object of the UmlProject class. It creates the folders needed
 * to store the data of a ViraquchaUML project, that is
 * - a main folder containing the following subfolders as well as an empty UPRJ file;
 * - a subfolder &quot;artifacts&quot; which may contain files of arbitrary format assigned to the project;
 * - a subfolder &quot;code&quot; which may contain initial code of operations of UML classes;
 * - a subfolder &quot;diagrams&quot; containing all diagram data;
 * - a subfolder &quot;elements&quot; which contains all element files in JSON format.
 * 
 * It also sets properties projectFolder(), artifactsFolder(), codeFolder(), diagramsFolder() and elementsFolder() 
 * accordingly.
 * 
 * @param path Path where the project shall be created.
 * @param name Name of the main folder and the UPRJ file to be created.
 * @returns true if successful, false if an error occurred.
 */
bool UmlProject::create(QString path, QString name)
{
   qDebug() << "Creating new project at " << path << " with name '" << name << "'...";
   data->projectFolder = path + KDirSep + name;
   data->artifactsFolder = data->projectFolder + KDirSep + KArtifactsFolder;
   data->elementsFolder = data->projectFolder + KDirSep + KElementsFolder;
   data->codeFolder = data->projectFolder + KDirSep + KCodeFolder;
   data->diagramsFolder = data->projectFolder + KDirSep + KDiagramsFolder;

   QDir root;
   if (!root.exists(data->projectFolder))
   {
      if (!root.mkdir(data->projectFolder)) return false;
      if (root.cd(data->projectFolder))
      {
         if (!root.mkdir(data->artifactsFolder)) return false;
         if (!root.mkdir(data->elementsFolder)) return false;
         if (!root.mkdir(data->codeFolder)) return false;
         if (!root.mkdir(data->diagramsFolder)) return false;
         
         QFile prjfile(data->projectFolder + KDirSep + name + KUPRJExt);
         if (prjfile.open(QIODevice::ReadWrite))
         {
            prjfile.close();
            qDebug() << "Done.";
            return true;
         }
      }

      qDebug() << "Cannot change directory to project folder";
      return false;
   }

   qDebug() << "Project folder does not exist";
   return false;
}

/**
 * Loads the project from a project file and folder.
 *
 * @param filename Name of the project file (with extension *.uprj) including path to be loaded.
 * @returns true if successful, false if a parse error occurred or the project or an element file cannot be read.
 */
bool UmlProject::load(QString filename)
{
   setErrorString("");

   // Skip if it is not a project file and folder:
   if (!isProject(filename))
   {
      setErrorString(QString(KNoProjectError).arg(filename));
      return false;
   }

   // Variables needed to compute the current load in percent:
   int count = 0, current = 1;
   QJsonParseError error;

   // Load project file first - it references all other files:
   QFile prjfile(filename);
   if (prjfile.open(QIODevice::ReadOnly))
   {
      qDebug() << "Start reading project file...";
      auto doc = QJsonDocument::fromJson(prjfile.readAll(), &error);
      if (doc.isNull())
      {
         setErrorString(QString(KFileParseError).arg(filename).arg(toString(error)));
         return false;
      }

      auto obj = doc.object();
      data->author = obj[KPropAuthor].toString();
      data->name = obj[KPropName].toString();
      data->comment = obj[KPropComment].toString();
      count = obj[KPropCount].toInt();

      auto array = obj[KPropElements].toArray();
      for (int index = 0; index < array.size(); ++index)
      {
         auto obj = array[index].toObject();

         // Retreive object and class identifier from the JSON file:
         QString name = obj[KPropClass].toString();
         QUuid ident(obj[KPropIdentifier].toString());
         if (!ident.isNull() && ident != KRootIdentifier)
         {
            qDebug() << "Inserting new class '" << name << "' into project.";
            // Build the element with this information using the factory:
            insert(UmlElementFactory::instance().build(name, ident));
         }
      }

      prjfile.close();
      qDebug() << "Done.";
   }
   else
   {
      setErrorString(QString(KFileReadError).arg(filename).arg(prjfile.errorString()));
      return false;
   }

   // Do not load corrupt project file:
   if (count == 0) return false;

   // Now load all other files:
   QHashIterator<QUuid, UmlElementPtr> iter(data->elements);
   while (iter.hasNext())
   {
      iter.next();

      QFile objfile(iter.value()->elementFile());
      if (objfile.open(QIODevice::ReadOnly))
      {
         qDebug() << "Start reading element file...";
         auto doc = QJsonDocument::fromJson(objfile.readAll(), &error);
         if (doc.isNull())
         {
            setErrorString(QString(KFileParseError).arg(objfile.fileName()).arg(toString(error)));
            return false;
         }

         auto obj = doc.object();
         int  ver = obj[KPropVersion].toInt();
         iter.value()->serialize(obj, true, ver);
         objfile.close();

         // Compute percentage and issue signal:
         int percent = (current / count) * 100;
         emit updateProgress(percent);
         ++current;
         qDebug() << "Done.";
      }
      else
      {
         setErrorString(QString(KFileReadError).arg(objfile.fileName()).arg(objfile.errorString()));
         return false;
      }
   }

   isModified(false);
   qDebug() << "Project successfully read.";
   return true;
}

/**
 * Saves the project to a project file and folder.
 *
 * Note: If the project does not yet exist on disk, call function create() first. This function assumes that the
 * subfolder structure is already created. If not, it will return false.
 *
 * @param filename File name including path of the project file (with file extension *.uprj) to be saved.
 * @returns true if successful, false if an error occurred.
 */
bool UmlProject::save(QString filename)
{
   setErrorString("");

   // Skip if it is not a project file and folder:
   if (!isProject(filename))
   {
      setErrorString(QString(KNoProjectError).arg(filename));
      return false;
   }

   // Variables needed to compute the current save in percent:
   int count = data->elements.size(), current = 1;

   // Write the project file down to the folder:
   QSaveFile prjfile(filename);
   if (prjfile.open(QIODevice::WriteOnly | QIODevice::Truncate))
   {
      qDebug() << "Writing project file '" << filename << "'...";
      QJsonObject obj;
      obj[KPropAuthor] = data->author;
      obj[KPropName] = data->name;
      obj[KPropComment] = data->comment;
      obj[KPropCount] = count;
      obj[KPropVersion] = (int)KFileVersion;

      QJsonArray array;
      QHashIterator<QUuid, UmlElementPtr> iter(data->elements);
      while (iter.hasNext())
      {
         iter.next();

         QJsonObject obj;
         obj[KPropClass] = iter.value()->className();
         obj[KPropIdentifier] = iter.value()->identifier().toString();
         array.append(obj);
      }
      obj[KPropElements] = array;

      QJsonDocument doc(obj);
      prjfile.write(doc.toJson(QJsonDocument::Compact));
      prjfile.commit();
      qDebug() << "Done.";
   }
   else
   {
      setErrorString(QString(KFileWriteError).arg(filename).arg(prjfile.errorString()));
      return false;
   }

   // Now write each element to its own file:
   QHashIterator<QUuid, UmlElementPtr> iter(data->elements);
   while (iter.hasNext())
   {
      iter.next();

      QSaveFile objfile(iter.value()->elementFile());
      if (objfile.open(QIODevice::WriteOnly | QIODevice::Truncate))
      {
         qDebug() << "Start writing element file...";
         QJsonObject obj;
         obj[KPropVersion] = (int)KFileVersion;
         iter.value()->serialize(obj, false, KFileVersion);

         QJsonDocument doc(obj);
         objfile.write(doc.toJson(QJsonDocument::Compact));
         objfile.commit();

         // Compute percentage and issue signal:
         int percent = (current / count) * 100;
         emit updateProgress(percent);
         ++current;
         qDebug() << "Done.";
      }
   }

   // And remove all files of disposed elements:
   for (int index = 0; index < data->removedFiles.count(); ++index)
   { 
      QFile file(data->removedFiles[index]);
      if (file.exists())
      {
         qDebug() << "Removing file '" << file.fileName() << "'...";
         file.remove();
      }
   }
   data->removedFiles.clear();

   isModified(false);
   qDebug() << "Project successfully written.";
   return 0;
}

/**
 * Disposes all objects in the project, including the root object.
 *
 * This function must be called before deleting the project. After calling it, the project cannot be used anymore.
 */
void UmlProject::dispose()
{
   QHashIterator<QUuid, UmlElementPtr> iter(data->elements);
   while (iter.hasNext())
   {
      iter.next();
      iter.value()->dispose(false);
   }

   data->elements.clear();
   data->root = nullptr;
   data->isDisposed = true;
}

/** 
 * Adds a file name to the list of files to be removed. 
 *
 * If a file needs to be deleted from the project folders, it should not be deleted directly! Instead it should be
 * added to the list of files to be removed in the UmlProject object. The UmlProject object takes care of deleting
 * the file from the folders and from the project file (*.uprj) on saving (lazy delete), thus preventing invalid
 * projects.
 */
void UmlProject::removeFile(QString filename)
{
   if (!filename.isEmpty() && !data->removedFiles.contains(filename))
   {
      data->removedFiles.append(filename);
   }
}

/** Removes a file name from the list of files to be removed. */
void UmlProject::recoverFile(QString filename)
{
   if (!filename.isEmpty())
   {
      data->removedFiles.removeAll(filename);
   }
}

/**
 * Adds a primitive type to the list of primitive types of the project.
 *
 * The list of primitive types is stored in the *.UPRJ file of the ViraquchaUML project.
 * @param name Name of the primitive type to be added.
 */
void UmlProject::addPrimitiveType(QString name)
{
   if (data->primitiveTypes.contains(name)) return;
   data->primitiveTypes.append(name);
}

/**
 * Removes a primitive type from the list of primitive types of the project.
 *
 * @param name Name of the primitive type to be removed.
 */
void UmlProject::removePrimitiveType(QString name)
{
   data->primitiveTypes.removeOne(name);
}

/**
 * Resets the list of primitive types of the project to the default primitive types.
 */
void UmlProject::resetPrimitiveTypes()
{
   data->primitiveTypes.clear();
   primitiveTypes();
}

/**
 * Adds a new stereotype to the list of stereotypes of the project.
 *
 * @param name Name of the stereotype to be added.
 */
void UmlProject::addStereoType(QString name)
{
   if (data->stereoTypes.contains(name)) return;
   data->stereoTypes.append(name);
}

/**
 * Removes a stereotype from the list of stereotypes of the project.
 *
 * @param name Name of the stereotype to be removed.
 */
void UmlProject::removeStereoType(QString name)
{
   data->stereoTypes.removeOne(name);
}

/**
 * Resets the list of stereotypes of the project to the UML standard profile.
 */
void UmlProject::resetStereoTypes()
{
   data->stereoTypes.clear();
   stereoTypes();
}

/**
 * Checks wheter a given file name is a ViraquchaUML project file.
 *
 * @param filename File name to be checked
 */
bool UmlProject::isProject(QString filename)
{
   QFileInfo info(filename);
   data->projectFolder = info.path();
   data->artifactsFolder = data->projectFolder + KDirSep + KArtifactsFolder;
   data->codeFolder = data->projectFolder + KDirSep + KCodeFolder;
   data->diagramsFolder = data->projectFolder + KDirSep + KDiagramsFolder;
   data->elementsFolder = data->projectFolder + KDirSep + KElementsFolder;

   QDir dir(data->projectFolder);
   auto list = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDir::DirsFirst | QDir::Name);
   if (list.count() == 5)
   { 
      return (list[0].isDir() && list[0].fileName() == KArtifactsFolder) &&
             (list[1].isDir() && list[1].fileName() == KCodeFolder) &&
             (list[2].isDir() && list[2].fileName() == KDiagramsFolder) &&
             (list[3].isDir() && list[3].fileName() == KElementsFolder) &&
             (list[4].isFile() && list[4].fileName().endsWith(KUPRJExt));
   }

   return false;
}

/** Sets the error string. */
void UmlProject::setErrorString(QString value)
{
   data->errorString = value;
}

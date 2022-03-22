//---------------------------------------------------------------------------------------------------------------------
// UmlDiagram.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlDiagram.
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
#include "UmlDiagram.h"
#include "UmlElement.h"
#include "UmlLink.h"
#include "UmlProject.h"

#include "DiaEdge.h"
#include "DiaNode.h"
#include "ErrorTools.h"
#include "PropertyStrings.h"

#include <QDebug>
#include <QSaveFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QListIterator>
#include <QString>
#include <QUuid>

/**
 * @class UmlDiagram
 * @brief The UmlDiagram class models a UML diagram.
 * @since 0.1.0
 * @ingroup UmlCommon
 *
 * The UmlDiagram class models a diagram on which graphical representations (shapes) of the UmlElement objects can be 
 * stored. It corresponds to the "diagram" of the UML specification, with the difference that it is also derived from 
 * the UmlElement class. Objects of these classes can therefore theoretically be used in the same way as other memory 
 * objects in the project (for example, linking to other objects. In practice, however, this does not make much sense).
 *
 * To avoid that the graphical information has to be kept permanently in memory, the class UmlDiagram uses a subsystem 
 * consisting of the classes DiaShape, DiaNode and DiaEdge, which is only loaded into memory when needed. DiaShape is 
 * the base class for DiaNode and DiaEdge. The data of these classes is stored in a separate JSON file in the "diagrams" 
 * subdirectory of the project. This file has the same name as the JSON file of the  UmlDiagram object itself. 
 *
 * Before a UmlDiagram object can be used, it must be "opened". After modifying its data, it should be saved and then
 * "closed". This can be done with the following functions:
 * ~~~{.c}
 * auto diagram = dynamic_cast<UmlDiagram*>(project->insertNew("UmlDiagram"));
 * diagram->open();
 * 
 * // Do some modification, e.g. add nodes and edges:
 * auto node = diagram->addNode(...);
 * auto edge = diagram->addEdge(...);
 * 
 * // Save the modified diagram and then close it:
 * diagram->save();
 * diagram->close();
 * ~~~
 * If necessary, function open() creates the file in the subdirectory. After calling close() all DiaShape objects are
 * removed from memory.
 * 
 * UmlDiagram implements the IElementObserver interface. It automatically logs on to an UmlElement object in two cases:
 * - when a new DiaShape object is created by calling functions addNode() or addEdge()
 * - when a DiaShape object is loaded from a diagram file
 * 
 * If the UmlElement object is released from the project, it sends a notification to the UmlDiagram object which then
 * removes the DiaShape object associated with the UmlElement object.
 */

static const int KDiagramVersion = 1; // File version of diagram files - may differ from the global file version.

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlDiagram::Data
{
   Data()
   : kind(DiagramKind::Undefined)
   , isOpen(false)
   {}

   QString         name;
   QString         comment;
   DiagramKind     kind;
   QList<DiaNode*> nodes;
   QList<DiaEdge*> edges;
   bool            isOpen;
   QString         errorString;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the UmlDiagram class with a new identifier.
 */
UmlDiagram::UmlDiagram()
: data(new Data())
{
}

/**
 * Initializes a new object of the UmlDiagram class with an existing identifier.
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new object with a new unique identifier, use the constructor without parameters instead.
 * @param id Identifier read from serialization or passed in by unit tests.
 */
UmlDiagram::UmlDiagram(QUuid id)
: super(id)
, data(new Data())
{
}

UmlDiagram::~UmlDiagram()
{
   clear();
   delete data;
}

/** 
 * Gets the class name. 
 */
QString UmlDiagram::className() const
{
   return staticMetaObject.className();
}

/** 
 * Gets name and path of the diagram file. 
 */
QString UmlDiagram::diagramFile() const
{
   return project()->diagramsFolder() + "/" + identifier().toString() + ".json";
}

/**
 * Gets a value indicating whether the diagram is open.
 *
 * This property is set by function open().
 */
bool UmlDiagram::isOpen() const
{
   return data->isOpen;
}

/**
 * Gets the name of the diagram.
 */
QString UmlDiagram::name() const
{
   return data->name;
}

/**
 * Sets the name of the diagram.
 */
void UmlDiagram::setName(QString value)
{
   data->name = value;
}

/**
 * Gets the comment of the diagram.
 */
QString UmlDiagram::comment() const
{
   return data->comment;
}

/**
 * Sets the comment of the diagram.
 */
void UmlDiagram::setComment(QString value)
{
   data->comment = value;
}

/**
 * Gets the visibility of the diagram.
 *
 * Note: the visibility of a diagram is always &quot;public&quot;. Therefore, it cannot be set.
 */
VisibilityKind UmlDiagram::visibility() const
{
   return VisibilityKind::Public;
}

/**
 * This function is unused.
 */
void UmlDiagram::setVisibility(VisibilityKind value)
{
   Q_UNUSED(value);
}

/**
 * Gets the DiagramKind value of the diagram.
 */
DiagramKind UmlDiagram::kind() const
{
   return data->kind;
}

/**
 * Sets the DiagramKind value of the diagram.
 */
void UmlDiagram::setKind(DiagramKind value)
{
   data->kind = value;
}

/**
 * Gets a list of DiaNode objects.
 */
QList<DiaNode*> UmlDiagram::nodes() const
{
   return QList<DiaNode*>(data->nodes);
}

/**
 * Gets the node count.
 */
int UmlDiagram::nodeCount() const
{
   return data->nodes.size();
}

/**
 * Gets a list of DiaEdge objects.
 */
QList<DiaEdge*> UmlDiagram::edges() const
{
   return QList<DiaEdge*>(data->edges);
}

/**
 * Gets the edge count.
 */
int UmlDiagram::edgeCount() const
{
   return data->edges.size();
}

/** Gets the error string if a file IO error was detected. */
QString UmlDiagram::errorString() const
{
   return data->errorString;
}

/**
 * Adds a new DiaNode object to the diagram and assigns the UmlElement object to it.
 * 
 * Note that the function does not check whether the UmlElement object is already contained in the diagram! This must
 * be done by the caller (See function contains()).
 * @param elm UmlElement object to be assigned to the new DiaNode object.
 * @returns A new DiaNode object or nullptr if elm == nullptr.
 */
DiaNode* UmlDiagram::addNode(UmlElement* elm)
{
   if (elm != nullptr)
   {
      elm->observers().append(this);

      auto* node = new DiaNode();
      node->setElement(elm);
      append(node);
      return node;
   }

   return nullptr;
}

/**
 * Adds a new DiaEdge object to the diagram and assigns the UmlLink object to it.
 * 
 * Note that the function does not check whether the UmlLink object is already contained in the diagram! This must
 * be done by the caller (See function contains()).
 * @param lnk UmlLink object to be assigned to the new DiaEdge object.
 * @returns A new DiaEdge object or nullptr if lnk == nullptr.
 */
DiaEdge* UmlDiagram::addEdge(UmlLink* lnk)
{
   if (lnk != nullptr)
   {
      lnk->observers().append(this);

      auto* edge = new DiaEdge();
      edge->setLink(lnk);
      append(edge);
      return edge;
   }

   return nullptr;
}

/**
 * Removes a DiaNode object from the diagram and deletes it.
 * 
 * @param node DiaNode object to be removed from the diagram.
 */
void UmlDiagram::remove(DiaNode* node)
{
   if (node != nullptr)
   {
      node->element()->observers().removeOne(this);
      data->nodes.removeOne(node);
      delete node;
   }
}

/**
 * Removes a DiaEdge object from the diagram and deletes it.
 * 
 * @param edge DiaEdge object to be removed from the diagram.
 */
void UmlDiagram::remove(DiaEdge* edge)
{
   if (edge != nullptr)
   {
      edge->link()->observers().removeOne(this);
      data->edges.removeOne(edge);
      delete edge;
   }
}

/**
 * Uses the identifier of an UmlElement object to remove the DiaNode or DiaEdge object assigned to the element.
 * 
 * @param id Identifier of the UmlElement object
 */
void UmlDiagram::removeById(QUuid id)
{
   for (auto* node : data->nodes)
   {
      if (node->element()->identifier() == id)
      {
         data->nodes.removeOne(node);
         delete node;
         
         // Iterator is invalid now, break out!
         break;
      }
   }

   for (auto* edge : data->edges)
   {
      if (edge->link()->identifier() == id)
      {
         data->edges.removeOne(edge);
         delete edge;
         
         // Iterator is invalid now, break out!
         break;
      }
   }
}

/**
 * Checks whether an UmlElement object of a given identifier is already contained in the diagram.
 * 
 * @param id Identifier to be checked.
 * @returns true, if the object is contained; false otherwise.
 */
bool UmlDiagram::contains(QUuid id)
{
   for (auto* node : data->nodes)
   {
      if (node->element()->identifier() == id)
      {
         return true;
      }
   }

   for (auto* edge : data->edges)
   {
      if (edge->link()->identifier() == id)
      {
         return true;
      }
   }
   
   return false;
}

/**
 * Clears the diagram.
 */
void UmlDiagram::clear()
{
   // Delete DiaNode objects first:
   for (auto* node : data->nodes)
   {
      node->element()->observers().removeOne(this);
      delete node;
   }
   data->nodes.clear();

   // Then delete DiaEdge objects:
   for (auto* edge : data->edges)
   {
      edge->link()->observers().removeOne(this);
      delete edge;
   }
   data->edges.clear();
}

/**
 * Disposes the diagram.
 *
 * This function resets intrusive pointers and releases system resources owned by the object. It should not be called 
 * directly, call function dispose() without parameters instead.
 */
void UmlDiagram::dispose(bool disposing)
{
   if (disposing)
   {
      // Do a lazy remove of the diagram file:
      project()->removeFile(diagramFile());
   }

   super::dispose(disposing);
}

/** 
 * Opens the diagram by loading diagram data from a file. 
 *
 * The function returns false if loading failed. Use property errorString() to retrieve the error that caused the 
 * failure. See also function save().
 * @returns true if successful; otherwise false.
 */
bool UmlDiagram::open()
{
   // Pre: diagram must be opened only once.
   if (data->isOpen) return false;
   setErrorString("");

   QString filename = diagramFile();
   QFile diafile(filename);
   if (diafile.open(QIODevice::ReadOnly))
   {
      QJsonParseError error;

      qDebug() << "Reading diagram file '" << filename << "'...";
      auto doc = QJsonDocument::fromJson(diafile.readAll(), &error);
      if (doc.isNull())
      { 
         setErrorString(QString(KFileParseError).arg(filename).arg(::toString(error)));
         data->isOpen = true; // Diagram is open but empty!
         return false;
      }

      QMap<DiaEdge*, QPair<QUuid, QUuid>> grid; // Needed for setting the shapes of an edge
      QMap<QUuid, DiaShape*>              shapes;
      int                                 index;
 
      // Read DiaNodes first:
      auto json  = doc.object();
      auto nodes = json[KPropNodes].toArray();
      for (index = 0; index < nodes.size(); ++index)
      {
         auto obj = nodes[index].toObject();
         auto id = QUuid(obj[KPropElement].toString());
         
         UmlElement* elem = nullptr;
         if (project()->find(id, &elem))
         {
            elem->observers().append(this);
            
            auto* node = new DiaNode();
            node->setElement(elem);
            node->serialize(obj, true, KDiagramVersion);
            
            shapes.insert(id, node);
            append(node);
         }
         else
         {
            qDebug() << "Element " << id.toString() << " was removed, node not created.";
         }
      }

      // Then read DiaEdges...
      auto edges = json[KPropEdges].toArray();
      for (index = 0; index < edges.size(); ++index)
      {
         auto obj = edges[index].toObject();
         auto id = QUuid(obj[KPropLink].toString());

         UmlElement* elem = nullptr;
         if (project()->find(id, &elem))
         {
            elem->observers().append(this);
            
            auto* edge = new DiaEdge();
            edge->setLink(dynamic_cast<UmlLink*>(elem));
            edge->serialize(obj, true, KDiagramVersion);
            
            shapes.insert(id, edge);
            grid.insert(edge, qMakePair(QUuid(obj[KPropNode1].toString()), QUuid(obj[KPropNode2].toString())));
            append(edge);
         }
         else
         {
            qDebug() << "Link " << id.toString() << " was removed, edge not created.";
         }
      }

      // ...and connect them with their DiaShapes:
      for (index = 0; index < data->edges.size(); ++index)
      {
         auto* edge = data->edges[index];
         auto  pair = grid[edge];

         edge->setShape1(shapes[pair.first]);
         edge->setShape2(shapes[pair.second]);
         if (edge->shape1() == nullptr || edge->shape2() == nullptr)
         {
            setErrorString("Error connecting edge shape");
            clear();
            data->isOpen = true;
            return false;
         }
      }

      qDebug() << "Done.";
      diafile.close();
   }

   data->isOpen = true;
   return true;
}

/** Closes the diagram and removes all diagram data from memory. */
void UmlDiagram::close()
{
   clear();
   data->isOpen = false;
}

/** 
 * Saves diagram data to a file located in the diagrams folder of the project. 
 *
 * The name of the file is automatically set to be the same as the file name of the element file. The difference is 
 * that it is located in the diagrams subfolder of the project file, instead of in the elements folder.
 * @returns true, if saving was successful; otherwise false.
 */
bool UmlDiagram::save()
{
   // Pre: Diagram must be open to be saved.
   if (!data->isOpen) return false;
   setErrorString("");

   QString   filename = diagramFile();
   QSaveFile diafile(filename);
   if (diafile.open(QIODevice::WriteOnly | QIODevice::Truncate))
   {
      qDebug() << "Writing diagram file '" << filename << "'...";
      QJsonObject json;

      // Add DiaNodes to the JSON file:
      QJsonArray nodes;
      for (auto* node : data->nodes)
      {
         QJsonObject obj;
         obj[KPropElement] = node->element()->identifier().toString();
         node->serialize(obj, false, KDiagramVersion);
         nodes.append(obj);
      }
      json[KPropNodes] = nodes;

      // Add DiaEdges to the JSON file:
      QJsonArray edges;
      for (auto* edge : data->edges)
      {
         auto* link = edge->link();

         QJsonObject obj;
         obj[KPropLink] = link->identifier().toString();
         obj[KPropNode1] = link->source()->identifier().toString();
         obj[KPropNode2] = link->target()->identifier().toString();
         edge->serialize(obj, false, KDiagramVersion);
         edges.append(obj);
      }
      json[KPropEdges] = edges;

      QJsonDocument doc(json);
      diafile.write(doc.toJson(QJsonDocument::Compact));
      diafile.commit();
      qDebug() << "Done.";
      return true;
   }

   qDebug() << "Diagram file '" << filename << "' cannot be opened for writing.";
   return false;
}

/**
 * Serializes properties of the UmlDiagram object to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlDiagram::serialize(QJsonObject& json, bool read, bool flat, int version)
{
   super::serialize(json, read, flat, version);
   if (read)
   {
      data->name = json[KPropName].toString();
      data->comment = json[KPropComment].toString();
      data->kind = (DiagramKind)json[KPropDiagramKind].toInt();
   }
   else
   {
      json[KPropName] = data->name;
      json[KPropComment] = data->comment;
      json[KPropDiagramKind] = (int)data->kind;
      save();
   }
}

/**
 * Handles a notification sent by an UmlElement object.
 * 
 * Removes the DiaShape object associated with the sender from the diagram, if type == EventType::ObjectReleased.
 * @param sender The UmlElement object sending the event.
 * @param type Event type.
 */
void UmlDiagram::notify(UmlElement* sender, EventType type)
{
   if (type == EventType::ObjectReleased)
   {
      removeById(sender->identifier());
   }
}

/** Gets a string representation of the object. */
QString UmlDiagram::toString() const
{
   return data->name;
}

/** Appends a DiaNode object to the list of nodes. */
void UmlDiagram::append(DiaNode* node)
{
   data->nodes.append(node);
}

/** Appends a DiaEdge object to the list of edges. */
void UmlDiagram::append(DiaEdge* edge)
{
   data->edges.append(edge);
}

/** Sets the error string. */
void UmlDiagram::setErrorString(QString value)
{
   data->errorString = value;
}

//---------------------------------------------------------------------------------------------------------------------
// ProjectTreeModel.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class ProjectTreeModel.
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
#include "ProjectTreeModel.h"
#include "IconProvider.h"

#include "UmlElement.h"
#include "UmlProject.h"
#include "UmlRoot.h"
#include "INamedElement.h"
#include "NameBuilder.h"

#include <QDebug>
#include <QIcon>
#include <QListIterator>

/**
 * @class ProjectTreeModel
 * @brief Implements the concrete item model of the project tree.
 * @since 0.1.0
 * @ingroup GuiProject
 * 
 * The ProjectTreeModel class implements abstract base class QAbstractItemModel. It provides the model for the project 
 * tree view of ViraquchaUML which is shown on the left side of the main window.
 */

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the ProjectTreeModel class.
 * @param root UmlRoot object of the project associated.
 * @param parent Parent object.
 */
ProjectTreeModel::ProjectTreeModel(UmlRoot* root, QObject* parent)
: super(parent)
, _root(root)
{
}

ProjectTreeModel::~ProjectTreeModel()
{
}

//---------------------------------------------------------------------------------------------------------------------
// Implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Gets the model index of the item in the tree model specified by the given row, column and parent index.
 * 
 * @param row Row of the model index.
 * @param column Column of the model index.
 * @param parent Parent model index.
 * @returns The model index found for the specified row, column and parent index.
 */
QModelIndex ProjectTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if (parent.isValid() && parent.column() != 0) return QModelIndex();
    
    auto* owner = getComposite(parent);
    auto* child = owner->at(row);
    if (child != nullptr)
    {
       return createIndex(row, column, child);
    }

    return QModelIndex();
}

/**
 * Gets the parent model index of a given model index.
 * 
 * @param index Model index to get the parent of.
 * @returns The model index of the parent.
 */
QModelIndex ProjectTreeModel::parent(const QModelIndex& index) const
{
    if (!index.isValid()) return QModelIndex();

    auto* child = getElement(index);
    auto* owner = child->owner();

    if (owner == _root) return QModelIndex();
    if (owner->owner() != nullptr)
    {
       return createIndex(owner->owner()->indexOf(owner), 0, owner);
    }

    return createIndex(0, 0, owner);
}

/** 
 * Gets the row count of a specified parent model index in the project tree. 
 * 
 * @param parent Parent model index.
 * @returns The row count.
 */
int ProjectTreeModel::rowCount(const QModelIndex& parent) const
{
   auto* owner = getComposite(parent);
   if (owner != nullptr) return owner->count(false);
   return 0;
}

/** 
 * Gets the column count of a specified parent model index in the project tree.
 * 
 * Always returns 1 column for all elements in the project tree, since this tree has no further columns. 
 * @param parent Parent model index.
 * @returns Always 1.
 */
int ProjectTreeModel::columnCount(const QModelIndex& parent) const
{
   return 1;
}

/**
 * Gets data stored under a given role for the item referred to by the model index.
 * 
 * @param index Model index.
 * @param role Role (e.g. Qt::EditRole)
 * @returns A QVariant object containing the data.
 */
QVariant ProjectTreeModel::data(const QModelIndex& index, int role) const
{
   if (index.isValid())
   {
      UmlElement* elem = getElement(index);
      switch (role)
      {
      case Qt::DecorationRole:
         return IconProvider::getIcon(elem->className());
      case Qt::DisplayRole:
         return elem->toString();
      case Qt::EditRole:
      {
         INamedElement* named = dynamic_cast<INamedElement*>(elem);
         if (named == nullptr) break;
         return named->name();
      }
      case Qt::ToolTipRole:
      case Qt::StatusTipRole:
      case Qt::WhatsThisRole:
      default:
         break;
      }
   }

   return QVariant();
}

/**
 * Sets the role data for the item at the given index to the given value.
 * 
 * This concrete implementation of the function only uses the Qt::EditRole to set the name of the UML element stored
 * at the given index to the value passed in (i.e. the value is assumed to be a string containing the name entered by
 * the user). All other roles are ignored.
 * Emits the dataChanged() signal if the data was successfully set and then returns true.
 * @param index Model index under which the UML element is stored in the project tree.
 * @param value Value to be set, in this case the name entered by the user.
 * @param role Role of the data to be set.
 * @returns true if role == Qt::EditRole and name was successfully set; false otherwise.
 */
bool ProjectTreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
   if (index.isValid())
   {
      QString name = value.toString();
      if (name == "") return false;

      INamedElement* named = dynamic_cast<INamedElement*>(getElement(index));
      if (named == nullptr) return false;
      if (role == Qt::EditRole)
      {
         named->setName(name);
         emit dataChanged(index, index);
         return true;
      }
   }

   return false;
}

/**
 * Gets item flags for a given model index.
 * 
 * @param index Model index.
 * @returns Item flags or 0 if index is invalid.
 */
Qt::ItemFlags ProjectTreeModel::flags(const QModelIndex& index) const
{
   if (!index.isValid()) return 0;
   return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

/**
 * Gets header data for a given section, orientation and role.
 * 
 * @param section This parameter is ignored.
 * @param orientation Orientation, only Qt::Horizontal is accepted.
 * @param role Role, only Qt::DisplayRole is accepted.
 * @returns A QVariant object containing header data.
 */
QVariant ProjectTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   Q_UNUSED(section);
   if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
   {
      return tr("Element");
   }

   return QVariant();
}

/**
 * Gets the model index of a UmlElement object.
 * @param element
 * @return Model index of the object.
 */
QModelIndex ProjectTreeModel::indexOf(UmlElement* element)
{
   if (element != nullptr)
   {
      auto* owner = element->owner();
      if (owner != nullptr)
      {
         return createIndex(owner->elements().indexOf(element), 0, element);
      }
   }

   return QModelIndex();
}

/**
 * Gets the parent model index of a UmlElement object.
 * @param element
 * @return The parent model index of the object.
 */
QModelIndex ProjectTreeModel::parentOf(UmlElement* element)
{
   if (element != nullptr)
   {
      auto* owner = element->owner();
      if (owner == _root) return QModelIndex();
      if (owner->owner() != nullptr)
      {
         return createIndex(owner->owner()->indexOf(owner), 0, owner);
      }

      return createIndex(0, 0, owner);
   }

   return QModelIndex();
}

/**
 * Inserts a single row for a UML element before the given position in the list of child items of the parent specified.
 * 
 * @param position Insert position.
 * @param parent Parent.
 * @param element UML element.
 * @returns true if successful; false otherwise.
 */
bool ProjectTreeModel::insertRow(int position, const QModelIndex& parent, UmlElement* element)
{
   if (!parent.isValid()) return false;

   auto* owner = getComposite(parent);
   Q_ASSERT(owner != nullptr);

   if (element != nullptr)
   {
      auto* project = _root->project();
      project->insert(element);
      if (element->isHidden())
      {
         // Append at the end of the parent, do not update tree!
         owner->append(element);
         project->isModified(true);
         return true;
      }

      beginInsertRows(parent, position, position);
      owner->insert(position, element);
      endInsertRows();
      project->isModified(true);
      return true;
   }

   return false;
}

/**
 * Inserts a single row for a UML element at the end of the list of child items of the parent specified.
 * 
 * @param parent Parent.
 * @param element UML element.
 * @returns true if successful; false otherwise.
 */
bool ProjectTreeModel::insertRow(const QModelIndex& parent, UmlElement* element)
{
   if (!parent.isValid()) return false;

   auto* owner = getComposite(parent);
   Q_ASSERT(owner != nullptr);

   if (element != nullptr)
   {
      auto* project = _root->project();
      project->insert(element);
      if (element->isHidden())
      {
         // Append at the end of the parent, do not update tree!
         owner->append(element);
         project->isModified(true);
         return true;
      }

      int pos = owner->count(false);
      beginInsertRows(parent, pos, pos);
      owner->insert(pos, element);
      endInsertRows();
      project->isModified(true);
      return true;
   }

   return false;
}

/**
 * Inserts a single row for a UML element at the end of the list of child items of the parent specified.
 * 
 * This is an overloaded function. It creates a new UML element using the className and then sets its name to the given
 * baseName.
 * @param parent
 * @param className Name of the class that shall be created.
 * @param baseName Base name of the new object.
 * @returns true if successful; false otherwise.
 */
bool ProjectTreeModel::insertRow(const QModelIndex& parent, QString className, QString baseName)
{
   if (!parent.isValid()) return false;
   
   auto* owner = getComposite(parent);
   Q_ASSERT(owner != nullptr);

   auto* project = _root->project();
   auto* element = project->insertNew(className);
   if (element == nullptr) return false;

   auto* named = dynamic_cast<INamedElement*>(element);
   if (named != nullptr)
   {
      NameBuilder builder(owner);
      named->setName(builder.build(baseName));
   }

   if (element->isHidden())
   {
      // Append at the end of the parent, do not update tree!
      owner->append(element);
      project->isModified(true);
      return true;
   }

   int pos = owner->count(false);
   beginInsertRows(parent, pos, pos);
   owner->insert(pos, element);
   endInsertRows();
   project->isModified(true);
   return true;
}

/**
 * Removes a row specified by a model index from the project tree.
 * 
 * @param index Model index.
 * @returns true if successful; otherwise false.
 */
bool ProjectTreeModel::removeRow(const QModelIndex& index)
{
   if (!index.isValid()) return false;

   auto* elem = getElement(index);
   auto* owner = getComposite(index.parent());
   auto* project = _root->project();
   if (elem != nullptr && owner != nullptr)
   {
      int pos = index.row();
      beginRemoveRows(index.parent(), pos, pos);
      removeRecursive(elem);
      endRemoveRows();
      project->isModified(true);
      return true;
   }
   
   return false;
}

/**
 * Removes a row specified by a model index of a parent object and a UmlElement object.
 * 
 * This function uses an UmlElement object to find the row to be removed. Row number in the tree model as well as index 
 * number in the parent holding the element must be the same, otherwise the function will fail.
 * @param index Model index of the parent.
 * @param element UmlElement object to be removed.
 * @returns true if successful; otherwise false.
 */
bool ProjectTreeModel::removeRow(const QModelIndex& parent, UmlElement* element)
{
   if (!parent.isValid()) return false;
   
   auto* owner = getComposite(parent);
   auto* project = _root->project();
   if (element != nullptr && owner != nullptr)
   {
      // We assume that the index of the element in its parent is the same as the 
      // row of the sub tree where the element is shown:
      return removeRow(index(owner->indexOf(element), 0, parent));
   }
   
   return false;
}

/**
 * Moves a row specified by its model index up or down.
 * 
 * @param index Model index of the row to be moved.
 * @param down true if the row shall be moved down; false if it shall be moved up.
 * @returns true, if the row was successfully moved; false otherwise.
 */
bool ProjectTreeModel::moveRow(const QModelIndex &index, bool down)
{
   if (!index.isValid()) return false;

   auto* elem = getElement(index);
   auto* owner = getComposite(index.parent());
   int pos = index.row();
   if (down)
   { 
      if (pos == owner->count(false) - 1) return false;
      beginMoveRows(index.parent(), pos, pos, index.parent(), pos + 2);
      owner->moveDown(elem);
      endMoveRows();
      _root->project()->isModified(true);
      return true;
   }
   else
   { 
      if (pos == 0) return false;
      beginMoveRows(index.parent(), pos, pos, index.parent(), pos - 1);
      owner->moveUp(elem);
      endMoveRows();
      _root->project()->isModified(true);
      return true;
   }

   return false;
}

/** 
 * Gets the UML element stored under a specified model index as a UmlCompositeElement object. 
 * 
 * @param index Model index.
 * @returns The UML element stored or nullptr if the model index is invalid.
 */
UmlCompositeElement* ProjectTreeModel::getComposite(const QModelIndex& index) const
{
   return dynamic_cast<UmlCompositeElement*>(getElement(index));
}

/** 
 * Gets the UML element stored under a specified model index or the root element if the index is invalid. 
 * 
 * @param index Model index.
 * @returns The UML element stored or the UmlRoot object if index is invalid.
 */
UmlElement* ProjectTreeModel::getElement(const QModelIndex& index) const
{
   if (index.isValid()) 
   {
      auto* elem = static_cast<UmlElement*>(index.internalPointer());
      if (elem != nullptr) return elem;
   }

   return _root;
}

/** 
 * Gets the UML element stored under a specified model index as a UmlPackage object. 
 * 
 * @param index Model index.
 * @returns The UML element stored or nullptr if the model index is invalid.
 */
UmlPackage* ProjectTreeModel::getPackage(const QModelIndex& index) const
{
   return dynamic_cast<UmlPackage*>(getElement(index));
}

/** 
 * Recursively removes an element from the project.
 *
 * The function also removes all links connected to the element, as well as all child elements (if it is a composite
 * element, that is, an object of class UmlCompositeElement) from the project.
 * @param elem UML element to be removed from the project.
 */
void ProjectTreeModel::removeRecursive(UmlElement* elem)
{
   auto links = elem->links();
   for (auto victim : links)
   {
      removeRecursive(victim);
   }

   auto* comp = dynamic_cast<UmlCompositeElement*>(elem);
   if (comp != nullptr)
   {
      auto elements = comp->elements();
      for (auto victim : elements)
      {
         removeRecursive(victim);
      }
   }

   elem->dispose();

   auto* owner = elem->owner();
   owner->remove(elem);

   Q_ASSERT(elem->refCount() == 1);

   auto* project = _root->project();
   project->remove(elem);
}

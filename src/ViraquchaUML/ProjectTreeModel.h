//---------------------------------------------------------------------------------------------------------------------
// ProjectTreeModel.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class ProjectTreeModel.
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
#pragma once

#include "TreeIconProvider.h"

#include "UmlCommon.h"
#include "UmlClassifiers.h"

#include <QAbstractItemModel>

class ProjectTreeModel : public QAbstractItemModel
{
   Q_OBJECT
   typedef QAbstractItemModel super;
public: // Constructors
   ProjectTreeModel(UmlRoot* root, QObject* parent = nullptr);
   virtual ~ProjectTreeModel();

public: // Methods
   QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
   QModelIndex parent(const QModelIndex& child) const override;
   int rowCount(const QModelIndex& parent = QModelIndex()) const override;
   int columnCount(const QModelIndex& parent = QModelIndex()) const override;
   QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
   bool setData(const QModelIndex& index, const QVariant &value, int role = Qt::EditRole) override;
   Qt::ItemFlags flags(const QModelIndex& index) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

   bool insertRow(int position, const QModelIndex& parent, UmlElement* element);
   bool insertRow(const QModelIndex& parent, UmlElement* element);
   bool insertRow(const QModelIndex& parent, QString className, QString baseName);
   bool removeRow(const QModelIndex& index);
   bool removeRow(const QModelIndex& parent, UmlElement* element);
   bool moveRow(const QModelIndex& index, bool down);

   UmlCompositeElement* getComposite(const QModelIndex& index) const;
   UmlElement* getElement(const QModelIndex& index) const;
   UmlPackage* getPackage(const QModelIndex& index) const;

private:
   void removeRecursive(UmlElement* elem);

private: // Attributes
   UmlRoot*         _root;
   TreeIconProvider _icons;
};


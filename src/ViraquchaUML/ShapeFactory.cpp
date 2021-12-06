//---------------------------------------------------------------------------------------------------------------------
// ShapeFactory.cpp
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class ShapeFactory.
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
#include "ShapeFactory.h"
#include "DiagramScene.h"

#include "AssociationShape.h"
#include "ClassifierShape.h"
#include "CommentShape.h"
#include "DependencyShape.h"
#include "GeneralizationShape.h"
#include "LinkShape.h"
#include "PrimitiveTypeShape.h"
#include "RealizationShape.h"
#include "IShapeBuilder.h"

#include "UmlCommon.h"
#include "UmlClassifiers.h"

#include <QList>
#include <QListIterator>
#include <QMapIterator>

/**
 * @class ShapeFactory
 * @brief Creates Shape objects for diagrams.
 * @since 1.0
 * @ingroup GUI
 *
 * The ShapeFactory class is a factory method that creates Shape objects for the diagrams of ViraquchaUML. It is
 * implemented as a singleton.
 */

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the ShapeFactory class.
 */
ShapeFactory::ShapeFactory()
{
   subscribe(UmlClass::staticMetaObject.className(), new ClassifierShapeBuilder());
   subscribe(UmlDatatype::staticMetaObject.className(), new ClassifierShapeBuilder());
   subscribe(UmlEnumeration::staticMetaObject.className(), new ClassifierShapeBuilder());
   subscribe(UmlInterface::staticMetaObject.className(), new ClassifierShapeBuilder());
   subscribe(UmlSignal::staticMetaObject.className(), new ClassifierShapeBuilder());
   subscribe(UmlComment::staticMetaObject.className(), new CommentShapeBuilder());
   subscribe(UmlPrimitiveType::staticMetaObject.className(), new PrimitiveTypeShapeBuilder());

   subscribe(UmlAssociation::staticMetaObject.className(), new AssociationShapeBuilder());
   subscribe(UmlDependency::staticMetaObject.className(), new DependencyShapeBuilder());
   subscribe(UmlGeneralization::staticMetaObject.className(), new GeneralizationShapeBuilder());
   subscribe(UmlRealization::staticMetaObject.className(), new RealizationShapeBuilder());
   subscribe(UmlLink::staticMetaObject.className(), new LinkShapeBuilder());
   // TODO: add further IShapeBuilder instances here.
}

ShapeFactory::~ShapeFactory()
{
   QMapIterator<QString, IShapeBuilder*> iter(_builder);
   while (iter.hasNext())
   {
      iter.next();
      delete iter.value();
   }
}

//---------------------------------------------------------------------------------------------------------------------
// Implementation
//---------------------------------------------------------------------------------------------------------------------

/** Gets the one and only instance of the ShapeFactory class. */
ShapeFactory& ShapeFactory::instance()
{
   static ShapeFactory factory;
   return factory;
}

/**
 * Builds a Shape object for a given DiaEdge object.
 *
 * @param edge DiaEdge object to be used
 */
Shape* ShapeFactory::buildShape(DiaEdge* edge)
{
   Q_ASSERT(edge != nullptr);

   if (_builder.contains(edge->link()->className()))
   {
      return _builder[edge->link()->className()]->build(edge);
   }

   return nullptr;
}

/**
 * Builds a Shape object for a given DiaNode object.
 *
 * @param node DiaNode object to be used
 */
Shape* ShapeFactory::buildShape(DiaNode* node)
{
   Q_ASSERT(node != nullptr);

   if (_builder.contains(node->element()->className()))
   {
      return _builder[node->element()->className()]->build(node);
   }

   return nullptr;
}

/**
 * Builds a whole scene from a UmlDiagram instance.
 *
 * @param scene The DiagramScene object to be filled with shapes
 * @param diagram The UmlDiagram object providing data for the shapes
 */
void ShapeFactory::buildScene(DiagramScene* scene, UmlDiagram* diagram)
{
   Q_ASSERT(scene != nullptr);
   Q_ASSERT(diagram != nullptr);

   QListIterator<DiaNode*> nodes(diagram->nodes());
   while (nodes.hasNext())
   {
      auto* item = buildShape(nodes.next());
      if (item != nullptr)
      {
         item->setContextMenu(scene->contextMenu());
         scene->addItem(item);
      }
   }

   QListIterator<DiaEdge*> edges(diagram->edges());
   while (edges.hasNext())
   {
      auto* item = buildShape(edges.next());
      if (item != nullptr)
      {
         item->setContextMenu(scene->contextMenu());
         scene->addItem(item);
      }
   }
}

/**
 * Finds an IShapeBuilder object for a given class name.
 *
 * @param className Class name of the UmlElement object to find an IShapeBuilder object for
 * @return The IShapeBuilder object or nullptr if nothing was found
 */
IShapeBuilder* ShapeFactory::find(const QString& className)
{
   if (_builder.contains(className))
   {
      return _builder[className];
   }

   return nullptr;
}

/**
 * Subscribes an IShapeBuilder object with a class name.
 *
 * The IShapeBuilder objects are stored in a QMap using the class name as key. Therefore, the class name must be
 * unique.
 * @param className Class name used as key for the IShapeBuilder object to be subscribed
 * @param builder IShapeBuilder object to be subscribed
 */
void ShapeFactory::subscribe(const QString& className, IShapeBuilder* builder)
{
   Q_ASSERT(builder != nullptr);
   _builder.insert(className, builder);
}

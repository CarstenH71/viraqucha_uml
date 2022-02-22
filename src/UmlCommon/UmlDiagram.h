//---------------------------------------------------------------------------------------------------------------------
// UmlDiagram.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class UmlDiagram.
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

#include "umlcommon_globals.h"
#include "UmlElement.h"
#include "DiagramKind.h"
#include "IElementBuilder.h"
#include "IElementObserver.h"
#include "INamedElement.h"

class DiaNode;
class DiaEdge;

class UMLCOMMON_EXPORT UmlDiagram : public UmlElement, public INamedElement, public IElementObserver
{
   /// @cond
   Q_GADGET
   typedef UmlElement super;
   /// @endcond
public: // Constructors
   UmlDiagram();
   UmlDiagram(QUuid id);
   virtual ~UmlDiagram();

public: // Properties
   QString className() const override;
   QString diagramFile() const;

   bool isOpen() const;
   
   QString name() const override;
   void setName(QString value) override;

   QString comment() const override;
   void setComment(QString value) override;

   VisibilityKind visibility() const override;
   void setVisibility(VisibilityKind value) override;

   DiagramKind kind() const;
   void setKind(DiagramKind value);

   QList<DiaNode*> nodes() const;
   int nodeCount() const;

   QList<DiaEdge*> edges() const;
   int edgeCount() const;

   QString errorString() const;

public: // Methods
   DiaNode* addNode(UmlElement* elm);
   DiaEdge* addEdge(UmlLink* lnk);

   void remove(DiaNode* node);
   void remove(DiaEdge* edge);
   void removeById(QUuid id);

   bool contains(QUuid id);
   void clear();

   bool open();
   void close();
   bool save();

   void notify(UmlElement* sender, EventType type) override;

   QString toString() const override;

protected:
   void dispose(bool disposing) override;
   void serialize(QJsonObject& json, bool read, bool flat, int version) override;

private:
   void append(DiaNode* node);
   void append(DiaEdge* edge);
   void setErrorString(QString value);

private: // Attributes
   /// @cond
   struct Data;
   Data* data;
   /// @endcond
};

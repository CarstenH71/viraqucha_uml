//---------------------------------------------------------------------------------------------------------------------
// UmlElement.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class UmlElement.
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
#include "EventType.h"
#include "IElementObserver.h"
#include "ISerializable.h"
#include "IntrusivePtr.h"

#include <QObject>
#include <QString>
#include <QUuid>

#ifdef _DEBUG
// Used only in debug builds: 
// asserts that the project database is clean (all elements deleted) if the project is deleted.
void assertClean();
#endif

class UmlCompositeElement;
class UmlLink;
class UmlProject;

class UMLCOMMON_EXPORT UmlElement : public ISerializable
{
   ///@cond
   friend UmlProject;
   ///@endcond
public: // Constructors
   UmlElement();
   UmlElement(QUuid id);
   virtual ~UmlElement();

public: // Properties
   virtual QString className() const = 0;
   QString elementFile() const;

   QUuid identifier() const;

   QString keywords() const;
   void setKeywords(QString value);

   virtual bool isHidden() const;
   virtual bool isLink() const;

   QList<UmlLink*> links() const;

   UmlCompositeElement* owner() const;
   void setOwner(UmlCompositeElement* value);

   UmlProject* project() const;
   virtual void setProject(UmlProject* value);

   QList<IElementObserver*>& observers() const;

public: // Methods:
   void dispose();

   void linkto(UmlLink* link);
   void unlink(UmlLink* link);
   bool isLinkedTo(UmlLink* link);

   void serialize(QJsonObject& json, bool read, int version) override;

   void incRefCount();
   void decRefCount();
   quint32 refCount() const;

   virtual QString toString() const;

protected:
   virtual void dispose(bool disposing);
   void send(EventType type);

private: // Attributes
   ///@cond
   struct Data;
   Data* data;
   ///@endcond
};

typedef IntrusivePtr<UmlElement> UmlElementPtr;

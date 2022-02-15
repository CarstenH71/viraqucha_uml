//---------------------------------------------------------------------------------------------------------------------
// UmlProject.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class UmlProject.
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

#include <QFile>
#include <QJsonDocument>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QUuid>

class UmlRoot;

class UMLCOMMON_EXPORT UmlProject : public QObject
{
   ///@cond
   Q_OBJECT
   ///@endcond
public:
   UmlProject();
   virtual ~UmlProject();

public: // Properties
   QString author() const;
   void setAuthor(QString value);

   QString name() const;
   void setName(QString value);

   QString comment() const;
   void setComment(QString value);

   QList<UmlElement*> elements() const;
   UmlRoot* root() const;

   int count() const;

   QString artifactsFolder() const;
   QString codeFolder() const;
   QString diagramsFolder() const;
   QString elementsFolder() const;
   QString projectFolder() const;

   bool isModified() const;
   void isModified(bool value);

   QStringList primitiveTypes() const;
   QStringList stereoTypes() const;

   QString errorString() const;

public: // Methods
   UmlElement* insertNew(QString className);
   bool insert(UmlElement* entity);
   void remove(UmlElement* entity);

   bool contains(QUuid id);
   bool find(QUuid id, UmlElement** entity);
   UmlElement* take(QUuid id);

   bool create(QString path, QString name);
   bool load(QString filename);
   bool save(QString filename);

   void dispose();

   void removeFile(QString filename);
   void recoverFile(QString filename);

   void addPrimitiveType(QString name);
   void removePrimitiveType(QString name);
   void resetPrimitiveTypes();

   void addStereoType(QString name);
   void removeStereoType(QString name);
   void resetStereoTypes();

signals:
   void updateProgress(int percent);

private:
   bool isProject(QString filename);
   void setErrorString(QString error);

private: // Attributes
   ///@cond
   struct Data;
   Data* data;
   ///@endcond
};

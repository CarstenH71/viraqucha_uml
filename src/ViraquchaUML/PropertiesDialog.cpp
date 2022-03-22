//---------------------------------------------------------------------------------------------------------------------
// PropertiesDialog.cpp
//
// Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class PropertiesDialog.
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
#include "PropertiesDialog.h"
#include "CommentTab.h"
#include "GeneralTab.h"
#include "ClassifierTab.h"
#include "MultiplicityTab.h"
#include "AttributeTab.h"
#include "AttributesTab.h"
#include "OperationTab.h"
#include "OperationsTab.h"
#include "ParameterTab.h"
#include "ProjectTreeModel.h"
#include "TemplateParameterTab.h"

#include <QListIterator>

/**
 * @class PropertiesDialog
 * @brief The PropertiesDialog class implements a properties dialog for UML elements.
 * @since 0.1.0
 * @ingroup ViraquchaUML
 *
 * The PropertiesDialog shows all properties of an UML element distributed on one or several tab pages. Each tab pages
 * allows editing a set of properties. 
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the PropertiesDialog class.
 *
 * @param parent Parent widget.
 * @param model ProjectTreeModel object needed for undo/redo commands.
 * @param elem UmlElement object to be edited.
 */
PropertiesDialog::PropertiesDialog(QWidget* parent, ProjectTreeModel& model, UmlElement* elem)
: super(parent)
, _elem(elem)
, _model(model)
{
   ui.setupUi(this);
   connect(ui.buttonBox, &QDialogButtonBox::helpRequested, this, &PropertiesDialog::showHelp);
   
   if (elem->className() == UmlComment::staticMetaObject.className())
   {
      setWindowTitle(tr("Comment properties"));
      
      // Special case UML comment: no tab needed, since the only property 
      // of this element is its text.
      auto widget = new CommentTab(this, dynamic_cast<UmlComment*>(elem));
      ui.verticalLayout->removeWidget(ui.tabWidget);
      ui.verticalLayout->insertWidget(0, widget);
      _tabs.append(dynamic_cast<IPropertiesTab*>(widget));
   }
   else
   {
      // All other UML elements have several properties which must be 
      // distributed on several tabs:
      addTab(new GeneralTab(this, elem), tr("General"));
      if (elem->className() == UmlAttribute::staticMetaObject.className())
      { 
         createTabsFor(dynamic_cast<UmlAttribute*>(elem));
      }
      else if (elem->className() == UmlDatatype::staticMetaObject.className())
      { 
         createTabsFor(dynamic_cast<UmlDatatype*>(elem));
      }
      else if (elem->className() == UmlDiagram::staticMetaObject.className())
      {
         createTabsFor(dynamic_cast<UmlDiagram*>(elem));
      }
      else if (elem->className() == UmlClass::staticMetaObject.className())
      { 
         createTabsFor(dynamic_cast<UmlClass*>(elem));
      }
      else if (elem->className() == UmlEnumeration::staticMetaObject.className())
      {
         createTabsFor(dynamic_cast<UmlEnumeration*>(elem));
      }
      else if (elem->className() == UmlInterface::staticMetaObject.className())
      {
         createTabsFor(dynamic_cast<UmlInterface*>(elem));
      }
      else if (elem->className() == UmlOperation::staticMetaObject.className())
      { 
         createTabsFor(dynamic_cast<UmlOperation*>(elem));
      }
      else if (elem->className() == UmlPackage::staticMetaObject.className())
      {
         createTabsFor(dynamic_cast<UmlPackage*>(elem));
      }
      else if (elem->className() == UmlModel::staticMetaObject.className())
      {
         setWindowTitle("Model properties");
      }
      else if (elem->className() == UmlGeneralization::staticMetaObject.className())
      {
         setWindowTitle("Generalization properties");
      }
      else if (elem->className() == UmlRealization::staticMetaObject.className())
      {
         setWindowTitle("Realization properties");
      }
   }
}

PropertiesDialog::~PropertiesDialog()
{
}

void PropertiesDialog::createTabsFor(UmlAttribute* elem)
{
   setWindowTitle(tr("Attribute properties"));
   addTab(new AttributeTab(this, elem), tr("Details"));
   addTab(new MultiplicityTab(this, elem), tr("Multiplicity"));
}

void PropertiesDialog::createTabsFor(UmlDatatype* elem)
{
   setWindowTitle(tr("DataType properties"));
   addTab(new ClassifierTab(this, elem), tr("Details"));
   addTab(new AttributesTab(this, elem, _model), tr("Attributes"));
   addTab(new OperationsTab(this, elem, _model), tr("Operations"));
}

void PropertiesDialog::createTabsFor(UmlDiagram* elem)
{
   setWindowTitle(tr("Diagram properties"));
   // TODO: Details
}

void PropertiesDialog::createTabsFor(UmlClass* elem)
{
   setWindowTitle(tr("Class properties"));
   addTab(new ClassifierTab(this, elem), tr("Details"));
   addTab(new AttributesTab(this, elem, _model), tr("Attributes"));
   addTab(new OperationsTab(this, elem, _model), tr("Operations"));
   addTab(new TemplateParameterTab(this, elem), tr("Template Parameter"));
}

void PropertiesDialog::createTabsFor(UmlEnumeration* elem)
{
   setWindowTitle(tr("Enumeration properties"));
   addTab(new TemplateParameterTab(this, elem), tr("Template Parameter"));
   // TODO: Literale
}

void PropertiesDialog::createTabsFor(UmlInterface* elem)
{
   setWindowTitle(tr("Interface properties"));
   addTab(new ClassifierTab(this, elem), tr("Details"));
   addTab(new AttributesTab(this, elem, _model), tr("Attributes"));
   addTab(new OperationsTab(this, elem, _model), tr("Operations"));
   addTab(new TemplateParameterTab(this, elem), tr("Template Parameter"));
}

void PropertiesDialog::createTabsFor(UmlOperation* elem)
{
   setWindowTitle(tr("Operation properties"));
   addTab(new OperationTab(this, elem), tr("Details"));
   addTab(new ParameterTab(this, elem), tr("Parameter"));
   addTab(new MultiplicityTab(this, elem), tr("Multiplicity"));
   addTab(new TemplateParameterTab(this, elem), tr("Template Parameter"));
}

void PropertiesDialog::createTabsFor(UmlPackage* elem)
{
   setWindowTitle(tr("Package properties"));
   addTab(new TemplateParameterTab(this, elem), tr("Template Parameter"));
}

/** 
 * Adds a new tab to the tab widget as well as to the array of applyable tabs. 
 *
 * Note: the tab *must* implement interface IPropertiesTab, otherwise this function will assert.
 * @param tab QWidget to be added as a tab.
 * @param title Title of the tab.
 */
void PropertiesDialog::addTab(QWidget* tab, const QString& title)
{
   ui.tabWidget->addTab(tab, title);
   _tabs.append(dynamic_cast<IPropertiesTab*>(tab));
   
   // If we assert here, the tab is not derived from IPropertiesTab!
   Q_ASSERT(_tabs.last() != nullptr);
}

/** 
 * Shows online help for this dialog. 
 */
void PropertiesDialog::showHelp()
{
}

/** 
 * Handles the Accept button of the dialog and applies all changes to the ViraquchaUML data model. 
 */
void PropertiesDialog::accept()
{
   bool ok = true;
   
   int index = 0;
   for (index = 0; index < _tabs.size() && ok; ++index)
   {
      ok &= _tabs[index]->validateInput();
   }

   if (ok)
   {
      for (index = 0; index < _tabs.size(); ++index)
      {
         _tabs[index]->applyChanges();
      }

      super::accept();
   }
   else
   {
      ui.tabWidget->setCurrentIndex(index);
   }
}

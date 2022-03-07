//---------------------------------------------------------------------------------------------------------------------
// ToolBoxManager.cpp
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class ToolBoxManager.
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
#include "ToolBoxManager.h"
#include "IconProvider.h"

#include <QGridLayout>
#include <QLabel>

/**
 * @class ToolBoxManager
 * @brief Manages the toolbox of ViraquchaUML
 * @since 0.1.0
 * @ingroup ViraquchaUML
 *
 * The ToolBoxManager class manages the toolbox of ViraquchaUML. It provides functions for adding buttons to the 
 * toolbox and translates signals sent by the toolbox to fit with the DiagramPage slots.
 *
 * The toolbox of ViraquchaUML shows icons for inserting new UML elements in diagrams. Currently the overall layout
 * of the toolbox is a grid layout where all buttons are laid out in two columns and several rows (depending on the
 * count of buttons) per tab. The ToolBoxManager class allows both, adding new tabs and buttons.
 *
 * Tabs are used to categorize the buttons. For example, buttons which create Classifier elements (Class, DataType,
 * Instance) can be put into a tab called &quot;Classifier&quot;, whereas buttons which create Relationship elements
 * (Association, Generalization...) can be put into another tab called &quot;Relationship&quot;.
 */

//---------------------------------------------------------------------------------------------------------------------
// Constructors
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the ToolBoxManager class.
 * 
 * @param parent Parent object.
 * @param toolbox QToolBox object to be managed.
 */
ToolBoxManager::ToolBoxManager(QObject* parent, QToolBox* toolbox)
: super(parent)
, _toolbox(toolbox)
, _group(new QButtonGroup(this))
, _row(0)
, _col(0)
{
   _group->setExclusive(false);
   connect(_group, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &ToolBoxManager::handleButton);

   Q_ASSERT_X(_toolbox != nullptr, "ToolBoxManager", "Pointer to QToolBox is null");
   _toolbox->setMinimumWidth(100);
}

ToolBoxManager::~ToolBoxManager()
{
   delete _group;
}

//---------------------------------------------------------------------------------------------------------------------
// Implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Adds a new tab to the tool box.
 *
 * Must be called once for each set of buttons to be added to the tool box.
 * @param name Name of the new tab.
 */
void ToolBoxManager::addTab(QString name)
{
   _row = 0;
   _col = 0;

   _layout = new QGridLayout();
   
   auto* tab = new QWidget();
   tab->setLayout(_layout);
   _toolbox->addItem(tab, name);
}

/**
 * Adds a new button decorated with an icon to the tool box.
 *
 * The function looks up an icon from the program resources in medium (24x24 pixels) size using the class name given
 * and then adds it to the toolbar using the display name given.
 * @param dispName Display name of the button.
 * @param className Class name of the UmlElement class that shall be created by clicking the button.
 */
void ToolBoxManager::addButton(int id, QString dispName, QString className)
{
   addButton(id, dispName, className, IconProvider::getIcon(className, IconSize::Medium));
}

/**
 * Adds a new button decorated with a given icon to the tool box.
 *
 * The function uses the icon given to decorate the button to be added. It then adds it to the toolbar using the
 * display name given. The class name is later used for creating the specific UmlElement object when clicking the
 * button.
 * @param dispName Display name of the button.
 * @param className Class name of the UmlElement class that shall be created by clicking the button.
 * @param icon Icon to decorate the button with.
 */
void ToolBoxManager::addButton(int id, QString dispName, QString className, QIcon icon)
{
   // Group *must* exist - if not then we have some serious problems!
   Q_ASSERT(_group != nullptr);

   // Identifier must be unique!
   Q_ASSERT(!_classes.contains(id));
   _classes.insert(id, className);

   // Create a new tool box button and add it to the button group:
   auto* button = new QToolButton();
   button->setIcon(icon);
   button->setIconSize(QSize(26, 26));
   button->setCheckable(true);
   _group->addButton(button, id);

   // Create a grid layout for the button and a label positioned at the bottom of the button:
   auto* grid = new QGridLayout();
   grid->setSizeConstraint(QLayout::SetFixedSize);
   grid->addWidget(button, 0, 0, Qt::AlignHCenter);
   grid->addWidget(new QLabel(dispName), 1, 0, Qt::AlignCenter);

   // Create the widget holding both, the button and the label:
   auto* widget = new QWidget();
   widget->setLayout(grid);
   _layout->addWidget(widget, _row, _col, Qt::AlignCenter);

   // Increment row and column number:
   if (_col == KMaxColumns - 1)
   {
      _col = 0;
      ++_row;
   }
   else
   {
      ++_col;
   }
}

/**
 * Resets a button.
 */
void ToolBoxManager::resetButton()
{
   // Group *must* exist - if not then we have some serious problems!
   Q_ASSERT(_group != nullptr);
   if (_group->checkedButton() != nullptr)
   {
      _group->checkedButton()->setChecked(false);
   }
}

/** 
 * Handles signal buttonClicked of the group box. 
 * 
 * @param id Identifier of the button.
 */
void ToolBoxManager::handleButton(int id)
{
   // Group *must* exist - if not then we have some serious problems!
   Q_ASSERT(_group != nullptr);

   // Identifier must be contained in the map!
   Q_ASSERT(_classes.contains(id));
   
   // Unchecke all other buttons except the clicked one:
   QListIterator<QAbstractButton*> iter(_group->buttons());
   while (iter.hasNext())
   {
      auto* button = iter.next();
      if (_group->id(button) != id)
      {
         button->setChecked(false);
      }
   }

   emit buttonClicked(id, _classes[id]);
}

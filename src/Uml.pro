#---------------------------------------------------------------------------------------------------------------------
# Uml.pro
#
# Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
#
# Description: Qt root project file for the ViraquchaUML program.
#
# *******************************************************************************************************************
# *                                                                                                                 *
# * This file is part of ViraquchaUML.                                                                              *
# *                                                                                                                 *
# * ViraquchaUML is free software; you can redistribute it and/or modify it under the terms of the GNU General      *
# * Public License as published by the Free Software Foundation; either version 3.0 of the License, or (at your     *
# * option) any later version.                                                                                      *
# *                                                                                                                 *
# * ViraquchaUML is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the      *
# * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License     *
# * for more details.                                                                                               *
# *                                                                                                                 *
# * You should have received a copy of the GNU General Public License along with ViraquchaUML; if not, see          *
# * http://www.gnu.org/licenses/gpl                                                                                 *
# *                                                                                                                 *
# *******************************************************************************************************************
#
# See https://github.com/CarstenH71/viraqucha_uml for the latest version of this software.
#---------------------------------------------------------------------------------------------------------------------

TEMPLATE = subdirs
SUBDIRS  = \
  GuiCommon \
  GuiResources \
  UmlCommon \
  UmlClassifiers \
  ViraquchaUML

UmlClassifiers.depends = UmlCommon
ViraquchaUML.depends = GuiCommon GuiResources UmlCommon UmlClassifiers

ViraquchaUML
================================================================================

Introduction
------------

ViraquchaUML is an open source modelling tool for software architects as well as
software engineers based on the Unified Modelling Language 2.5.1. It is entirely 
written in C++ using the open source library Qt and should therefore work on all 
major operating systems supported by Qt (Android/Linux, MacOS and Windows).

ViraquchaUML uses JSON files for serialization of UML data instead of a database 
system. This has the advantage that ViraquchaUML projects can be compared or 
merged by version control systems, but the disadvantage that UML projects 
(currently) cannot be modified by multiple users.

Please note that the programme is still in a very early alpha phase. Many 
functions are missing or not yet fully developed, and no help or further 
documentation (other than the API documentation) is available yet. Furthermore,
there is no setup programme or installation script available.

So if you still want to try the programme, you will have to build it yourself. 
How to do this is briefly outlined in the next section.

Building
--------

ViraquchaUML is currently available as source code only. That is, you need to
build it yourself if you want to try it out. Since it is written in plain C++
you need one of the following compilers:

* Linux: GCC 5.1 or newer, Clang 2.5 or newer
* MacOS: Apple Clang (latest version)
* Windows: Visual C++ 2017 (MSVC 19.x) or Mingw-w64 (MSYS) 5.x

Then you need the Qt library, version 5.12.8 or 5.15 and CMake 3.16 or newer.
To build the programme, run cmake-gui on the CMakeLists.txt file in the /src
subdirectory and configure source and build directory. Then generate the
Makefiles (see documentation of cmake-gui), open a console (Linux) or command 
window (Windows), go to the build directory and run make. If no failures
occurred, you can find and run the executable in the /bin subdirectory.

License
-------

Copyright (C) 2017-2021 Carsten Huber

ViraquchaUML is free software: you can redistribute it and/or modify it under 
the terms of the GNU General Public License as published by the Free Software 
Foundation, either version 3 of the License, or (at your option) any later 
version.

ViraquchaUML is distributed in the hope that it will be useful, but WITHOUT ANY 
WARRANTY; without even the implied warranty of or FITNESS FOR A PARTICULAR 
PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with 
ViraquchaUML. If not, see <https://www.gnu.org/licenses/>.

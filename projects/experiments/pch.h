/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki_toolkit.git
@file    /projects/experiments/pch.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <http://calemccollough.github.io>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once

#ifdef ASSEMBLE_DYNAMIC_LIB  // Exqmple doesn't need to assemble the DLL to blow
                             // up.
#ifdef LIB_EXPORT
#define LIB_MEMBER __declspec(dllexport)
#else
#define LIB_MEMBER __declspec(dllimport)
#endif
#else
#define LIB_MEMBER  //< Still blows up when nothing is here.
#endif
#include <iostream>

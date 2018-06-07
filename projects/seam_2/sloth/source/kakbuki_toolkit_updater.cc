/** Kabuki Toolkit
    @version 0.x
    @file    ~/projects/seam_2/kabuki_toolkit_updater/kabuki_toolkit_updater.cc
    @author  Cale McCollough <https://calemccollough.github.io>
    @license Copyright (C) 2014-8 Cale McCollough <calemccollough@gmail.com>;
             All right reserved (R). Licensed under the Apache License, Version 
             2.0 (the "License"); you may not use this file except in 
             compliance with the License. You may obtain a copy of the License 
             [here](http://www.apache.org/licenses/LICENSE-2.0). Unless 
             required by applicable law or agreed to in writing, software
             distributed under the License is distributed on an "AS IS" BASIS,
             WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
             implied. See the License for the specific language governing 
             permissions and limitations under the License. */

#pragma once
#include<stdafx.h>
#include "../../../../library/crabs/global.h"
#include "../../../../library/kabuki/sloth/global.h"

int main (int arg_count, const char* args) {

    COUT << "\nSloth: ";
    if (arg_count > 1) {
        COUT << "arg_count";
        for (int i = 0; i < arg_count; ++i) {
            COUT << '\n' << args;
        }
    }
    COUT << '\n';
    system ("PAUSE");
    return 0;
}
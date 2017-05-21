/** Kabuki Theater
    @file    /.../KabukiTheater-Impl/Workspace/Workspace.cpp
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough <https://calemccollough.github.io>

                            All right reserved  (R).

        Licensed under the Apache License, Version 2.0  (the "License"); you may
        not use this file except in compliance with the License. You may obtain
        a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

        Unless required by applicable law or agreed to in writing, software
        distributed under the License is distributed on an "AS IS" BASIS,
        WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
        See the License for the specific language governing permissions and
        limitations under the License.
*/

#include <_VEnv/Workspace.hpp>

namespace _VEnv {

Workspace::Workspace ()
//:   controlSurfaces ()
{
}

Workspace::Workspace  (const Workspace& O) 
//:   controlSurfaces  (O.controlSurfaces)
{

}

Workspace::~Workspace ()
{
    for  (int i = 0; i < controlSurfaces.size; ++i)
        delete controlSurfaces[i];
}

void Workspace::Add (Devices::ControlSurface* newControlSurface)
{
    if  (newControlSurface == nullptr)
        return;

    controlSurfaces.add  (newControlSurface);
}

int Workspace::getNumControlSurfaces ()
{
    return controlSurfaces.count ();
}

}   //< namespace VEnv

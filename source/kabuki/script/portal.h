/** kabuki::script
    @version 0.x
    @file    ~/source/kabuki/script/include/portal.h
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough <calemccollough@gmail.com>;
             All right reserved (R). Licensed under the Apache License, Version 
             2.0 (the "License"); you may not use this file except in 
             compliance with the License. You may obtain a copy of the License 
             [here](http://www.apache.org/licenses/LICENSE-2.0). Unless 
             required by applicable law or agreed to in writing, software
             distributed under the License is distributed on an "AS IS" BASIS,
             WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
             implied. See the License for the specific language governing 
             permissions and limitations under the License.
*/

#ifndef SCRIPT_PORTAL_H
#define SCRIPT_PORTAL_H

#include "window.h"

namespace _ {

/** A slot in Door that connects two or more Chinese Rooms.
    Examples of common Portal are UART, Dual-UART, SPI, I2C, Quad SPI, 
    TCP/HTTP/UDP, Bluetooth, CAN. */
struct KABUKI Portal {

    /** Feeds tx messages through the a without scanning them. */
    virtual Expression* GetSlot () = 0;

    /** Pulls rx messages through the a and runs them through the scanner. */
    virtual Window* GetWindow () = 0;
};
}       //< namespace _
#endif  //< SCRIPT_PORTAL_H

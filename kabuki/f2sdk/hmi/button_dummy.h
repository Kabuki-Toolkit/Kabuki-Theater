/* Kabuki Toolkit
@file    ~/source/hmi/hmi_dummy_button.h
@author  Cale McCollough <calemccollough.github.io>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough@gmail.com>;
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

#pragma once
#include <stdafx.h>
#if SEAM_MAJOR > 2 || SEAM_MAJOR == 2 && SEAM_MINOR >= 0
#ifndef HEADER_FOR_KT_HMI_DUMMYBUTTON
#define HEADER_FOR_KT_HMI_DUMMYBUTTON

#include "button.h"
#include "button_event.h"

namespace _ {

/* A dummy Button that doesn't do anything. */
class KABUKI ButtonDummy : public Button {
 public:
  //< Creates a ButtonDummy with the initLabel.
  ButtonDummy(const char* initLabel = "");

  //< Action that gets performed when this button gets pressed.
  void Press(ButtonEvent buttonEvent);

  //< Action that gets performed when this button gets depressed.
  void Depress(ButtonEvent buttonEvent);

  //< Action that gets performed when this button gets double pressed.
  void DoublePress(ButtonEvent buttonEvent);

};      //< class ButtonDummy
}       // namespace _
#endif  //< HEADER_FOR_KT_HMI_DUMMYBUTTON
#endif  //< #if SEAM_MAJOR > 2 || SEAM_MAJOR == 2 && SEAM_MINOR >= 0
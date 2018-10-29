/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki-toolkit.git
@file    /kabuki/crabs/crabs_exceptions.cc
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>
#if SEAM >= _0_0_4_0__00_00
// Dependencies:
#include "interrupts.h"
// End dependencies.
#if USING_CRABS_INTERRUPTS
#include <cassert>

namespace _ {

#if CRABS_TEXT
const char* RoomCrashException::what() const throw() {
  return "External crash";
}
#endif

}  // namespace _
#endif  //< USING_CRABS_INTERRUPTS
#endif  ///< #if SEAM >= _0_0_4_0__00_00
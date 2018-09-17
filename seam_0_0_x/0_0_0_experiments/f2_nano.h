/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki-toolkit.git
@file    ~/seam_0_0_x/0_0_0_experiments/f2_nano.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <stdafx.h>

#ifndef INCLUDED_KABUKI_AI_F2NANO
#define INCLUDED_KABUKI_AI_F2NANO 1

#define ASSERT(condition) \
  if (Assert(condition)) _::AssertHandle(__FILE__, __LINE__)

namespace _ {

void Print(char c = '\n');
void Print(const char* string);
inline int ToUpper(int c) {  // For some reason this won't compile in the .cc???
  if ((c >= 'a') && (c <= 'z')) return c - ('a' - 'A');
  return c;
}
inline int CInKey();
inline bool CInState(int vk_code);
void Pause(const char* message = nullptr);
bool Assert(bool condition);
bool AssertHandle(const char* file, int line);

}  // namespace _

#endif  //< #ifndef INCLUDED_KABUKI_AI_F2NANO

/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki-toolkit.git
@file    ~/seam_0_0_x/0_0_0_experiments/maze.cc
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

#include "f2_nano.h"

#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <iostream>

namespace _ {

void Print(const char* string) { std::cout << string; }

void Print(char c) { std::cout << c; }

int ToUpper(int c) {  // For some reason this won't compile in the .cc???
  if ((c >= 'a') && (c <= 'z')) return c - ('a' - 'A');
  return c;
}

int CInKey() { return _getch(); }

bool CInState(int vk_code) { return GetKeyState(vk_code); }

void Pause(const char* message) {
  if (message) {
    Print();
    Print(message);
  }
  Print("\nPress any key to continue...");
  while (CInKey() < 0)
    ;
}
bool Assert(bool condition) { return !condition; }

bool AssertHandle(const char* file, int line) {
  std::cout << "\nAssertion failed at line " << line << " in \"" << file;
  Pause();
  return true;
}

}  // namespace _

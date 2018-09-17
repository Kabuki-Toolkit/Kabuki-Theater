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

#include "maze.h"

#include "f2_nano.h"

#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <iostream>

using namespace std;

namespace _ {

const char** Maze1(int& height) {
  static const char* kMaze[] = {
      "         +--+",  //
      "+--------+  |",  //
      "| @         |",  //
      "| *+-- --+  |",  //
      "|  |     |  |",  //
      "|  |     |  |",  //
      "|  | +-+ |  |",  //
      "|  |X| | |  |",  //
      "|  +-+ | |  |",  //
      "|      | |  |",  //
      "|  +---+ |  |",  //
      "|  |        |",  //
      "|  |        |",  //
      "|  +-----   |",  //
      "|           |",  //
      "+-----------+",  //
  };
  height = 16;
  return kMaze;
}

char* PreprocessMaze(MazeLoader get_maze, int& width, int& height) {
  cout << "\n1.) Load the maze from a GetMaze function.";
  int y;
  const char** strings = get_maze(y);
  const char* read = strings[0];
  int x = 0;
  while (*read++) ++x;
  cout << "\n  width:" << x << " height:" << y << '\n';
  if (!x || !y) {
    cout << "\nERROR: width and/or height can't be zero!";
    return nullptr;
  }
  width = x;

  char *tiles = new char[x * y + 1], *cursor = tiles;
  cout << "\n2.) Packing strings into maze.\n";
  for (int j = 0; j < y; ++j) {
    cout << '\n';
    read = strings[j];
    for (int k = 0; k < x; ++k) {
      char c = (char)ToUpper(*read++);
      cout << c;
      *cursor++ = c;
    }
  }
  return tiles;
}

Maze::Maze(MazeLoader get_maze, int number) : number(number) {
  tiles = PreprocessMaze(get_maze, width, height);
}

Maze::Maze(char* tiles, int width, int height, int number)
    : tiles(tiles), width(width), height(height), number(number) {}

Maze::~Maze() {
  if (tiles) delete[] tiles;
}

bool Maze::IsValid() {
  return tiles == nullptr && width > 0 && height > 0 && number > 0;
}

char Maze::Get(int x, int y) {
  if (x < 0 || y < 0 || x >= height || y >= height) return 0;
  return tiles[y * width + x];
}

bool Maze::Set(int x, int y, char c) {
  if (x < 0 || y < 0 || x >= height || y >= height) return false;
  tiles[y * width + x] = c;
  return true;
}

bool Maze::CanMove(int x, int y) { return Get(x, y) == ' '; }

bool Maze::IsEnd(int x, int y) {
  char tile = Get(x, y);
  return tile == 'F';
}

bool Maze::Find(int& x, int& y, char c) {
  if (c >= 'a' && c <= 'z') c -= 'z' - 'Z';
  char* cursor = tiles;
  for (int j = 0; j < height; ++j) {
    for (int k = 0; k < width; ++k) {
      char d = *cursor++;
      if (c == d) {
        x = k;
        y = j;
        *(--cursor) = ' ';  //< Remove the char.
        return true;
      }
    }
  }
  x = y = -1;
  return false;
}

bool Maze::FindStart(int& x, int& y, int& dx, int& dy) {
  if (!Find(x, y, '@')) return false;
  if (!Find(dx, dy, '*')) return false;
  dx = x - dx;
  dy = y - dy;
  if (dx < -1 || dx > 1 || dy < -1 || dy > 1) return false;
  return true;
}

bool Maze::FindFinish(int& x, int& y) { return Find(x, y, 'F'); }

void Maze::Print(int iteration) {
  cout << '\n';
  for (int i = 0; i < width; ++i) cout << '-';
  cout << "\nMaze " << number;
  if (iteration) cout << " iteration:" << iteration;
  char* cursor = tiles;
  for (int y = 0; y < height; ++y) {
    cout << '\n';
    for (int x = 0; x < width; ++x) {
      cout << *cursor++;
    }
  }
}

int XYVector(int direction, int& dy) {
  switch (direction) {
    case kXYRight: {
      dy = 0;
      return 1;
    }
    case kXYUpperRight: {
      dy = -1;
      return 0;
    }
    case kXYUp: {
      dy = 0;
      return 0;
    }
    case kXYUpperLeft: {
      dy = -1;
      return -1;
    }
    case kXYLeft: {
      dy = 0;
      return -1;
    }
    case kXYLowerLeft: {
      dy = 1;
      return -1;
    }
    case kXYDown: {
      dy = 1;
      return 0;
    }
    case kXYLowerRight: {
      dy = 1;
      return 1;
    }
  }
  dy = 0;
  return 0;
}
}  // namespace _

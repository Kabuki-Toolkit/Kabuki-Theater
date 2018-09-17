/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki-toolkit.git
@file    ~/seam_0_0_x/0_0_0_experiments/maze.h
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

#ifndef INCLUDED_KABUKI_AI_MAZE
#define INCLUDED_KABUKI_AI_MAZE 1

namespace _ {

// Function pointer for getting static mazes and their height.
typedef const char** (*MazeLoader)(int& height);

// Example maze with function pointer.
const char** Maze1(int& height);

char* PreprocessMaze(MazeLoader get_maze, int& width, int& height);

/*
# Allowed Moves
Our ASCII robot car takes up 2 characters that cannot be diagonal. */
struct Maze {
  char* tiles;
  int width, height, number;
  Maze(MazeLoader get_maze = Maze1, int number = 1);
  Maze(char* tiles, int width, int height, int number);
  bool IsValid();
  ~Maze();
  char Get(int x, int y);
  bool Set(int x, int y, char c);
  bool CanMove(int x, int y);
  bool IsEnd(int x, int y);
  bool Find(int& x, int& y, char c);
  inline bool FindStart(int& x, int& y, int& dx, int& dy);
  inline bool FindFinish(int& x, int& y);
  void Print(int iteration = 0);
};

enum {
  kXYRight = 0,   //< Direction Right @ 0 degrees.
  kXYUpperRight,  //< Direction Upper right @ 45 degrees.
  kXYUp,          //< Direction Up @ 90 degrees.
  kXYUpperLeft,   //< Direction Upper left @ 135 degrees.
  kXYLeft,        //< Direction Left @ 180 degrees.
  kXYLowerLeft,   //< Direction Lower left @ 225 degrees.
  kXYDown,        //< Direction Down @ 270 degrees.
  kXYLowerRight,  //< Direction Lower right @ 315 degrees.
  kXYCenter,      //< No directions.
};

/* Gets the dx and dy values for the given direction.
@return DeltaX.
@param  direction The direction.
@param  dy        DeltaY. */
inline int XYVector(int direction, int& dy);

}  // namespace _
#endif  //< #ifndef INCLUDED_KABUKI_AI_MAZE

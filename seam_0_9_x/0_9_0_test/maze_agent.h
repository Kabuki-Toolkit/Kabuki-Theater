/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki-toolkit.git
@file    ~/seam_0_0_x/0_0_0_experiments/maze_agent.h
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

#ifndef INCLUDED_KABUKI_AI_MAZEAGENT
#define INCLUDED_KABUKI_AI_MAZEAGENT 1

#include "maze.h"

namespace _ {

struct MazeAgent;

typedef int (*PolicyPilot)(MazeAgent* agent);

int PolicyPilotManual(MazeAgent* agent);

int PolicyPilotDepthFirstRoundRobin(MazeAgent* agent);

/* Simple stack AI agent for solving simple mazes with 8 directions.
In order to better pack the data, the visited directions in the stack search
are that each quadrant contains two paths where quad_n is zero if neither path
has been traversed, it's -1 if the lower value angle path has been visited and
+1 if both nodes have been visited.
Speed will always be either -1, 0, or +1, and direction will always be
*/
struct MazeAgent {
  struct State {
    enum {
      kShuttingDown = 0,  //< Exiting application.
      kInit,              //< Initial state when booting.
      kWaiting,           //< Not doing anything.
      kTurning,           //< Turning.
      kMoving,            //< Moving without stepping.
      kStuck,             //< Stuck on this path.
      kConfused,          //< Can't find a solution.
    };

    static inline const char* Label(int state);

    int state, x, y, direction, speed;
    int8_t quad_1, quad_2, quad_3, quad_4;
    State();
    State(const State& other);
    void Set(int new_x, int new_y, int new_state = kInit, int new_dx = 0,
             int new_dy = 0);
    bool DetectLoop(int other_x, int other_y);
    inline const char* Label();
  };
  struct Point2D {
    int x, y;
    Point2D();
    Point2D(State& state);
    Point2D(const Point2D& other);
  };
  enum { kStackSize = 1024 };

  PolicyPilot pilot, autopilot;
  State state, states[kStackSize];
  int stack_height, iteration, shortest_height, init_dx, init_dy;
  Maze maze;
  Point2D shortest_path[kStackSize];

  MazeAgent(PolicyPilot pilot = PolicyPilotManual, MazeLoader get_maze = Maze1,
            int maze_number = 1);
  bool IsValid();
  bool ChangeState(int new_state);
  bool Move(int x, int y, int new_x, int new_y);
  bool IsLoop(int new_x, int new_y);
  int Update();
  void TurnLeft();
  void TurnRight();
  void AutopilotToggle();
  void Decelerate();
  void Accellerate();
  void ShutDown();
  void SetAutopilot(PolicyPilot new_pilot);
  void Print();
};

int PolicyPilotManual(MazeAgent* agent);
int PolicyPilotDepthFirstRoundRobin(MazeAgent* agent);
}  // namespace _

#endif  //< #ifndef INCLUDED_KABUKI_AI_MAZEAGENT

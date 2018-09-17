/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki-toolkit.git
@file    ~/seam_0_0_x/0_0_0_experiments/maze_agent.cc
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

#include "maze_agent.h"

#include "f2_nano.h"

namespace _ {

MazeAgent::State::State() {}

MazeAgent::State::State(const State& other) {
  state = other.state;
  x = other.x;
  y = other.y;
  direction = other.direction;
  speed = other.speed;
}
void MazeAgent::State::Set(int new_x, int new_y, int new_state, int new_dx,
                           int new_dy) {
  state = new_state;
  x = new_x;
  y = new_y;
  direction = new_dx;
  direction = new_dy;
}
bool MazeAgent::State::DetectLoop(int other_x, int other_y) {
  return x == other_x && y == other_y;
}

inline const char* MazeAgent::State::Label(int state) {
  const char* kLabels[] = {"Shutting down", "Initializing", "Waiting",
                           "Turning",       "Moving",       "Stuck",
                           "Confused"};
  return kLabels[state];
};

inline const char* MazeAgent::State::Label() { return Label(state); }

MazeAgent::Point2D::Point2D() {}

MazeAgent::Point2D::Point2D(State& state) : x(state.x), y(state.y) {}

MazeAgent::Point2D::Point2D(const Point2D& other) : x(other.x), y(other.y) {}

MazeAgent::MazeAgent(PolicyPilot pilot, MazeLoader get_maze, int maze_number)
    : state(),
      pilot(pilot),
      autopilot(pilot),
      stack_height(0),
      iteration(0),
      shortest_height(kStackSize),
      init_dx(kXYUp),
      init_dy(0),
      maze(get_maze, maze_number) {
  int x, y, dx, dy;
  maze.FindStart(x, y, dx, dy);
  state.Set(x, y, dx, dy);
}

bool MazeAgent::IsValid() { return maze.IsValid(); }

bool MazeAgent::ChangeState(int new_state) {
  int l_stack_height = stack_height;
  if (l_stack_height >= kStackSize) return false;

  switch (new_state) {
    case State::kWaiting: {
      state.direction = -1;
      state.speed = 0;
      return true;
    }
  }
  return false;
}

bool MazeAgent::Move(int x, int y, int new_x, int new_y) {
  if (!maze.Set(x, y, ' ') || !maze.Set(new_x, new_y, 'S')) return false;
  maze.Print(++iteration);
  return true;
}

bool MazeAgent::IsLoop(int new_x, int new_y) {
  for (int i = stack_height - 1; i > 0; --i) {
    if (states[i].DetectLoop(new_x, new_y)) {
      return true;
    }
  }
  return false;
}

int MazeAgent::Update() {
  int l_state = pilot(this);
  ChangeState(l_state);
  return l_state;
}

void MazeAgent::TurnLeft() {
  int direction = state.direction + 1;
  if (direction >= kXYCenter) direction = kXYRight;
  int dy, dx = XYVector(direction, dy), x = state.x, y = state.y,
          new_x = x + dx, new_y = y + dy;
  if (!maze.CanMove(new_x, new_y)) return;
  ASSERT(stack_height <= kStackSize);
}

void MazeAgent::TurnRight() {
  int direction = state.direction - 1;
  if (direction < 0) direction = kXYLowerRight;
  int dy, dx = XYVector(direction, dy), x = state.x, y = state.y,
          new_x = x + dx, new_y = y + dy;
  if (!maze.CanMove(new_x, new_y)) return;
  ASSERT(stack_height <= kStackSize);
}

void MazeAgent::AutopilotToggle() {
  PolicyPilot manual_pilot = PolicyPilotManual;
  pilot = (pilot == manual_pilot) ? autopilot : manual_pilot;
}

void MazeAgent::Decelerate() {
  int speed = state.speed;
  if (speed < 0) return;
  state.speed = speed - 1;
}

void MazeAgent::Accellerate() {
  int speed = state.speed;
  if (speed > 0) return;
  state.speed = speed + 1;
}

void MazeAgent::ShutDown() { state.state = State::kShuttingDown; }

void MazeAgent::SetAutopilot(PolicyPilot new_pilot) {
  ASSERT(new_pilot);
  autopilot = new_pilot;
}

void MazeAgent::Print() {
  _::Print("\nAgent:");
  if (pilot == PolicyPilotManual) {
    _::Print(" Autopilot.");
    if (pilot == PolicyPilotDepthFirstRoundRobin) {
      _::Print("Depth-first Round-robin.");
    } else {
      _::Print("unknown.");
    }
  } else {
    _::Print(" Puppet.");
  }
  _::Print("\n state:");
  _::Print(state.Label());
  _::Print();
}

int PolicyPilotManual(MazeAgent* agent) { return agent->state.state; }

int PolicyPilotDepthFirstRoundRobin(MazeAgent* agent) {
  // PEAS: Performance Measurement, Environment, Actuators,
  //       Sensors
  int l_state = agent->state.state;
  if (l_state <= MazeAgent::State::kWaiting) return l_state;

  if (l_state == MazeAgent::State::kWaiting) return l_state;

  int x = agent->state.x, y = agent->state.y;

  if (agent->maze.IsEnd(x, y)) {
    if (agent->stack_height < agent->shortest_height) {
      agent->shortest_height = agent->stack_height;
      return MazeAgent::State::kWaiting;
      // You need to how copy the state stack somewhere and
      // so you compare this path to the others to find the
      // shortest_path.
    }
  }
  // Measurement: N/A because all movements are in units of 1.
  // Environment:
  int dx = agent->state.direction, dy = agent->state.speed;
  if (agent->maze.CanMove(x + dx, y + dy)) {
    // Keep going the same direction until we hit a wall.
    agent->Move(x, y, x + dx, y + dy);
    return l_state;
  }

  return ++l_state;
}

}  // namespace _

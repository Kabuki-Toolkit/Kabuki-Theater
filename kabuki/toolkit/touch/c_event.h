/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki_toolkit.git
@file    /kabuki_toolkit/av/t_event.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#if SEAM >= KABUKI_TOOLKIT_AV_1
#ifndef KABUKI_TOOLKIT_AV_EVENT
#define KABUKI_TOOLKIT_AV_EVENT

#include "t_config.h"

namespace _ {

/* A event with an ASCII TSS (Time Subsecond) timestamp. */
class Event {
 public:
  /* Default constructor. */
  Event();

  /* Virtual destructor. */
  virtual ~Event();

  /* gets the timestamp of the Event. */
  TSS GetTimestamp();

  /* Triggers the event. */
  virtual void Trigger() = 0;

  /* Prints this object to a string. */
  template<typename Printer> 
  virtual Printer& Print(Printer& o) const = 0;

 private:
  timestamp_t timestamp;  //< Event timestamp in microseconds.
};

}  // namespace _
#endif  //< KABUKI_TOOLKIT_AV_EVENT
#endif  //< #if SEAM >= KABUKI_TOOLKIT_AV_1
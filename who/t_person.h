/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.git
@file    /who/t_person.h
@author  Cale McCollough <<https://calemccollough.github.io>>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>
#if SEAM >= kabuki.toolkit_WHO_1
#ifndef kabuki.toolkit_WHO_PERSON
#define kabuki.toolkit_WHO_PERSON

#include "t_entity.h"

namespace _ {

/* Class that represents a person/human.
@todo Load a person from social media account using Facebook and OAuth APIs.
*/
class TPerson : public TEntity {
 public:
  /*Creates a person with no name. */
  TPerson();

  /* Prints this object to a expression. */
  Printer& Print (Printer& o) { o << "Person: "; }

 private:
  TStrand<>& lastName;  //< The last name of the entity.
};
}       // namespace _
#endif  //< kabuki.toolkit_WHO_PERSON
#endif  //< #if SEAM >= kabuki.toolkit_WHO_1
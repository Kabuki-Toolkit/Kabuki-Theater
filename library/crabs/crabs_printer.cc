/** Kabuki Toolkit
    @version 0.x
    @file    ~/library/crabs/crabs_text.cc
    @author  Cale McCollough <cale.mccollough@gmail.com>
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

#include <stdafx.h>

#if MAJOR_SEAM > 1 || MAJOR_SEAM == 1 && MINOR_SEAM >= 2

#include "printer.h"

#if USING_PRINTER

#include "text.h"
#include "type.h"

#if MAJOR_SEAM == 1 && MINOR_SEAM == 1
#define PRINTF(format, ...) printf(format, __VA_ARGS__);
#define PUTCHAR(c) putchar(c);
#define PRINT_HEADING\
    std::cout << '\n';\
    for (int i = 80; i > 0; --i) std::cout << '-';
#else
#define PRINTF(x, ...)
#define PUTCHAR(c)
#define PRINT_HEADING
#endif

namespace _ {

Printer::Printer (char* cursor, size_t buffer_size) :
    cursor (cursor),
    end (cursor + buffer_size - 1) {
    ASSERT (cursor)
    ASSERT (buffer_size)
}

Printer::Printer (char* begin, char* end) :
    cursor (begin),
    end (end) {
    ASSERT (cursor < end)
}

Printer::Printer (const Printer& other) :
    cursor (other.cursor),
    end (other.end) {
    // Nothing to do here! ({:-)-+=<
}

char* Print (char* cursor, char* end, const char* string) {
    ASSERT (cursor)
    ASSERT (string)

    if (cursor >= end) {
        return nullptr;
    }

    char c = *string++;
    while (c) {
        *cursor++ = c;
        if (cursor >= end) {
            return nullptr;
        }
        c = *string++;
    }
    *cursor = 0;
    return cursor;
}

char* Print (char* cursor, char* end, const char* string, const char* string_end) {
    ASSERT (string)
    ASSERT (string_end)
    ASSERT (cursor)
    ASSERT (end);

    if (cursor >= end) {
        cursor = nullptr;
    }
    if (string >= string_end) {
        return nullptr;
    }

    char c = *string;
    while (c) {
        if (!c) {
            return nullptr;
        }
        *cursor = c;
        if (++cursor >= end) {
            *cursor = 0;
            return nullptr;
        }
        if (++string >= string_end) {
            *cursor = 0;
            return nullptr;
        }
        c = *string;
    }
    *cursor = 0;
    return cursor;
}

char* Print (char* cursor, char* end, char character) {
    ASSERT (cursor)
    ASSERT (end);

    if (cursor + 1 >= end)
        return nullptr;

    *cursor++ = character;
    *cursor = 0;
    return cursor;
}

}       //< namespace _

#undef PRINTF
#undef PUTCHAR
#endif  //< USING_PRINTER
#endif  //< #if MAJOR_SEAM > 1 || MAJOR_SEAM == 1 && MINOR_SEAM >= 2
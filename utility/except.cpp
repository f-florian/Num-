/***************************************************************************
 * Copyright (C) 2018 Francesco Florian
 * This file is part of Num++.
 *
 * Num++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Num++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Num++.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "except.h"
#include <string>

namespace Numpp{
    /**
     * @param what_arg description string
     * @param item enum item which triggered the error 
     */
    EnumError::EnumError(const std::string& what_arg, int item) noexcept : std::runtime_error(what_arg)
    {
        item_m=item;
    }
    /**
     * @param what_arg description string
     * @param item enum item which triggered the error 
     */
    EnumError::EnumError(const char *what_arg, int item) noexcept : std::runtime_error(what_arg)
    {
        item_m=item;
    }
    /**
     * @return error string
     */
    const char* EnumError::what() const noexcept
    {
        return (static_cast<const std::runtime_error*>(this)->what() + std::string(". Item number ") + std::to_string(item_m)).data();
    }
}

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

#include <type_traits>
#include <stdexcept>

/**
 * Namespace container for Num++.
 */
namespace Numpp{
    /**
     * Throw this for errors in enum management.
     */
    class EnumError : public std::runtime_error
    {
    public:
	EnumError(const std::string& what_arg, int item) noexcept;		//!< std::string constructor
	EnumError(const char *what_arg, int item) noexcept;			//!< char* constructor
	const char* what() const noexcept;					//!< what()
    protected:
	int item_m;								//!< Item identifier for constructing string
    };
}

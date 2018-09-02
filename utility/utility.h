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
#ifndef UTILITY_H
#define UTILITY_H

#include <type_traits>

namespace Numpp {
    /**
     * Template functions for getting information about and manipulating enum classes
     */
    namespace EnumUtils {
        /**
         * Convert enum item to its numeric value.
	 *
         * @param item enum item to convert
         * @return converted value
         */
        template <class T> constexpr typename std::enable_if<std::is_enum<T>::value, typename std::underlying_type<T>::type>::type enumToNumeric (T item) noexcept {
            return static_cast<typename std::underlying_type<T>::type>(item);
        }
	/**
	 * Get enum size.
	 *
	 * @return enum size (i.e. 1 + maximum value)
	 * For this function to work the enum must have an item named `max` indicating maximum value
	 */
        template <class T> constexpr typename std::enable_if<std::is_enum<T>::value, size_t>::type size() noexcept {
            return static_cast<size_t>(T::max) + 1;
        }
    }
    
    /**
     * Storage types
     */
    enum class StorageType
    {
        Dense = 0,
        Sparse,
        Custom,                                                                                                            //!< User defined type
        max = Custom
    };
}

#endif /* UTILITY_H */

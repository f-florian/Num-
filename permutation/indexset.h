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

#include <string>
#include <initializer_list>

namespace Numpp {
    /**
     * Ordered (multi)set of indices
     * 
     * Substitute an index permutation when indices can be repeated.   
     */
    class IndexSet
    {
    public:
        IndexSet(const size_t size);                                                                //!< Construct from size
        IndexSet(std::initializer_list<size_t> list);                                               //!< Construct from initializer_list
        IndexSet(const size_t start, const size_t end, const size_t step=1);                        //!< Construct linear progression
        IndexSet(const size_t start, const size_t size);                                            //!< Construct with constant index
        IndexSet(const IndexSet & other);                                                           //!< Copy constructor
        IndexSet(IndexSet && other) noexcept;                                                       //!< Move constructor
        ~IndexSet() noexcept;                                                                       //!< Destructor

        IndexSet& operator=(const IndexSet &other);                                                 //!< Copy assignment
        IndexSet& operator=(IndexSet &&other) noexcept;                                             //!< Move assignment
	
        IndexSet operator+ (const size_t offset) const;                                             //!< Shift
        void operator+= (const size_t offset);                                                      //!< Shift and assign 
        IndexSet operator* (const size_t factor) const;                                             //!< Sscale
        void operator*= (const size_t factor);                                                      //!< Scale and assign
 
        bool operator==(const IndexSet &other) const noexcept;                                      //!< Comparison (equality)
        bool operator!=(const IndexSet &other) const noexcept;                                      //!< Comparison (inequality)

        std::string print() const noexcept;                                                         //!< Print in a standardized anh human readable form 
        size_t operator[](const size_t point) const noexcept;                                       //!< Accessindex at given position
        size_t at(const size_t point) const;                                                        //!< Accessindex at given position
        void swap(IndexSet &other) noexcept;                                                        //!< Swap with other element
    private:
        vector<size_t> permutation;                                                                 //!< Internal representation
    };
}


namespace std {
    void swap(IndexSet &a, IndexSet &b) noexcept;                                                   //!< Swap function for std
}

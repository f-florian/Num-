
/***************************************************************************
  * Copyright (C) 2018 Francesco Florian
  * This file is part of Num++.
  *
  * Num++ is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.

  * Num++ is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.

  * You should have received a copy of the GNU General Public License
  * along with Num++.  If not, see <http://www.gnu.org/licenses/>.
  ***************************************************************************/

#include "indexset.h"

namespace Numpp {
    /**
     * \param size set size
     * all elements are initialized to 0
     */
    IndexSet::IndexSet(const size_t size)
    {
        permutation.resize(size,0);
    }
    /**
     * \param list initializer_listithhe same erlements of the set
     */
    IndexSet::IndexSet(std::initializer_list<size_t> list)
    {
        permutation=list;
    }
    /**
     * \param start first element
     * \param end last or past-the-last element
     * \param step distance between consecutive elements
     * 
     * If end<start step is considered negative 
     */
    IndexSet::IndexSet(const size_t start, const size_t end, const size_t step)
    {
        if(step==0)
            throw(std::runtime_error("Step cannot be 0"));
        if(start > end) {
            size_t size=(start - end +1)/step;
            permutation.resize(size);
            for(size_t j=0; j<size; ++j)
                permutation[j]=start - j * step;
        } else {
            size_t size=(start - end +1)/step;
            permutation.resize(size);
            for(size_t j=0; j<size; ++j)
                permutation[j]=start - j * step;
        }
    }
    /**
     * \param start first element
     * \param size number of elements
     * 
     * Construct object with size element equal to start
     */
    IndexSet::IndexSet(const size_t start, const size_t size)
    {
        permutation.resize(size,start);
    }
    /**
     * \param other Object to copy
     */
    IndexSet::IndexSet(const IndexSet & other)
    {
        permutation=other.permutation;
    }
    /**
     * \param other Object to move
     */
    IndexSet::IndexSet(IndexSet && other) noexcept
    {
        permutation=std::move(other.permutation);
    }
    /**
     * Clear memory
     */
    IndexSet::~IndexSet() noexcept{
        permutation.clear();
    }

    /**
     * \param other Object to copy
     * \return copied object
     */
    IndexSet& IndexSet::operator=(const IndexSet &other)
    {
        permutation=other.permutation;
        return *this;
    }
    /**
     * \param other Object to move
     * \return Moved object
     */
    IndexSet& IndexSet::operator=(IndexSet &&other) noexcept
    {
        permutation=std::move(other.permutation);
        return *this;
    }

    /**
     * \param offset Quantity to add to each element
     * \return Copy of this shifted by offet
     */
    IndexSet IndexSet::operator+(const size_t offset) const	
    {
        IndexSet tmpvar(*this);
        tmpvar += offset;
        return tmpvar;
    }
    /**
     * \param offset Quantity to add to each element
     *
     * Shift each element by offset
     */
    void IndexSet::operator+=(const size_t offset)	
    {
        for(auto& x : permutation)
            x+=offset;
    }
    /**
     * \param factor Scaling factor
     * \return Copy of this scaled of factor
     */
    IndexSet IndexSet::operator*(const size_t factor) const	
    {
        IndexSet tmpvar(*this);
        tmpvar *= factor;
        return tmpvar;
    }
    /**
     * \param factor Scaling factor
     *
     * Scale each element of factor
     */
    void IndexSet::operator*=(const size_t factor)	
    {
        for(auto& x : permutation)
            x*=factor;        
    }

    /**
     * \param other Second object to compare
     * \return true if the two objects represent the same set of indices, false otherwise
     */
    bool IndexSet::operator==(const IndexSet &other) const noexcept	
    {
        return (permutation==other.permutation);
    }
    /**
     * \param other Second object to compare
     * \return false if the two objects represent the same set of indices, true otherwise
     */
    bool IndexSet::operator!=(const IndexSet &other) const noexcept	
    {
        return (permutation!=other.permutation);
    }

    /**
     * \return A string representing this object
     *
     * This is a human readable representation, but it could also be used to reconstruct the object
     */
    std::string IndexSet::print() const noexcept
    {
        std::string out="IndexSet{";
        for (auto &x : permutation)
            out += std::to_string(x);
        out += "}";
        return out;
    }

    /**
     * \param point position identifying the index
     * \return the index at position point
     */
    size_t IndexSet::operator[](const size_t point) const noexcept
    {
        return permutation[point];
    }

    /**
     * \param point position identifying the index
     * \return the index at position point
     */
    size_t IndexSet::at(const size_t point) const
    {
        return permutation.at(point);
    }

    /**
     * \param other object to swap
     */
    void IndexSet::swap(IndexSet &other) noexcept
    {
        permutation.swap(other.permutation);
    }
}

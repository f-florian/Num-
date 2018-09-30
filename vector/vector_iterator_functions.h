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

#ifndef VECTOR_ITERATOR_FUNCTIONS_H
#define VECTOR_ITERATOR_FUNCTIONS_H

#include <stdexcept>
#include "vector.h"

/**
 * \file 
 * Template functions for Vector::t_Iterator<T>.
 *
 * Not needed if T is double or const double (use vector_iterator_extern.h instead)
 */

namespace Numpp {
    /**
     * The iterator is not associated to any container.
     * Operating on it results in an exception being throw when using non-noexcept functions.
     * Current noexcept functions are comparison and index access.
     */
    template<typename T>
    Vector::t_Iterator<T>::t_Iterator() noexcept
    {
        data=nullptr;
        position=0;
    }

    /**
     * \param container referenced Vector
     * \param position_p referenced position in the container
     */
    template<typename T>
    Vector::t_Iterator<T>::t_Iterator(VType container, size_t position_p) noexcept :
        data(container), position(position_p) {}
    
    /**
     * \param it iterator to copy
     */
    template<typename T>
    Vector::t_Iterator<T>::t_Iterator(const t_Iterator<T> &it) noexcept
    {
        data=it.data;
        position=it.position;
    }

    /**
     * \param it iterator to move.
     * This constructor is not faster than copy
     */
    template<typename T>
    Vector::t_Iterator<T>::t_Iterator(t_Iterator<T> &&it) noexcept
    {
        data=it.data;
        position=it.position;
    }

    /**
     * \param it iterator to copy
     * \return Copied iterator
     */
    template<typename T>
    Vector::t_Iterator<T>& Vector::t_Iterator<T>::operator=(const Vector::t_Iterator<T> &it) noexcept
    {
        data=it.data;
        position=it.position;
        return (*this);
    }
    /**
     * \param it iterator to move
     * \return Moved iterator
     * This function is not faster than copy
     */
    template<typename T>
    Vector::t_Iterator<T>& Vector::t_Iterator<T>::operator=(Vector::t_Iterator<T> &&it) noexcept
    {
        data=it.data;
        position=it.position;
        return (*this);
    }

    /**
     *\return size of the underlying container
     */
    template<typename T>
    size_t Vector::t_Iterator<T>::size() const
    {
        if(data==nullptr)
            throw(std::range_error("Vector::t_Iterator<T>::size: Operating on uninitialized iterator is not allowed"));
        return data->size();
    }

    template<typename T>
    void Vector::t_Iterator<T>::operator++()
    {
        if(size()>=position)
            throw(std::range_error("Trying to advance iterator beyond the container size"));
        position++;
    }
    /**
     * \param i Unused parameter used to dddistinguish between pre- and post- increment
     */
    template<typename T>
    void Vector::t_Iterator<T>::operator++([[maybe_unused]] int i)
    {
        if(size()>=position)
            throw(std::range_error("Trying to advance iterator beyond the container size"));
        position++;
    }

    /**
     * \param other Iterator to compare
     * \return true if iterators point to the element of the same container, false otherwise
     *
     * Note that pointing to distinct containers which are equal will still mak the iterators different
     */
    template<typename T>
    bool Vector::t_Iterator<T>::operator==(const Vector::t_Iterator<T> &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position==other.position);
    }
    /**
     * \param other Iterator to compare
     * \return false if iterators point to the element of the same container, true otherwise
     *
     * Note that pointing to distinct containers which are equal will still make the iterators different
     */
    template<typename T>
    bool Vector::t_Iterator<T>::operator!=(const Vector::t_Iterator<T> &other) const noexcept
    {
        if(data!=other.data)
            return true;
        else
            return (position!=other.position);
    }

    /**
     * \return value of the cell pointed by the iterator
     */
    template<typename T>
    double Vector::t_Iterator<T>::operator*() const
    {
        if(position < size())
            return (*data)[position];
        throw(std::range_error("Dereferencing past the end iterator"));
    }
    
    template<typename T>
    void Vector::t_Iterator<T>::operator--()
    {
        if(position==0)
            throw(std::range_error("Trying to move iterator to a negative position"));
        position--;
    }
    /**
     * \param unused parameter used to dddistinguish between pre- and post- decrement
     */
    template<typename T>
    void Vector::t_Iterator<T>::operator--([[maybe_unused]] int)
    {
        if(position==0)
            throw(std::range_error("Trying to move iterator to a negative position"));
        position--;
    }

    /**
     * \param other Iterator to compare
     * \return false if iterators point to different containers, or if this points to an element 
     * which follows (strictly) that pointed by other
     *
     * Note that pointing to distinct containers which are equal will still make the iterators different.
     *
     * Note that this is not equivalent to (! (*this) > other)).
     */
    template<typename T>
    bool Vector::t_Iterator<T>::operator<=(const Vector::t_Iterator<T> &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position<=other.position);
    }
    /**
     * \param other Iterator to compare
     * \return false if iterators point to different containers, or if this points to an element 
     * which precedes (strictly) that pointed by other
     *
     * Note that pointing to distinct containers which are equal will still make the iterators different.
     *
     * Note that this is not equivalent to (! (*this) < other)).
     */
    template<typename T>
    bool Vector::t_Iterator<T>::operator>=(const Vector::t_Iterator<T> &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position>=other.position);
    }

    /**
     * \param other Iterator to compare
     * \return false if iterators point to different containers, or if this points to an element 
     * which is equal to or follows that pointed by other
     *
     * Note that pointing to distinct containers which are equal will still make the iterators different.
     *
     * Note that this is not equivalent to (! (*this) >= other)).
     */
    template<typename T>
    bool Vector::t_Iterator<T>::operator<(const Vector::t_Iterator<T> &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position < other.position);
    }

    /**
     * \param other Iterator to compare
     * \return false if iterators point to different containers, or if this points to an element 
     * which is equal to or precedes that pointed by other
     *
     * Note that pointing to distinct containers which are equal will still make the iterators different.
     *
     * Note that this is not equivalent to (! (*this) <= other)).
     */
    template<typename T>
    bool Vector::t_Iterator<T>::operator>(const Vector::t_Iterator<T> &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position > other.position);
    }

    /**
     * \param offset number of positions to advance
     * \return adanced iterator
     */
    template<typename T>
    Vector::t_Iterator<T> Vector::t_Iterator<T>::operator+(const diff_t offset) const
    {
        t_Iterator<T> tmp(*this);
        tmp+=offset;
        return tmp;
    }
    /**
     * \param offset number of positions to move back
     * \return iterator moved back
     */
    template<typename T>
    Vector::t_Iterator<T> Vector::t_Iterator<T>::operator-(const diff_t offset) const
    {
        t_Iterator<T> tmp(*this);
        tmp-=offset;
        return tmp;
    }
    /**
     * \param offset number of positions to advance
     * \return adanced iterator
     */
    template<typename T>
    Vector::t_Iterator<T> Vector::t_Iterator<T>::operator+(const size_t offset) const
    {
        t_Iterator<T> tmp(*this);
        tmp+=offset;
        return tmp;
    }
    /**
     * \param offset number of positions to move back
     * \return iterator moved back
     */
    template<typename T>
    Vector::t_Iterator<T> Vector::t_Iterator<T>::operator-(const size_t offset) const
    {
        t_Iterator<T> tmp(*this);
        tmp-=offset;
        return tmp;
    }

    /**
     * Compute difference of iterators; throws if they point to different containers
     */
    template<typename T>
    typename Vector::t_Iterator<T>::diff_t Vector::t_Iterator<T>::operator-(const Vector::t_Iterator<T> other) const
    {
        if(data != other.data)
            throw(std::runtime_error("Vector::t_Iterator<T>::operator-: Taking difference of iterators relative to different containers is not allowed"));
        return position>other.position ? diff_t(true,position-other.position) : diff_t(false,other.position-position);
    }
    
    /**
     * \param offset number of positions to advance
     */
    template<typename T>
    void Vector::t_Iterator<T>::operator+=(const diff_t offset)
    {
        if(offset.first)
            return (*this)+=offset.second;
        return (*this)-=offset.second;
    }
    /**
     * \param offset number of positions to advancemove back
     */
    template<typename T>
    void Vector::t_Iterator<T>::operator-=(const diff_t offset)
    {
        if(offset.first)
            return (*this)-=offset.second;
        return (*this)+=offset.second;
    }
    /**
     * \param offset number of positions to advance
     */
    template<typename T>
    void Vector::t_Iterator<T>::operator+=(const size_t offset)
    {
        if(position + offset > data->size())
            throw(std::range_error("Vector::t_Iterator<T>::operator+=: Trying to advance iterator beyond the container size"));
        position+=offset;
    }
    /**
     * \param offset number of positions to advancemove back
     */
    template<typename T>
    void Vector::t_Iterator<T>::operator-=(const size_t offset)
    {
        if(position < offset)
            throw(std::range_error("Vector::t_Iterator<T>::operator-= Trying to move iterator to a negative position"));
        position-=offset;
    }

    /**
     * \param offset Position to access, gives as difference from the current one
     */
    template<typename T>
    double Vector::t_Iterator<T>::operator[](const diff_t offset) const
    {
        if(offset.first){
            if(position + offset.second >= size())
                throw(std::range_error("Vector::t_Iterator<T>::operator[]: Trying to dereference iterator beyond the container size"));
            else
                return (*data)[position+offset.second];
        } else {
            if(position < offset.second)
                throw(std::range_error("Vector::t_Iterator<T>::operator[] Trying to dereference iterator to a negative position"));
            else
                return (*data)[position-offset.second];
        }
    }

    /**
     * \param index Position to move to
     */
    template<typename T>
    void Vector::t_Iterator<T>::set(const size_t index)
    {
        if(index >= size())
            throw(std::range_error("Vector::t_Iterator<T>::set: Trying to move iterator beyond the container size"));
        position=index;
    }

}

#endif /* VECTOR_ITERATOR_FUNCTIONS_H */

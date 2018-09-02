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

#include <stdexcept>
#include "vector.h"

namespace Numpp {
    template<typename T>
    Vector::t_Iterator<T>::t_Iterator() noexcept
    {
        data=nullptr;
        position=0;
    }
    template<typename T>
    Vector::t_Iterator<T>::t_Iterator(VType container, size_t position_p) noexcept :
        data(container), position(position_p) {}
    template<typename T>
    Vector::t_Iterator<T>::t_Iterator(const t_Iterator<T> &it) noexcept
    {
        data=it.data;
        position=it.position;
    }
    template<typename T>
    Vector::t_Iterator<T>::t_Iterator(t_Iterator<T> &&it) noexcept
    {
        data=it.data;
        position=it.position;
    }
    template<typename T>
    Vector::t_Iterator<T>& Vector::t_Iterator<T>::operator=(const Vector::t_Iterator<T> &it) noexcept
    {
        data=it.data;
        position=it.position;
        return (*this);
    }
    template<typename T>
    Vector::t_Iterator<T>& Vector::t_Iterator<T>::operator=(Vector::t_Iterator<T> &&it) noexcept
    {
        data=it.data;
        position=it.position;
        return (*this);
    }

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
    template<typename T>
    void Vector::t_Iterator<T>::operator++([[maybe_unused]] int)
    {
        if(size()>=position)
            throw(std::range_error("Trying to advance iterator beyond the container size"));
        position++;
    }

    template<typename T>
    bool Vector::t_Iterator<T>::operator==(const Vector::t_Iterator<T> &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position==other.position);
    }
    template<typename T>
    bool Vector::t_Iterator<T>::operator!=(const Vector::t_Iterator<T> &other) const noexcept
    {
        if(data!=other.data)
            return true;
        else
            return (position!=other.position);
    }

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
    template<typename T>
    void Vector::t_Iterator<T>::operator--([[maybe_unused]] int)
    {
        if(position==0)
            throw(std::range_error("Trying to move iterator to a negative position"));
        position--;
    }

    template<typename T>
    bool Vector::t_Iterator<T>::operator<=(const Vector::t_Iterator<T> &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position<=other.position);
    }
    template<typename T>
    bool Vector::t_Iterator<T>::operator>=(const Vector::t_Iterator<T> &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position>=other.position);
    }
    template<typename T>
    bool Vector::t_Iterator<T>::operator<(const Vector::t_Iterator<T> &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position < other.position);
    }
    template<typename T>
    bool Vector::t_Iterator<T>::operator>(const Vector::t_Iterator<T> &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position > other.position);
    }
    template<typename T>
    Vector::t_Iterator<T> Vector::t_Iterator<T>::operator+(const diff_t offset) const
    {
        t_Iterator<T> tmp(*this);
        tmp+=offset;
        return tmp;
    }
    template<typename T>
    Vector::t_Iterator<T> Vector::t_Iterator<T>::operator-(const diff_t offset) const
    {
        t_Iterator<T> tmp(*this);
        tmp-=offset;
        return tmp;
    }
    template<typename T>
    Vector::t_Iterator<T> Vector::t_Iterator<T>::operator+(const size_t offset) const
    {
        t_Iterator<T> tmp(*this);
        tmp+=offset;
        return tmp;
    }
    template<typename T>
    Vector::t_Iterator<T> Vector::t_Iterator<T>::operator-(const size_t offset) const
    {
        t_Iterator<T> tmp(*this);
        tmp-=offset;
        return tmp;
    }
    template<typename T>
    typename Vector::t_Iterator<T>::diff_t Vector::t_Iterator<T>::operator-(const Vector::t_Iterator<T> other) const
    {
        if(data != other.data)
            throw(std::runtime_error("Vector::t_Iterator<T>::operator-: Taking difference of iterators relative to different containers is not allowed"));
        return position>other.position ? diff_t(true,position-other.position) : diff_t(false,other.position-position);
    }
    template<typename T>
    void Vector::t_Iterator<T>::operator+=(const diff_t offset)
    {
        if(offset.first)
            return (*this)+=offset.second;
        return (*this)-=offset.second;
    }
    template<typename T>
    void Vector::t_Iterator<T>::operator-=(const diff_t offset)
    {
        if(offset.first)
            return (*this)-=offset.second;
        return (*this)+=offset.second;
    }
    template<typename T>
    void Vector::t_Iterator<T>::operator+=(const size_t offset)
    {
        if(position + offset > data->size())
            throw(std::range_error("Vector::t_Iterator<T>::operator+=: Trying to advance iterator beyond the container size"));
        position+=offset;
    }
    template<typename T>
    void Vector::t_Iterator<T>::operator-=(const size_t offset)
    {
        if(position < offset)
            throw(std::range_error("Vector::t_Iterator<T>::operator-= Trying to move iterator to a negative position"));
        position-=offset;
    }
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
}

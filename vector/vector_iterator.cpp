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
    Vector::Iterator::Iterator() noexcept
    {
        data=nullptr;
        position=0;
    }
    Vector::Iterator::Iterator(Vector *container, size_t position_p) noexcept :
        data(container), position(position_p) {}
    Vector::Iterator::Iterator(const Iterator &it) noexcept
    {
        data=it.data;
        position=it.position;
    }
    Vector::Iterator::Iterator(Iterator &&it) noexcept
    {
        data=it.data;
        position=it.position;
    }
    Vector::Iterator& Vector::Iterator::operator=(const Vector::Iterator &it) noexcept
    {
        data=it.data;
        position=it.position;
        return (*this);
    }
    Vector::Iterator& Vector::Iterator::operator=(Vector::Iterator &&it) noexcept
    {
        data=it.data;
        position=it.position;
        return (*this);
    }

    size_t Vector::Iterator::size() const
    {
        if(data==nullptr)
            throw(std::range_error("Vector::Iterator::size: Operating on uninitialized iterator is not allowed"));
        return data->size();
    }
    void Vector::Iterator::operator++()
    {
        if(size()>=position)
            throw(std::range_error("Trying to advance iterator beyond the container size"));
        position++;
    }

    bool Vector::Iterator::operator==(const Vector::Iterator &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position==other.position);
    }
    bool Vector::Iterator::operator!=(const Vector::Iterator &other) const noexcept
    {
        if(data!=other.data)
            return true;
        else
            return (position!=other.position);
    }

    double& Vector::Iterator::operator*() const
    {
        if(position < size())
            return (*data)[position];
        throw(std::range_error("Dereferencing past the end iterator"));
    }
    void Vector::Iterator::operator--()
    {
        if(position==0)
            throw(std::range_error("Trying to move iterator to a negative position"));
        position--;
    }

    bool Vector::Iterator::operator<=(const Vector::Iterator &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position<=other.position);
    }
    bool Vector::Iterator::operator>=(const Vector::Iterator &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position>=other.position);
    }
    bool Vector::Iterator::operator<(const Vector::Iterator &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position < other.position);
    }
    bool Vector::Iterator::operator>(const Vector::Iterator &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position > other.position);
    }
    Vector::Iterator Vector::Iterator::operator+(const diff_t offset) const
    {
        Iterator tmp(*this);
        tmp+=offset;
        return tmp;
    }
    Vector::Iterator Vector::Iterator::operator-(const diff_t offset) const
    {
        Iterator tmp(*this);
        tmp-=offset;
        return tmp;
    }
    Vector::Iterator Vector::Iterator::operator+(const size_t offset) const
    {
        Iterator tmp(*this);
        tmp+=offset;
        return tmp;
    }
    Vector::Iterator Vector::Iterator::operator-(const size_t offset) const
    {
        Iterator tmp(*this);
        tmp-=offset;
        return tmp;
    }
    Vector::Iterator::diff_t Vector::Iterator::operator-(const Vector::Iterator other) const
    {
        if(data != other.data)
            throw(std::runtime_error("Vector::Iterator::operator-: Taking difference of iterators relative to different containers is not allowed"));
        return position>other.position ? diff_t(true,position-other.position) : diff_t(false,other.position-position);
    }
    void Vector::Iterator::operator+=(const diff_t offset)
    {
        if(offset.first)
            return (*this)+=offset.second;
        return (*this)-=offset.second;
    }
    void Vector::Iterator::operator-=(const diff_t offset)
    {
        if(offset.first)
            return (*this)-=offset.second;
        return (*this)+=offset.second;
    }
    void Vector::Iterator::operator+=(const size_t offset)
    {
        if(position + offset > data->size())
            throw(std::range_error("Vector::Iterator::operator+=: Trying to advance iterator beyond the container size"));
        position+=offset;
    }
    void Vector::Iterator::operator-=(const size_t offset)
    {
        if(position < offset)
            throw(std::range_error("Vector::Iterator::operator-= Trying to move iterator to a negative position"));
        position-=offset;
    }
    double& Vector::Iterator::operator[](const diff_t offset) const
    {
        if(offset.first){
            if(position + offset.second >= size())
                throw(std::range_error("Vector::Iterator::operator[]: Trying to dereference iterator beyond the container size"));
            else
                return (*data)[position+offset.second];
        } else {
            if(position < offset.second)
                throw(std::range_error("Vector::Iterator::operator[] Trying to dereference iterator to a negative position"));
            else
                return (*data)[position-offset.second];
        }
    }
}

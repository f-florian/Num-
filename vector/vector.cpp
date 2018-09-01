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

#include <initializer_list>
#include <cstring>
#include <string>
#include <stdexcept>
#include <new>
#include "vector.h"
#include "except.h"

namespace Numpp{
    Vector* Vector::operator+(const Vector *other) const
    {
        if(size()!=other->size())
            throw(std::range_error("Attempt of summing vectors of different sizes"));
        Vector* tmpst=allocCopy();
        (*tmpst)+=other;
        return tmpst;
    }
    void Vector::operator+=(const Vector *other)
    {
        if(size()!=other->size())
            throw(std::range_error("Attempt of summing vectors of different sizes"));
        for(auto x = other->storageBegin(); x != other->storageEnd(); x.storageAdvance())
            (*this)[x-other->begin()]+=(*x);
    }
    Vector* Vector::operator-(const Vector *other) const
    {
        if(size()!=other->size())
            throw(std::range_error("Attempt of summing vectors of different sizes"));
        Vector* tmpst=allocCopy();
        (*tmpst)-=other;
        return tmpst;
    }
    void Vector::operator-=(const Vector *other)
    {
        if(size()!=other->size())
            throw(std::range_error("Attempt of summing vectors of different sizes"));
        for(auto x = other->storageBegin(); x != other->storageEnd(); x.storageAdvance())
            (*this)[x-other->begin()]-=(*x);
    }
    double Vector::operator*(const Vector *other) const
    {
        double sum=0;
        for(auto x = begin(); x != end(); ++x)
            sum+=(*x)*(*other)[x-begin()];
    }
    Vector* Vector::operator*(const double scale) const
    {
        Vector* tmpst=allocCopy();
        (*tmpst)*=scale;
        return tmpst;
    }
    void Vector::operator*=(const double scale)
    {
        for(auto x = storageBegin(); x != storageEnd(); storageAdvance(x))
            (*x)*=scale;
    }

    // Comparison
    bool Vector::operator==(const Vector *other) const noexcept
    {
        if(size() != other->size())
            return false;
        for(auto x = begin(); x != end(); ++x)
            if((*x)!=(*other)[x-begin()])
                return false;
        return true;
    }

    bool Vector::operator!=(const Vector *other) const noexcept
    {
        if(size() != other->size())
            return true;
        for(auto x = begin(); x != end(); ++x)
            if((*x)!=(*other)[x-begin()])
                return true;
        return false;
    }

    bool Vector::operator<=(const Vector *other) const noexcept
    {
        if(size() != other->size())
            return false;
        for(auto x = begin(); x != end(); ++x)
            if((*x)>(*other)[x-begin()])
                return false;
        return true;
    }

    bool Vector::operator>=(const Vector *other) const noexcept
    {
        if(size() != other->size())
            return false;
        for(auto x = begin(); x != end(); ++x)
            if((*x)<(*other)[x-begin()])
                return false;
        return true;
    }

    bool Vector::operator<(const Vector *other) const noexcept
    {
        if(size() != other->size())
            return false;
        for(auto x = begin(); x != end(); ++x)
            if((*x)>=(*other)[x-begin()])
                return false;
        return true;
    }

    bool Vector::operator>(const Vector *other) const noexcept
    {
        if(size() != other->size())
            return false;
        for(auto x = begin(); x != end(); ++x)
            if((*x)<=(*other)[x-begin()])
                return false;
        return true;
    }
    std::string Vector::print() const noexcept
    {
        std::string out=std::to_string(EnumUtils::enumToNumeric(storageType()))+std::to_string(size());
        for(auto  &x : *this)
            out+=std::to_string(*x);
    }
    void Vector::swap(const size_t x1, const size_t x2)
    {
        auto tmp = (*this)[x1];
        this->set(x1,(*this)[x2]);
        this->set(x2,tmp);
    }
    Vector::Iterator Vector::begin() noexcept
    {
        return new Vector::Iterator(this, 0);
    }
    Vector::Iterator Vector::end() noexcept
    {
        return new Vector::Iterator(this, size());
    }
    double Vector::at(const size_t point) const
    {
        if(point >= size())
            throw(std::range_error("Numpp::Vector::at(): Trying to access elements past the Vector"));
        return (*this)[point];
    }
}
namespace std {
    void swap(Numpp::VectorStorageSparse &a, Numpp::VectorStorageSparse &b)
    {
        a.swap(b);
    }
    void swap(Numpp::VectorStorageLinear &a, Numpp::VectorStorageLinear &b)
    {
        a.swap(b);
    }
}

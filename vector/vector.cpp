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
#include "vector_iterator_extern.h"

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
        for(auto x = other->storagecBegin(); x != other->storagecEnd(); other->storageAdvance(x))
            set(x-other->cbegin(), (*this)[x-other->cbegin()]+(*x));
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
        for(auto x = other->storagecBegin(); x != other->storagecEnd(); other->storageAdvance(x))
            set(x-other->cbegin(), (*this)[x-other->cbegin()]-(*x));
    }
    double Vector::operator*(const Vector *other) const
    {
        double sum=0;
        for(auto x = cbegin(); x != cend(); ++x)
            sum+=(*x)*(*other)[x-cbegin()];
        return sum;
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
            set(x-begin(), scale*(*this)[x-begin()]);
    }

    // Comparison
    bool Vector::operator==(const Vector *other) const noexcept
    {
        if(size() != other->size())
            return false;
        for(auto x = cbegin(); x != cend(); ++x)
            if((*x)!=(*other)[x-cbegin()])
                return false;
        return true;
    }

    bool Vector::operator!=(const Vector *other) const noexcept
    {
        if(size() != other->size())
            return true;
        for(auto x = cbegin(); x != cend(); ++x)
            if((*x)!=(*other)[x-cbegin()])
                return true;
        return false;
    }

    bool Vector::operator<=(const Vector *other) const noexcept
    {
        if(size() != other->size())
            return false;
        for(auto x = cbegin(); x != cend(); ++x)
            if((*x)>(*other)[x-cbegin()])
                return false;
        return true;
    }

    bool Vector::operator>=(const Vector *other) const noexcept
    {
        if(size() != other->size())
            return false;
        for(auto x = cbegin(); x != cend(); ++x)
            if((*x)<(*other)[x-cbegin()])
                return false;
        return true;
    }

    bool Vector::operator<(const Vector *other) const noexcept
    {
        if(size() != other->size())
            return false;
        for(auto x = cbegin(); x != cend(); ++x)
            if((*x)>=(*other)[x-cbegin()])
                return false;
        return true;
    }

    bool Vector::operator>(const Vector *other) const noexcept
    {
        if(size() != other->size())
            return false;
        for(auto x = cbegin(); x != cend(); ++x)
            if((*x)<=(*other)[x-cbegin()])
                return false;
        return true;
    }
    std::string Vector::print() const noexcept
    {
        std::string out=std::to_string(EnumUtils::enumToNumeric(storageType())) + " " + std::to_string(size());
        for(auto x = cbegin(); x != cend(); ++x)
            out+=" " + std::to_string(*x);

        out+="end";
        return out;
    }
    void Vector::swap(const size_t x1, const size_t x2)
    {
        auto tmp = (*this)[x1];
        this->set(x1,(*this)[x2]);
        this->set(x2,tmp);
    }
    Vector::Iterator Vector::begin() noexcept
    {
        Vector::Iterator tmp(this, 0);
        return tmp;
    }
    Vector::Iterator Vector::end() noexcept
    {
        Vector::Iterator tmp(this, size());
        return tmp;
    }
    Vector::Iterator Vector::at(const size_t point)
    {
        if(point >= size())
            throw(std::range_error("Numpp::Vector::at(): Trying to access elements past the Vector"));
        Vector::Iterator tmp(this,point);
        return tmp;
    }
    Vector::ConstIterator Vector::cAt(const size_t point) const
    {
        if(point >= size())
            throw(std::range_error("Numpp::Vector::at(): Trying to access elements past the Vector"));
        Vector::ConstIterator tmp(this,point);
        return tmp;
    }
    
    void Vector::transform(double (*fn)(double))
    {
        for(auto x = begin(); x != end(); ++x)
            this->set(x.index(),(*fn)(*x));
    }
    void Vector::transform(doubleUnary fn)
    {
        for(auto x = begin(); x != end(); ++x)
            this->set(x.index(),fn(*x));
    }
    
    void Vector::transform(double (*fn)(double,double), const Vector * const other)
    {
        for(auto x = begin(); x != end(); ++x)
            this->set(x.index(),(*fn)(*x, other->at(x.index())));
    }
    void Vector::transform(doubleBinary fn, const Vector * const other)
    {
        for(auto x = begin(); x != end(); ++x)
            this->set(x.index(),fn(*x, other->at(x.index())));
    }
    Vector* Vector::ctransform(double (*fn)(double,double), const Vector * const other) const
    {
        Vector * tmp=allocSameType(size());
        for(auto x = cbegin(); x != cend(); ++x)
            tmp->set(x.index(),(*fn)(*x, other->at(x.index())));
        return tmp;
    }
    Vector* Vector::ctransform(doubleBinary fn, const Vector * const other) const
    {
        Vector * tmp=allocSameType(size());
        for(auto x = cbegin(); x != cend(); ++x)
            tmp->set(x.index(),fn(*x, other->at(x.index())));
        return tmp;
    }

}

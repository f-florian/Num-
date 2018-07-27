x/***************************************************************************
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

#include "vector.h"
#include "utility/except.h"
#include <initializer_list>

namespace Numpp{
    Vector::Vector(const StorageType type=StorageType::dense)
    {
        switch (type) {
        case Storagetype::dense:
            storage = new VectorStorageLinear();
            break;
        case Storagetype::sparse:
            storage = new VectorStorageLinear();
            break;
        default:
            throw(EnumError("Storage type not recognized"), EnumUtils::enumToNumeric(type));
        }
    }
    Vector::Vector(const size_t size, const double value, const StorageType type=StorageType::dense)
    {
        switch (type) {
        case Storagetype::dense:
            storage = new VectorStorageLinear(size,value);
            break;
        case Storagetype::sparse:
            storage = new VectorStorageLinear(size,value);
            break;
        default:
            throw(EnumError("Storage type not recognized"), EnumUtils::enumToNumeric(type));
        }
    }
    Vector::Vector(const std::initializer_list<double> values)
    {
        storage=new VectorStorageLinear(values.size());
    }
    Vector::Vector(const std::initializer_list<std::pair<size_t,double>> values)
    {
        storage=new VectorStorageSparse();
        for(auto &x:values)
            (*storage)[x.first,x.second];
    }
    Vector::Vector(const Vector &other)
    {
        switch(other.storage->storageType()) {
        case StorageType::dense:
            storage=new VectorStorageLinear(*static_cast<VectorStorageLinear*>(other.storage));
            break;
        case StorageType::sparse:
            storage=new VectorStorageSparse(*static_cast<VectorStorageSparse*>(other.storage));
            break;
        default:
            throw(EnumError("Storage type of argument \"other\" not recognized"), EnumUtils::enumToNumeric(type));
        }
    }
    Vector::Vector(Vector &&other)
    {
        storage=other.storage;
        other.storage=nullptr;
    }
    Vector::~Vector()
    {
        delete storage;
    }
    
    Vector& Vector::operator=(Vector &&other) noexcept
    {
        Vector tmp(other);
        return &tmp;
    }
	
    // Arithmetic
    Vector Vector::operator+(const Vector &other) const
    {
        VectorStorage* tmpst;
        if(size()!=other.size())
            throw(std::range_error("Attempt of summing vectors of different sizes"));
        if((storage->storageType==StorageType::dense) || (other.storage->storageType==StorageType::dense)) {
            tmpst=new VectorStorageLinear(size());
            for(size_t idx = 0; idx < size(); ++idx)
                (*tmpst)[idx,(*storage[idx] + (*other.storage)[idx])];
        } else {
            tmpst=new VectorStorageSparse()
        }
    }
    void Vector::operator+=(const Vector &other);
    Vector Vector::operator-(const Vector &other) const;
    void Vector::operator=(const Vector &other);
    double Vector::operator*(const Vector &other) const;
    Vector Vector::operator*(const double scale) const;
    void Vector::operator*=(const double scale);

    // Comparison
    bool Vector::operator==(const Vector &other) const noexcept
    {
        //use iterators?
    }
    bool Vector::operator!=(const Vector &other) const noexcept;
    bool Vector::operator<=(const Vector &other) const noexcept;
    bool Vector::operator>=(const Vector &other) const noexcept;
    bool Vector::operator<(const Vector &other) const noexcept;
    bool Vector::operator>(const Vector &other) const noexcept;

    // Other
    std::string Vector::print() const noexcept;
    double& Vector::operator[](const size_t point) const noexcept
    {
        return (*storage)[point];
    }
    double& Vector::at(const size_t point) const
    {
        return storage->at(point);
    }
    void Vector::swap(const size_t x1, const size_t x2)
    {
        auto tmp = (*storage)[x1];
        (*storage)[x1,(*storage)[x2]];
        (*storage)[x2,tmp];
    }
    void Vector::swap(Vector &&other) noexcept
    {
        swap(storage,other.storage);
    }
    void Vector::swap(Vector &other) noexcept
    {
        swap(storage,other.storage);
    }
}

namespace std {
    void swap(Numpp::Vector &a, Numpp::Vector& b)
    {
        a.swap(b);
    }
}

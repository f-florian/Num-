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

#include "vectorstorage.h"
#include <cstring>
#include <stdexcept>
#include <new>

namespace numpp{
    VectorStorageLinear::VectorStorageLinear()
    {
        data_m=nullptr;
        size_m=0;
    }
    VectorStorageLinear::VectorStorageLinear(const size_t size)
    {
        size_m=size;
        data_m=(double *) malloc(size*sizeof(double));
        if (data_m==NULL)
            throw(std::bad_alloc("malloc failed"));
    }
    VectorStorageLinear::VectorStorageLinear(const size_t size, const double fill)
    {
        size_m=size;
        if (fill) {
            data_m=(double *) malloc(size*sizeof(double));
            if (data_m==NULL)
                throw(std::bad_alloc("malloc failed"));
            for (size_t i = 0; i < size; ++i)
                data_m[i]=fill;
        } else {
            data_m=(double *) calloc(size*sizeof(double));
            if (data_m==NULL)
                throw(std::bad_alloc("calloc failed"));
        }
    }
    VectorStorageLinear::~VectorStorageLinear()
    {
        free(data_m);
    }
    double VectorStorageLinear::operator[](const size_t position) const noexcept
    {
        return data[position];
    }
    void VectorStorageLinear::operator[](const size_t position, const double val)
    {
        if(position>size_m)
            throw(std::range_error("index exceeds vector size"));
        data_m[position]=val;
    }
    size_t VectorStorageLinear::size() const noexcept
    {
        return size_m;
    }
    

    VectorStorageSparse::VectorStorageSparse(){}
    VectorStorageSparse::VectorStorageSparse(const size_t position, const double value)
    {
        data_m[position]=value;
        size_m=position;
    }
    VectorStorageSparse::~VectorStorageSparse()
    {
        data_m.clear();
    }
    double VectorStorageSparse::operator[](const size_t position) const noexcept
    {
        try {
            return data_m.at(position);
        } catch ([[maybe_unused]] const std::out_of_range &e) {
            return 0;
        }
    }
    void VectorStorageSparse::operator[](const size_t position, const double val)
    {
        if(val==0)
            data_m.erase(position);
        else if(position>size_m)
            throw(std::range_error("index exceeds vector size"));
        else
            data_m[position]=val;
    }
    size_t VectorStorageSparse::size() const noexcept
    {
        return size_m;
    }
}

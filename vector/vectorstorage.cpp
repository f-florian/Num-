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

#include <cstring>
#include <string>
#include <stdexcept>
#include <new>
#include "vector.h"
#include "except.h"
                 
namespace Numpp {
    VectorStorageLinear::VectorStorageLinear()
    {
        data_m=nullptr;
        size_m=0;
    }
    VectorStorageLinear::VectorStorageLinear(const size_t size)
    {
        size_m=size;
        data_m=static_cast<double *>(calloc(size,sizeof(double)));
        if (data_m==NULL)
            throw(std::bad_alloc());
    }
    VectorStorageLinear::VectorStorageLinear(const size_t size, const double fill)
    {
        size_m=size;
        data_m=static_cast<double *>(malloc(size*sizeof(double)));
        if (data_m==NULL)
            throw(std::bad_alloc());
        for (size_t i = 0; i < size; ++i)
            data_m[i]=fill;
        // memset(data_m, other.data_m, size_m * sizeof(double));
    }

    VectorStorageLinear::VectorStorageLinear(const Vector* const other)
    {
        data_m=static_cast<double *>(malloc(other->size()*sizeof(double)));
        if (data_m==NULL)
            throw(std::bad_alloc());
        size_m=other->size();
        if(other->storageType()==StorageType::dense)
            memcpy(data_m,static_cast<const VectorStorageLinear*>(other)->data_m,size_m*sizeof(double));
        else
            for(size_t i = 0; i != size_m; ++i)
                data_m[i]=(*other)[i];
    }
    
    VectorStorageLinear::VectorStorageLinear(const VectorStorageLinear &other)
    {
        data_m=static_cast<double *>(malloc(other.size_m*sizeof(double)));
        if (data_m==NULL)
            throw(std::bad_alloc());
        memcpy(data_m,other.data_m,size_m*sizeof(double));
        size_m=other.size_m;
    }
    VectorStorageLinear::VectorStorageLinear(VectorStorageLinear &&other)
    {
        size_m=other.size_m;
        data_m=other.data_m;
        other.data_m=NULL;
    }
    VectorStorageLinear::~VectorStorageLinear()
    {
        free(data_m);
    }

    double VectorStorageLinear::operator[](const size_t position) const noexcept
    {
        return data_m[position];
    }
    size_t VectorStorageLinear::size() const noexcept
    {
        return size_m;
    }
    StorageType VectorStorageLinear::storageType() const noexcept
    {
        return StorageType::dense;
    }
    Vector::Iterator VectorStorageLinear::storageBegin() noexcept
    {
        Vector::Iterator tmp(static_cast<Vector*>(this),0);
        return tmp;
    }
    Vector::Iterator VectorStorageLinear::storageEnd() noexcept
    {
        Vector::Iterator tmp(static_cast<Vector*>(this),size_m);
        return tmp;
    }
    void VectorStorageLinear::storageAdvance(Vector::Iterator &it) const
    {
        ++it;
    }

    Vector* VectorStorageLinear::allocSameType(size_t size) const
    {
        Vector *tmp=new VectorStorageLinear(size);
        return tmp;
    }
    Vector* VectorStorageLinear::allocCopy() const
    {
        Vector *tmp=new VectorStorageLinear(*this);
        return tmp;
    }
    
    VectorStorageSparse::VectorStorageSparse() :size_m(0) {}
    VectorStorageSparse::VectorStorageSparse(const size_t position, const double value)
    {
        data_m[position]=value;
        size_m=position;
    }
    VectorStorageSparse::VectorStorageSparse(const Vector * const other)
    {
        if(other->storageType()==StorageType::sparse) {
            data_m=static_cast<const VectorStorageSparse*>(other)->data_m;
            size_m=static_cast<const VectorStorageSparse*>(other)->size_m;
        } else {
            for(auto it = other->storageBegin(); it != other->storageEnd(); other->storageAdvance(it))
                data_m[it.position]=(*it);
        }
    }
    VectorStorageSparse::VectorStorageSparse(const VectorStorageSparse &other)
    {
        data_m=other.data_m;
        size_m=other.size_m;
    }
    VectorStorageSparse::VectorStorageSparse(VectorStorageSparse &&other) noexcept
    {
        data_m.swap(other.data_m);
        size_m=other.size_m;
        other.data_m.clear();
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
    void VectorStorageSparse::set(const size_t position, const double val)
    {
        if(position>size_m)
            throw(std::range_error("VectorStorageSparse::set: Index exceeds vector size"));

        if(val==0)
            data_m[position]=val;
        else
            data_m.erase(data_m.find(position));
    }
    size_t VectorStorageSparse::size() const noexcept
    {
        return size_m;
    }
    StorageType VectorStorageSparse::storageType() const noexcept
    {
        return StorageType::sparse;
    }
    
    Vector::Iterator VectorStorageSparse::storageBegin() noexcept
    {
        Vector::Iterator it(this, data_m.begin()->first);
        return it;
    }
    Vector::Iterator VectorStorageSparse::storageEnd() noexcept
    {
        Vector::Iterator it(this, data_m.end()->first);
        return it;
    }
    void VectorStorageSparse::storageAdvance(Vector::Iterator &it) const
    {
#ifndef ___debug
#warning advance has log complexity
#endif  
        auto mit=data_m.find(it.index());
        mit++;
        it.set(mit->first);
    }
    std::string VectorStorageSparse::print() const noexcept
    {
        std::string out=std::to_string(EnumUtils::enumToNumeric(storageType()))+" ";
        for(auto &x : data_m)
            out+=std::to_string(x.first)+" "+std::to_string(x.second);
        return out;
    }
    Vector* VectorStorageSparse::allocSameType([[maybe_unused]] size_t size) const
    {
        VectorStorageSparse *tmp=new VectorStorageSparse();
        return tmp; 
    }
    Vector* VectorStorageSparse::allocCopy() const
    {
        VectorStorageSparse *tmp=new VectorStorageSparse(*this);
        return tmp; 
    }
}

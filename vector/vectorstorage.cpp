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

#include "vectorstorage.h"
#include <cstring>
#include <stdexcept>
#include <new>

namespace Numpp{

    VectorStorage::Iterator::Iterator(VectorStorage *container, size_t position)
    {
        data=container;
        position_m=position;
    }
    VectorStorage::Iterator::Iterator(const Iterator it)
    {
        data=it.data;
        position_m=it.position_m;
    }
    VectorStorage::Iterator::Iterator(const Iterator &it)
    {
        data=it.data;
        position_m=it.position_m;
    }
    VectorStorage::Iterator::Iterator(Iterator &&it)
    {
        data=it.data;
        position_m=it.position_m;
        it.data=std::nullptr;
    }
    Iterator& VectorStorage::Iterator::operator=(const Iterator &it)
    {
        Iterator tmp(it);
        return &tmp;
    }
    Iterator& VectorStorage::Iterator::operator=(Iterator &&it)
    {
        Iterator tmp(it);
        return &tmp;
    }

    void VectorStorage::Iterator::operator++()
    {
        if(data->size()>=position_m)
            throw(std::range_error("Trying to advance iterator beyond the container size"));
        position_m++;
    }

    bool VectorStorage::Iterator::operator==(const Iterator &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position_m==other.position_m);
    }
    bool VectorStorage::Iterator::operator!=(const Iterator &other) const noexcept
    {
        if(data!=other.data)
            return true;
        else
            return (position_m!=other.position_m);
    }

    double& VectorStorage::Iterator::operator*() const
    {
        if(position_m < data->size())
            return (*data)[position_m];
        throw(std::range_error("Dereferencing past the end iterator"));
    }
    VectorStorage::Iterator::Iterator(){}

    VectorStorage::Iterator::// bidirectional
    void VectorStorage::Iterator::operator--()
    {
        if(data->size()==0)
            throw(std::range_error("Trying to move iterator to a negative position"));
        position_m--;
    }

    bool VectorStorage::Iterator::operator<=(const Iterator &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position_m<=other.position_m);
    }
    bool VectorStorage::Iterator::operator>=(const Iterator &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position_m>=other.position_m);
    }
    bool VectorStorage::Iterator::operator<(const Iterator &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position_m < other.position_m);
    }
    bool VectorStorage::Iterator::operator>(const Iterator &other) const noexcept
    {
        if(data!=other.data)
            return false;
        else
            return (position_m > other.position_m);
    }
    Iterator VectorStorage::Iterator::operator+(const size_t offset) const
    {
        Iterator tmp(this);
        tmp+=offeset;
        return tmp;
    }
    Iterator VectorStorage::Iterator::operator-(const size_t offset) const
    {
        Iterator tmp(this);
        tmp-=offeset;
        return tmp;
    }
    std::pair<bool,size_t> VectorStorage::Iterator::operator-(const Iterator other) const
    {
        if(data != other.data)
            throw(std::runtime_error("subtracting iterators relative to different containers"));
        return position_m>other.position_m ? {true,position_m-other.position_m} : {false,other.position_m-position_m};
    }
    void VectorStorage::Iterator::operator+=(const size_t offset)
    {
        if(position_m + offset > data->size())
            throw(std::range_error("Trying to advance iterator beyond the container size"));
        position_m+=offset;
    }
    void VectorStorage::Iterator::operator-=(const size_t offset);
    {
        if(position_m < offset)
            throw(std::range_error("Trying to move iterator to a negative position"));
        position_m-=offset;
    }
    double& VectorStorage::Iterator::operator[](bool positive, size_t offset) const
    {
        if(positive){
            if(position_m + offset >= data->size())
                throw(std::range_error("Trying to dereference iterator beyond the container size"));
            else
                return (*data)[position_m+offset];
        } else {
            if(position_m < offset)
                throw(std::range_error("Trying to dereference iterator to a negative position"));
            else
                return (*data)[position_m-offset];
        }
    }
    double& VectorStorage::Iterator::operator[](pair<bool, size_t> offset) const
    {
        return operator[](offset.first,offset.second);
    }
    
    VectorStorageLinear::VectorStorageLinear()
    {
        data_m=nullptr;
        size_m=0;
    }
    VectorStorageLinear::VectorStorageLinear(const size_t size)
    {
        size_m=size;
        data_m=(double *) calloc(size*sizeof(double));
        if (data_m==NULL)
            throw(std::bad_alloc("calloc failed"));
    }
    VectorStorageLinear::VectorStorageLinear(const size_t size, const double fill)
    {
        size_m=size;
        data_m=(double *) malloc(size*sizeof(double));
        if (data_m==NULL)
            throw(std::bad_alloc("malloc failed"));
        for (size_t i = 0; i < size; ++i)
            data_m[i]=fill;
    }
    VectorStorageLinear::VectorStorageLinear(const VectorStorage &other);
    VectorStorageLinear::VectorStorageLinear(const VectorStorageLinear &other)
    {
        size_m=other.size_m;
        data_m=(double *) malloc(size*sizeof(double));
        if (data_m==NULL)
            throw(std::bad_alloc("malloc failed"));
        memcpy(data_m, other.data_m, size_m * sizeof(double));
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
    StorageType VectorStorageLinear::storageType() const noexcept
    {
        return StorageType::dense;
    }
    VectorStorage::Iterator VectorStorageLinear::begin() const noexcept
    {
        VectorStorage::Iterator tmp(this,0);
        return tmp;
    }
    VectorStorage::Iterator VectorStorageLinear::end() const noexcept
    {
        VectorStorage::Iterator tmp(this,size_m);
        return tmp;
    }
    
    VectorStorageSparse::VectorStorageSparse(){}
    VectorStorageSparse::VectorStorageSparse(const size_t position, const double value)
    {
        data_m[position]=value;
        size_m=position;
    }
    VectorStorageSparse(const VectorStorage &other);
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
    StorageType VectorStorageSparse::storageType() const noexcept
    {
        return StorageType::sparse;
    }
    VectorStorage::Iterator VectorStorageSparse::begin() const noexcept
    {
        VectorStorage::Iterator tmp(this,0);
        return tmp;
    }
    VectorStorage::Iterator VectorStorageSparse::end() const noexcept;
    {
        VectorStorage::Iterator tmp(this,size_m);
        return tmp;
    }
}

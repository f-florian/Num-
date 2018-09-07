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
#ifndef VECTORSTORAGE_H
#define VECTORSTORAGE_H

#include <initializer_list>
#include <map>
#include "vector.h"

namespace Numpp{
    class VectorStorageLinear : public Vector
    {
    public:
        VectorStorageLinear();
        VectorStorageLinear(const size_t size);
        VectorStorageLinear(const size_t size, const double fill);
        VectorStorageLinear(const Vector * const other);
        VectorStorageLinear(const VectorStorageLinear &other);
        VectorStorageLinear(VectorStorageLinear &&other);
        VectorStorageLinear& operator=(const VectorStorageLinear &other);
        VectorStorageLinear& operator=(VectorStorageLinear &&other);
        ~VectorStorageLinear();
        void assign(const size_t size, double * const data);
        const double* data() const;
        double* stealData();
        Iterator begin() noexcept;
        Iterator end() noexcept;
        Iterator storageBegin() noexcept;
        Iterator storageEnd() noexcept;
        ConstIterator cbegin() const noexcept;
        ConstIterator cend() const noexcept;
        ConstIterator storagecBegin() const noexcept;
        ConstIterator storagecEnd() const noexcept;
        void storageAdvance(Iterator &it) const;
        void storageAdvance(ConstIterator &it) const;
        double operator[](const size_t point) const noexcept;
        std::string print() const noexcept;
        size_t size() const noexcept;
        StorageType storageType() const noexcept;
        Vector* allocSameType(size_t size) const;
        Vector* allocCopy() const;
        void swap(const size_t x1, const size_t x2);
        void swap(VectorStorageLinear &other) noexcept;
    private:
        double* data_m;
        size_t size_m;
    };

    class VectorStorageSparse : public Vector
    {
    public:
        VectorStorageSparse();
        VectorStorageSparse(const size_t idx, const double value);
        VectorStorageSparse(const Vector * const other);
        VectorStorageSparse(const VectorStorageSparse &other);
        VectorStorageSparse(VectorStorageSparse &&other) noexcept;
        ~VectorStorageSparse();
        Vector* operator+(const Vector* const other) const;
        void operator+=(const Vector* const other);
        Vector* operator-(const Vector* const other) const;
        void operator-=(const Vector* const other);
        double operator*(const Vector* const other) const;
        Vector* operator*(const double scale) const;
        void operator*=(const double scale);
        bool operator==(const Vector* const other) const noexcept;
        bool operator!=(const Vector* const other) const noexcept;
        bool operator<=(const Vector* const other) const noexcept;
        bool operator>=(const Vector* const other) const noexcept;
        bool operator<(const Vector* const other) const noexcept;
        bool operator>(const Vector* const other) const noexcept;
        virtual Iterator begin() noexcept;
        virtual Iterator end() noexcept;
        virtual Iterator storageBegin() noexcept;
        virtual Iterator storageEnd() noexcept;
        virtual ConstIterator cbegin() const noexcept;
        virtual ConstIterator cend() const noexcept;
        virtual ConstIterator storagecBegin() const noexcept;
        virtual ConstIterator storagecEnd() const noexcept;
        virtual void storageAdvance(Iterator &it) const;
        virtual void storageAdvance(ConstIterator &it) const;
        double operator[](const size_t point) const noexcept;
        void set(const size_t point, const double val);
        std::string print() const noexcept;
        size_t size() const noexcept;
        StorageType storageType() const noexcept;
        Vector* allocSameType(size_t size) const;
        Vector* allocCopy() const;
        void swap(const size_t x1, const size_t x2);
        void swap(VectorStorageSparse &other) noexcept;
    private:
        std::map<size_t, double> data_m;
        size_t size_m;
    };
}

namespace std {
    void swap(Numpp::VectorStorageSparse &a, Numpp::VectorStorageSparse &b);
    void swap(Numpp::VectorStorageLinear &a, Numpp::VectorStorageLinear &b);
}

#endif /* VECTORSTORAGE_H */

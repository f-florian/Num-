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
#include <map>
#include <iterator>

#include "utility.h"

namespace Numpp{
    class Vector
    {
    public:
        class Iterator
            : public std::iterator<std::random_access_iterator_tag,double,std::pair<bool,size_t>>
        {
        public:
            typedef std::pair<bool,size_t> diff_t;
            Iterator(Vector * container, size_t position) noexcept;

            // generic iterator
            Iterator(const Iterator &it) noexcept;
            Iterator(Iterator &&it) noexcept;
            Iterator& operator=(const Iterator &it) noexcept;
            Iterator& operator=(Iterator &&it) noexcept;
            void operator++();

            // input/output
            bool operator==(const Iterator &other) const noexcept;
            bool operator!=(const Iterator &other) const noexcept;
            double& operator*() const;

            // forward
            Iterator() noexcept;

            // bidirectional
            void operator--();

            // random
            bool operator<=(const Iterator &other) const noexcept;
            bool operator>=(const Iterator &other) const noexcept;
            bool operator<(const Iterator &other) const noexcept;
            bool operator>(const Iterator &other) const noexcept;
            Iterator operator+(const diff_t offset) const;
            Iterator operator+(const size_t offset) const;
            Iterator operator-(const diff_t offset) const;
            Iterator operator-(const size_t offset) const;
            diff_t operator-(const Iterator other) const;
            void operator+=(const diff_t offset);
            void operator+=(const size_t offset);
            void operator-=(const diff_t offset);
            void operator-=(const size_t offset);
            double& operator[](const diff_t offset) const;
        private:
            size_t size() const;
            Vector *data;
            size_t position;
        };

        // Arithmetic
        virtual ~Vector();
        virtual Vector* operator+(const Vector* other) const;
        virtual void operator+=(const Vector* other);
        virtual Vector* operator-(const Vector* other) const;
        virtual void operator-=(const Vector* other);
        virtual double operator*(const Vector* other) const;
        virtual Vector* operator*(const double scale) const;
        virtual void operator*=(const double scale);

        // Comparison
        virtual bool operator==(const Vector* other) const noexcept;
        virtual bool operator!=(const Vector* other) const noexcept;
        virtual bool operator<=(const Vector* other) const noexcept;
        virtual bool operator>=(const Vector* other) const noexcept;
        virtual bool operator<(const Vector* other) const noexcept;
        virtual bool operator>(const Vector* other) const noexcept;

        // iterating
        virtual Iterator begin() const noexcept;
        virtual Iterator end() const noexcept;
        virtual Iterator storageBegin() const noexcept=0;
        virtual Iterator storageEnd() const noexcept=0;
        virtual void storageAdvance(Iterator &it) const=0;

        // Access
        virtual double& operator[](const size_t point) const noexcept=0;
        virtual double& at(const size_t point) const;
        virtual void swap(const size_t x1, const size_t x2);
        
        // Serialization
        virtual std::string print() const noexcept;
        static Vector* scan(const std::string &in);

        // Inspect
        virtual size_t size() const noexcept=0;
        virtual StorageType storageType() const noexcept=0;

        // Copying
        virtual Vector* allocSameType(size_t size) const=0;
        virtual Vector* allocCopy() const=0;
    };

    class VectorStorageLinear : public Vector
    {
    public:
        VectorStorageLinear();
        VectorStorageLinear(const size_t size);
        VectorStorageLinear(const size_t size, const double fill);
        VectorStorageLinear(const Vector *other);
        VectorStorageLinear(const VectorStorageLinear &other);
        VectorStorageLinear(VectorStorageLinear &&other);
        ~VectorStorageLinear();
        Iterator storageBegin() const noexcept;
        Iterator storageEnd() const noexcept;
        void storageAdvance(Iterator &it) const;
        double& operator[](const size_t point) const noexcept;
        std::string print() const noexcept;
        size_t size() const noexcept;
        StorageType storageType() const noexcept;
        Vector* allocSameType(size_t size) const;
        Vector* allocCopy() const;
    private:
        double* data_m;
        size_t size_m;
    };

    class VectorStorageSparse : public Vector
    {
    public:
        VectorStorageSparse();
        VectorStorageSparse(const size_t idx, const double value);
        VectorStorageSparse(const Vector *other);
        ~VectorStorageSparse();
        Vector* operator+(const Vector* other) const;
        void operator+=(const Vector* other);
        Vector* operator-(const Vector* other) const;
        void operator-=(const Vector* other);
        double operator*(const Vector* other) const;
        Vector* operator*(const double scale) const;
        void operator*=(const double scale);
        bool operator==(const Vector* other) const noexcept;
        bool operator!=(const Vector* other) const noexcept;
        bool operator<=(const Vector* other) const noexcept;
        bool operator>=(const Vector* other) const noexcept;
        bool operator<(const Vector* other) const noexcept;
        bool operator>(const Vector* other) const noexcept;
        Iterator storageBegin() const noexcept;
        Iterator storageEnd() const noexcept;
        void storageAdvance(Iterator &it) const;
        double& operator[](const size_t point) const noexcept;
        std::string print() const noexcept;
        size_t size() const noexcept;
        StorageType storageType() const noexcept;
        Vector* allocSameType(size_t size) const;
        Vector* allocCopy() const;
    private:
        std::map<size_t, double> *data_m;
        size_t size_m;
    };
}

namespace std {
    void swap(Numpp::VectorStorageSparse &a, Numpp::VectorStorageSparse &b);
    void swap(Numpp::VectorStorageLinear &a, Numpp::VectorStorageLinear &b);
}

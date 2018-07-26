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

#include <map>
#include <iterator>
#include "utility/utility.h"

namespace numpp{
    class VectorStorage
    {
    public:
        class Iterator
            : public std::iterator<std::random_access_iterator_tag,double,std::pair<bool,size_t>>
        {
        public:
            Iterator(VectorStorage * container, size_t position);

            // generic iterator
            Iterator(const Iterator it);
            Iterator(const Iterator &it);
            Iterator(Iterator &&it);
            Iterator& operator=(const Iterator &it);
            Iterator& operator=(Iterator &&it);
            void operator++();

            // input/output
            bool operator==(const Iterator &other) const noexcept;
            bool operator!=(const Iterator &other) const noexcept;
            double& operator*() const;

            // forward
            Iterator();

            // bidirectional
            void operator--();

            // random
            bool operator<=(const Iterator &other) const noexcept;
            bool operator>=(const Iterator &other) const noexcept;
            bool operator<(const Iterator &other) const noexcept;
            bool operator>(const Iterator &other) const noexcept;
            Iterator operator+(const size_t offset) const;
            Iterator operator-(const size_t offset) const;
            std::pair<bool,size_t> operator-(const Iterator other) const noexcept;
            void operator+=(const size_t offset);
            void operator-=(const size_t offset);
            double& operator[](bool negative, size_t offset) const;
            double& operator[](pair<bool, size_t> offset) const;
        private:
            VectorStorage *data;
            size_t position_m;
        };
        // Constructors
        virtual VectorStorage();
        virtual VectorStorage(const VectorStorage &other);
        virtual ~VectorStorage() noexcept;
        virtual double operator[](const size_t position) const noexcept;
        virtual void operator[](const size_t position, const double val);
        virtual size_t size() const noexcept;
        virtual StorageType storageType() const noexcept;
        virtual Iterator begin() const noexcept;
        virtual Iterator end() const noexcept;
    };
    class VectorStorageLinear : public VectorStorage
    {
    public:
        VectorStorageLinear();
        VectorStorageLinear(const size_t size);
        VectorStorageLinear(const size_t size, const double fill);
        VectorStorageLinear(const VectorStorage &other);
        VectorStorageLinear(const VectorStorageLinear &other);
        VectorStorageLinear(VectorStorageLinear &&other);
        ~VectorStorageLinear();
        double operator[](const size_t position) const noexcept;
        void operator[](const size_t position, const double val);
        size_t size() const noexcept;
        StorageType storageType() const noexcept; 
        Iterator begin() const noexcept;
        Iterator end() const noexcept;
    private:
        double* data_m;
        size_t size_m;
    };
    class VectorStorageSparse : public VectorStorage
    {
    public:
        VectorStorageSparse();
        VectorStorageSparse(const size_t idx, const double value);
        VectorStorageSparse(const VectorStorage &other);
        ~VectorStorageSparse();
        double operator[](const size_t position) const noexcept;
        void operator[](const size_t position, const double val);
        size_t size() const noexcept;
        StorageType storageType() const noexcept; 
        Iterator begin() const noexcept;
        Iterator end() const noexcept;
    private:
        std::map<size_t, double> *data_m;
        size_t size_m;
    };
}

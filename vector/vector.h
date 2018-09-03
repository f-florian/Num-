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

#include <iterator>
#include <type_traits>
#include "utility.h"

namespace Numpp{
    class Vector
    {
    public:
        template <typename T>
        class t_Iterator
            : public std::iterator<std::random_access_iterator_tag, T, std::pair<bool,size_t>>
        {
        public:
            typedef typename std::iterator_traits<t_Iterator>::difference_type diff_t;
            typedef typename std::conditional<std::is_const<T>::value, const Vector*, Vector*>::type VType;

            t_Iterator(VType container, size_t position) noexcept;

            // generic iterator
            t_Iterator(const t_Iterator &it) noexcept;
            t_Iterator(t_Iterator &&it) noexcept;
            t_Iterator& operator=(const t_Iterator &it) noexcept;
            t_Iterator& operator=(t_Iterator &&it) noexcept;
            void operator++();
            void operator++([[maybe_unused]] int);

            // input/output
            bool operator==(const t_Iterator &other) const noexcept;
            bool operator!=(const t_Iterator &other) const noexcept;
            double operator*() const;

            // forward
            t_Iterator() noexcept;

            // bidirectional
            void operator--();
            void operator--([[maybe_unused]] int);

            // random
            bool operator<=(const t_Iterator &other) const noexcept;
            bool operator>=(const t_Iterator &other) const noexcept;
            bool operator<(const t_Iterator &other) const noexcept;
            bool operator>(const t_Iterator &other) const noexcept;
            t_Iterator operator+(const diff_t offset) const;
            t_Iterator operator+(const size_t offset) const;
            t_Iterator operator-(const diff_t offset) const;
            t_Iterator operator-(const size_t offset) const;
            diff_t operator-(const t_Iterator other) const;
            void operator+=(const diff_t offset);
            void operator+=(const size_t offset);
            void operator-=(const diff_t offset);
            void operator-=(const size_t offset);
            double operator[](const diff_t offset) const;

            // more
            size_t index() const noexcept;
            void set(size_t position);
        protected:
            size_t size() const;
            VType data;
            size_t position;
        };
        
        typedef t_Iterator<double> Iterator;
        typedef t_Iterator<const double> ConstIterator;

        // Arithmetic
        virtual ~Vector();
        virtual Vector* operator+(const Vector* const other) const;
        virtual void operator+=(const Vector* const other);
        virtual Vector* operator-(const Vector* const other) const;
        virtual void operator-=(const Vector* const other);
        virtual double operator*(const Vector* const other) const;
        virtual Vector* operator*(const double scale) const;
        virtual void operator*=(const double scale);

        // Comparison
        virtual bool operator==(const Vector* const other) const noexcept;
        virtual bool operator!=(const Vector* const other) const noexcept;
        virtual bool operator<=(const Vector* const other) const noexcept;
        virtual bool operator>=(const Vector* const other) const noexcept;
        virtual bool operator<(const Vector* const other) const noexcept;
        virtual bool operator>(const Vector* const other) const noexcept;

        // iterating
        virtual Iterator begin() noexcept;
        virtual Iterator end() noexcept;
        virtual Iterator storageBegin() noexcept=0;
        virtual Iterator storageEnd() noexcept=0;
        virtual ConstIterator cbegin() const noexcept;
        virtual ConstIterator cend() const noexcept;
        virtual ConstIterator storagecBegin() const noexcept=0;
        virtual ConstIterator storagecEnd() const noexcept=0;
        virtual void storageAdvance(Iterator &it) const=0;
        virtual void storageAdvance(ConstIterator &it) const=0;

        // Access
        virtual double operator[](const size_t point) const noexcept=0;
        virtual double operator[](const Iterator::diff_t point) const noexcept;
        virtual double at(const size_t point) const;
        virtual double at(const Iterator::diff_t point) const;
        virtual void swap(const size_t x1, const size_t x2);
        virtual void set(const size_t point, const double val);
        virtual void set(const Iterator::diff_t point, const double val);
        
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
}

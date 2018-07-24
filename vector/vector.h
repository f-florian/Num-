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
#include "utility/utility.h"
#include <initializer_list>

namespace Numpp{
    class Vector
    {
    public:
        // Constructors
        Vector()=delete;
        Vector(const StorageType type=StorageType::dense);
        Vector(const size_t size, const double value, const StorageType type=StorageType::dense);
        Vector(const std::initializer_list<double> values);
        Vector(const std::initializer_list<std::pair<size_t,double>> values);
        Vector(const Vector &other);
        Vector(Vector &&other);
        ~Vector();
        
        // Assignment
        Vector& operator=(const Vector &other)=delete;
        Vector& operator=(Vector &&other) noexcept;
	
        // Arithmetic
        Vector operator+(const Vector &other) const;
        void operator+=(const Vector &other);
        Vector operator-(const Vector &other) const;
        void operator-=(const Vector &other);
        double operator*(const Vector &other) const;
        Vector operator*(const double scale) const;
        void operator*=(const double scale);

        // Comparison
        bool operator==(const Vector &other) const noexcept;
        bool operator!=(const Vector &other) const noexcept;
        bool operator<=(const Vector &other) const noexcept;
        bool operator>=(const Vector &other) const noexcept;
        bool operator<(const Vector &other) const noexcept;
        bool operator>(const Vector &other) const noexcept;

        // Other
        std::string print() const noexcept;
        double& operator[](const size_t point) const noexcept;
        double& at(const size_t point) const;
        void swap(const size_t x1, const size_t x2);
        void swap(Vector &other) noexcept;
        void swap(Vector &&other) noexcept;
    private:
        VectorStorage *storage;
    };
}

namespace std {
    void swap(Numpp::Vector &a, Numpp::Vector& b);
}

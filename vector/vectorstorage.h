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

#include <map>

namespace numpp{
    class VectorStorage
    {
    public:
        // Constructors
        virtual VectorStorage();
        virtual ~VectorStorage() noexcept;
        virtual double operator[](const size_t position) const noexcept;
    };
    class VectorStorageLinear : public VectorStorage
    {
    public:
        VectorStorageLinear();
        VectorStorageLinear(const size_t size);
        VectorStorageLinear(const size_t size, const double fill);
        ~VectorStorageLinear();
        double operator[](const size_t position) const noexcept;
    private:
        double* data_m;
        size_t size_m;
    };
    class VectorStorageSparse : public VectorStorage
    {
    public:
        VectorStorageSparse();
        VectorStorageSparse(const size_t idx, const double value);
        ~VectorStorageSparse();
        double operator[](const size_t position) const noexcept;
    private:
        double *data_m;
        std::map<size_t, size_t> idx;
    };
}

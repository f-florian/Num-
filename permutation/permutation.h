/***************************************************************************
 * Copyright (C) 2017 Francesco Florian
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

#include <string>
#include <initializer_list>

class Permutation
{
public:
    // Constructors
    Permutation(size_t maximum);
    Permutation(size_t maximum, size_t e1, size_t e2);
    Permutation(std::initializer_list<size_t> list);
    Permutation(size_t maximum, std::initializer_list<size_t> list);
    Permutation(const Permutation & other);
    Permutation(Permutation && other) noexcept;
    ~Permutation() noexcept;
	
    // Assignment
    Permutation& operator=(const Permutation &other)=delete;
    Permutation& operator=(Permutation &&other) noexcept;
	
    // Arithmetic
    Permutation operator* (const Permutation &other) const;
    void operator*= (const Permutation &other);
    Permutation inverse() const;
    void invert() noexcept;
    Permutation operator/ (const Permutation &other) const;
    void operator/= (const Permutation &other) noexcept;

    // Comparison
    bool operator==(const Permutation &other) const noexcept;
    bool operator<=(const Permutation &other) const noexcept;
    bool operator>=(const Permutation &other) const noexcept;
    bool operator!=(const Permutation &other) const noexcept;
    bool operator<(const Permutation &other) const noexcept;
    bool operator>(const Permutation &other) const noexcept;

    // Other
    std::string print() const noexcept;
    size_t operator[](const size_t point) const;
    void swap(const size_t x1, const size_t x2);
    void swapExisting(const size_t x1, const size_t x2) noexcept
	void swap(Permutation &&other) noexcept;
private:
    size_t maximum;
    vector<size_t> permutation;
};

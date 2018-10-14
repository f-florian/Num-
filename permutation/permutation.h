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

#include <string>
#include <initializer_list>

namespace Numpp{
    /**
     * Class for storing a permutation
     */
    class Permutation
    {
    public:
        Permutation(size_t maximum);                                                                //!< Construct identity
        Permutation(size_t maximum, size_t e1, size_t e2);                                          //!< Construct transposition
        Permutation(std::initializer_list<size_t> list);                                            //!< Construct from initializer_list
        Permutation(size_t maximum, std::initializer_list<size_t> list);                            //!< Construct from initializer_list
        Permutation(const Permutation & other);                                                     //!< Copy constructor
        Permutation(Permutation && other) noexcept;                                                 //!< Move constructor
        ~Permutation() noexcept;                                                                    //!< Destructor

        Permutation& operator=(const Permutation &other)=delete;                                    //!< Copy assignment
        Permutation& operator=(Permutation &&other) noexcept;                                       //!< Move assignment

        Permutation operator* (const Permutation &other) const;                                     //!< Composition
        void operator*= (const Permutation &other);                                                 //!< Composition and assignment
        Permutation inverse() const;                                                                //!< Compute inverse
        void invert() noexcept;                                                                     //!< Invert current permutation
        Permutation operator/ (const Permutation &other) const;                                     //!< Compose with inverse
        void operator/= (const Permutation &other) noexcept;                                        //!< Compose with inverse and assignment

        bool operator==(const Permutation &other) const noexcept;                                   //!< Comparison (equality)
        bool operator<=(const Permutation &other) const noexcept;                                   //!< Comparison (less or equal)
        bool operator>=(const Permutation &other) const noexcept;                                   //!< Comparison (greater or equal)
        bool operator!=(const Permutation &other) const noexcept;                                   //!< Comparison (inequality)
        bool operator<(const Permutation &other) const noexcept;                                    //!< Comparison (less}
        bool operator>(const Permutation &other) const noexcept;                                    //!< Comparison (greater)

        std::string print() const noexcept;                                                         //!< Print in a standardized and human readable form
        size_t operator[](const size_t point) const;                                                //!< Access element at position
        void swap(const size_t x1, const size_t x2);                                                //!< Swap elements
        void swapExisting(const size_t x1, const size_t x2) noexcept;                               //!< Swap elements
        void swap(Permutation &other) noexcept;                                                     //!< Swap with other permutation
    private:
        size_t maximum;                                                                             //!< Set dimension
        vector<size_t> permutation;                                                                 //!< Permutiton storage
    };
}

namespace std {
    inline void swap(Permutation &a, Permutation &b) noexcept {a.swap(b);}                          //!< Swap with other permutation
}

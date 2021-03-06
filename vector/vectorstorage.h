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
    /**
     * Vector class using dense storage
     *
     * Storage is implemented as array allocated at construction or resize time
     */
    class VectorStorageLinear : public Vector
    {
    public:
        VectorStorageLinear();                                                                      //!< Empty constructor
        VectorStorageLinear(const size_t size);                                                     //!< Constuct Vector of given size and fill with 0
        VectorStorageLinear(const size_t size, const double fill);                                  //!< Constuct Vector of given size and fill with given value
        VectorStorageLinear(const Vector * const other);                                            //!< Copy vector
        VectorStorageLinear(const VectorStorageLinear &other);                                      //!< Copy Vector of same type
        VectorStorageLinear(VectorStorageLinear &&other);                                           //!< Move Vector of same type
        VectorStorageLinear& operator=(const VectorStorageLinear &other);                           //!< Copy Vector and assign
        VectorStorageLinear& operator=(VectorStorageLinear &&other);                                //!< Move Vector and assign
        ~VectorStorageLinear();                                                                     //!< Destructor
        void assign(const size_t size, double * const data);                                        //!< Assign content from a standard c array
        const double* data() const;                                                                 //!< Return data in form of a standard c array
        double* stealData();                                                                        //!< Return data in form of a standard c array, sstealing it from the object
        Iterator begin() noexcept;                                                                  //!< Return Iterator to begin
        Iterator end() noexcept;                                                                    //!< Return Iterator to end
        Iterator storageBegin() noexcept;                                                           //!< Return Iterator to storage begin
        Iterator storageEnd() noexcept;                                                             //!< Return Iterator to storage end
        ConstIterator cbegin() const noexcept;                                                      //!< Return ConstIterator to begin      
        ConstIterator cend() const noexcept;                                                        //!< Return ConstIterator to end         
        ConstIterator storagecBegin() const noexcept;                                               //!< Return ConstIterator to storage beg
        ConstIterator storagecEnd() const noexcept;                                                 //!< Return ConstIterator to storage end
        void storageAdvance(Iterator &it) const;                                                    //!< Advance in storage
        void storageAdvance(ConstIterator &it) const;                                               //!< Advance in storage
        double operator[](const size_t point) const noexcept;                                       //!< Access element
        std::string print() const noexcept;                                                         //!< Write Vector to string in a standardized manner
        size_t size() const noexcept;                                                               //!< Get size
        StorageType storageType() const noexcept;                                                   //!< Get storage type
        Vector* allocSameType(size_t size) const;                                                   //!< Allocate a Vector of the same type and given size
        Vector* allocCopy() const;                                                                  //!< Allocate a copy of this Vector
        void swap(const size_t x1, const size_t x2);                                                //!< Swap elements
        void swap(VectorStorageLinear &other) noexcept;                                             //!< Swap Vectors
    private:
        double* data_m;                                                                             //!< Vector data
        size_t size_m;                                                                              //!< Vector size
    };

    /**
     * Vector class using sparse storage
     *
     * Storage is implemented as a map
     */
    class VectorStorageSparse : public Vector
    {
    public:
        VectorStorageSparse();                                                                      //!< Empty constructor
        VectorStorageSparse(const size_t idx, const double value);                                  //!< Construct Vector with given value at position and 0 otherwise
        VectorStorageSparse(const Vector * const other);                                            //!< Copy vector
        VectorStorageSparse(const VectorStorageSparse &other);                                      //!< Copy Vector of same type
        VectorStorageSparse(VectorStorageSparse &&other) noexcept;                                  //!< Move Vector of same type
        ~VectorStorageSparse();                                                                     //!< Destructor
        Vector* operator+(const Vector* const other) const;                                         //!< Sum Vector
        void operator+=(const Vector* const other);                                                 //!< Sum Vector and assign to this
        Vector* operator-(const Vector* const other) const;                                         //!< Subtract Vector
        void operator-=(const Vector* const other);                                                 //!< Subtract Vector and assign to this
        double operator*(const Vector* const other) const;                                          //!< Dot product
        Vector* operator*(const double scale) const;                                                //!< Scale
        void operator*=(const double scale);                                                        //!< Scale and assign to this
        bool operator==(const Vector* const other) const noexcept;                                  //!< Comparison (equality)
        bool operator!=(const Vector* const other) const noexcept;                                  //!< Comparison (inequality)
        bool operator<=(const Vector* const other) const noexcept;                                  //!< Comparison (less or equal)
        bool operator>=(const Vector* const other) const noexcept;                                  //!< Comparison (greater or equal)
        bool operator<(const Vector* const other) const noexcept;                                   //!< Comparison (less)
        bool operator>(const Vector* const other) const noexcept;                                   //!< Comparison (greater)
        virtual Iterator begin() noexcept;                                                          //!< Return Iterator to begin
        virtual Iterator end() noexcept;                                                            //!< Return Iterator to end
        virtual Iterator storageBegin() noexcept;                                                   //!< Return Iterator to storage begin
        virtual Iterator storageEnd() noexcept;                                                     //!< Return Iterator to storage end
        virtual ConstIterator cbegin() const noexcept;                                              //!< Return ConstIterator to begin
        virtual ConstIterator cend() const noexcept;                                                //!< Return ConstIterator to end
        virtual ConstIterator storagecBegin() const noexcept;                                       //!< Return ConstIterator to storage begin
        virtual ConstIterator storagecEnd() const noexcept;                                         //!< Return ConstIterator to storage end
        virtual void storageAdvance(Iterator &it) const;                                            //!< Advance in storage
        virtual void storageAdvance(ConstIterator &it) const;                                       //!< Advance in storage
        double operator[](const size_t point) const noexcept;                                       //!< Access element
        void set(const size_t point, const double val);                                             //!< Set value at position
        std::string print() const noexcept;                                                         //!< Write Vector to string in a standardized manner
        size_t size() const noexcept;                                                               //!< Get size
        StorageType storageType() const noexcept;                                                   //!< Get storage type
        Vector* allocSameType(size_t size) const;                                                   //!< Allocate a Vector of the same type and given size
        Vector* allocCopy() const;                                                                  //!< Allocate a copy of this Vector
        void swap(const size_t x1, const size_t x2);                                                //!< Swap elements
        void swap(VectorStorageSparse &other) noexcept;                                             //!< Swap Vectors
    private:
        std::map<size_t, double> data_m;                                                            //!< Vector data                                            
        size_t size_m;                                                                              //!< Vector size                                      
    };
}

namespace std {
    inline void swap(Numpp::VectorStorageSparse &a, Numpp::VectorStorageSparse &b) {a.swap(b);}     //!< Swap Vectors of the same type; non-member version
    inline void swap(Numpp::VectorStorageLinear &a, Numpp::VectorStorageLinear &b) {a.swap(b);}     //!< Swap Vectors of the same type; non-member version
}

#endif /* VECTORSTORAGE_H */

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
#ifndef VECTORVIEW_H
#define VECTORVIEW_H

#include "vector.h"
#include "vectorstorage.h"
#include "indexset.h"

namespace Numpp{
    /**
     * Create and manipulate Vectors with permuted indices
     */
    class VectorView : public Vector
    {
    public:
        VectorView(Vector *data);                                                                   //!< Construct with identity permutation
        VectorView(Vector *data, IndexSet &indices);                                                //!< Construct with given permutation
        VectorView(Vector *data, IndexSet &&indices);                                               //!< Construct with given permutation
        VectorView(Vector *data, bool own=false);                                                   //!< Construct with identity permutation
        VectorView(Vector *data, IndexSet &indices, bool own=false);                                //!< Construct with given permutation
        VectorView(Vector *data, IndexSet &&indices, bool own=false);                               //!< Construct with given permutation
        VectorView(VectorView &other);                                                              //!< Copy constructor
        VectorView(VectorView &&other);                                                             //!< Move constructor
        VectorView(VectorView &other, IndexSet &indices, bool own=false);                           //!< Copy constructor
        VectorView(VectorView &&other, IndexSet &&indices);                                         //!< Move constructor
        virtual ~VectorView();                                                                      //!< Destructor
        virtual void operator+=(const Vector* const other);                                         //!< sum
        virtual void operator-=(const Vector* const other);                                         //!< difference
        virtual double operator*(const Vector* const other) const;                                  //!< Dot product
        virtual void operator*=(const double scale);                                                //!< Scale all elements

        // Comparison
        virtual bool operator==(const Vector* const other) const noexcept;                          //!< Comparison (equality)
        virtual bool operator!=(const Vector* const other) const noexcept;                          //!< Comparison (inequalty)
        virtual bool operator<=(const Vector* const other) const noexcept;                          //!< Comparison (less or equal)
        virtual bool operator>=(const Vector* const other) const noexcept;                          //!< Comparison (greater or equal)
        virtual bool operator<(const Vector* const other) const noexcept;                           //!< Comparison (less or equal)
        virtual bool operator>(const Vector* const other) const noexcept;                           //!< Comparison (greater or equal)

        // iterating
        virtual Iterator storageBegin() noexcept;                                                   //!< Iterator to first stored element
        virtual Iterator storageEnd() noexcept;                                                     //!< Iterator to past-the-last stored element
        virtual ConstIterator cbegin() const noexcept;                                              //!< ConstIterator to begin
        virtual ConstIterator cend() const noexcept;                                                //!< ConstIterator to begnd
        virtual ConstIterator storagecBegin() const noexcept;                                       //!< ConstIterator to first stored element
        virtual ConstIterator storagecEnd() const noexcept;                                         //!< ConstIterator to past-the-last stored element
        virtual void storageAdvance(Iterator &it) const;                                            //!< Advance Iterator to next stored item
        virtual void storageAdvance(ConstIterator &it) const;                                       //!< Advance ConstIterator to next stored item

        // Access
        virtual double operator[](const size_t point) const noexcept;                               //!< Access element
        virtual double operator[](const Iterator::diff_t point) const noexcept;                     //!< Access element
        virtual void set(const size_t point, const double val);                                     //!< set value element at position
        virtual void set(const Iterator::diff_t point, const double val);                           //!< set value element at abs(position)
        virtual void resize(size_t size);                                                           //!< resize
        
        // Serialization
        virtual std::string print() const noexcept;                                                 //!< Write to string
        static Vector* scan(const std::string &in);                                                 //!< Construct from string

        // Inspect
        virtual size_t size() const noexcept {return data->size};                                   //!< Get size \return Size of data
        virtual StorageType storageType() const noexcept;                                           //!< Get storage Type

        // Copying
        virtual Vector* allocSameType(size_t size) const;                                           //!< Allocate a Vector of ginven size and same type as the caller
        virtual Vector* allocCopy() const;                                                          //!< Allocate a copy
    protected:
        virtual double& getref(size_t point);                                                       //!< Get a reference to the element at point
        IndexSet indexMapping_m;                                                                    //!< Index mapping
        Vector *data_m;                                                                             //!< Original Vector
        bool owner;                                                                                 //!< Vector ownership flag
    };
}

#endif /* VECTORVIEW_H */

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
        virtual Vector* operator+(const Vector* const other) const;                                 //!< sum
        virtual void operator+=(const Vector* const other);                                         //!< sum
        virtual Vector* operator-(const Vector* const other) const;                                 //!< difference
        virtual void operator-=(const Vector* const other);                                         //!< difference
        virtual double operator*(const Vector* const other) const;                                  //!< Dot product
        virtual Vector* operator*(const double scale) const;                                        //!< Scale all elements
        virtual void operator*=(const double scale);                                                //!< Scale all elements

        // Comparison
        virtual bool operator==(const Vector* const other) const noexcept;                          //!< Comparison (equality)
        virtual bool operator!=(const Vector* const other) const noexcept;                          //!< Comparison (inequalty)
        virtual bool operator<=(const Vector* const other) const noexcept;                          //!< Comparison (less or equal)
        virtual bool operator>=(const Vector* const other) const noexcept;                          //!< Comparison (greater or equal)
        virtual bool operator<(const Vector* const other) const noexcept;                           //!< Comparison (less or equal)
        virtual bool operator>(const Vector* const other) const noexcept;                           //!< Comparison (greater or equal)

        // iterating
        virtual Iterator begin() noexcept;                                                          //!< Iterator to begin
        virtual Iterator end() noexcept;                                                            //!< Iterator to end
        virtual Iterator storageBegin() noexcept=0;                                                 //!< Iterator to first stored element
        virtual Iterator storageEnd() noexcept=0;                                                   //!< Iterator to past-the-last stored element
        virtual ConstIterator cbegin() const noexcept;                                              //!< ConstIterator to begin
        virtual ConstIterator cend() const noexcept;                                                //!< ConstIterator to begnd
        virtual ConstIterator storagecBegin() const noexcept=0;                                     //!< ConstIterator to first stored element
        virtual ConstIterator storagecEnd() const noexcept=0;                                       //!< ConstIterator to past-the-last stored element
        virtual void storageAdvance(Iterator &it) const=0;                                          //!< Advance Iterator to next stored item
        virtual void storageAdvance(ConstIterator &it) const=0;                                     //!< Advance ConstIterator to next stored item
        virtual void transform(double (*fn)(double));                                               //!< Apply unary function to all elemenst
        virtual void transform(doubleUnary fn);                                                     //!< Apply unary function to all elemenst
        virtual void transform(double (*fn)(double,double), const Vector * const other);            //!< Apply binary function to all elements
        virtual void transform(doubleBinary fn, const Vector * const other);                        //!< Apply binary function to all elements
        virtual Vector* ctransform(double (*fn)(double,double), const Vector * const other) const;  //!< Apply binary function to all elements
        virtual Vector* ctransform(doubleBinary fn, const Vector * const other) const;              //!< Apply binary function to all elements

        // Access
        virtual double operator[](const size_t point) const noexcept=0;                             //!< Access element
        virtual double operator[](const Iterator::diff_t point) const noexcept;                     //!< Access element
        virtual double at(const size_t point) const;                                                //!< Access element
        virtual ConstIterator cAt(const size_t point) const;                                        //!< Access element through ConstIterator
        virtual Iterator at(const size_t point);                                                    //!< Access element through Iterator
        virtual void swap(const size_t x1, const size_t x2);                                        //!< swap elements
        virtual void set(const size_t point, const double val);                                     //!< set value element at position
        virtual void set(const Iterator::diff_t point, const double val);                           //!< set value element at abs(position)
        virtual void resize(size_t size);                                                           //!< resize
        
        // Serialization
        virtual std::string print() const noexcept;                                                 //!< Write to string
        static Vector* scan(const std::string &in);                                                 //!< Construct from string

        // Inspect
        virtual size_t size() const noexcept=0;                                                     //!< Get size
        virtual StorageType storageType() const noexcept=0;                                         //!< Get storage Type

        // Copying
        virtual Vector* allocSameType(size_t size) const=0;                                         //!< Allocate a Vector of ginven size and same type as the caller
        virtual Vector* allocCopy() const=0;                                                        //!< Allocate a copy
    protected:
        virtual double& getref(size_t point);                                                       //!< Get a reference to the element at point
        IndexSet indexMapping_m;                                                                    //!< Index mapping
        Vector *data_m;                                                                             //!< Original Vector
        bool owner;                                                                                 //!< Vector ownership flag
    };
}

#endif /* VECTORVIEW_H */

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

#ifndef VECTOR_H
#define VECTOR_H

#include <iterator>
#include <type_traits>
#include <functional>
#include "utility.h"

namespace Numpp{
    /**
     * Virtual base class for vector objects.
     */
    class Vector
    {
    public:
        /**
         * template iterator to a Vector object. 
         *
         * Random access iterator, uses the virtual functions from Vector
         */
        template <typename T>
        class t_Iterator
            : public std::iterator<std::random_access_iterator_tag, T, std::pair<bool,size_t>>
        {
        public:
            /**
             * Iterator difference.
             */
            typedef typename std::iterator_traits<t_Iterator>::difference_type diff_t;
            /**
             * Vector type used as reference.
             */
            typedef typename std::conditional<std::is_const<T>::value, const Vector*, Vector*>::type VType;

            t_Iterator(VType container, size_t position) noexcept;                                      //!< Constructor from container and index

            // generic iterator
            t_Iterator(const t_Iterator &it) noexcept;                                                  //!< Copy constructor
            t_Iterator(t_Iterator &&it) noexcept;                                                       //!< Move constructor
            t_Iterator& operator=(const t_Iterator &it) noexcept;                                       //!< Copy assignment
            t_Iterator& operator=(t_Iterator &&it) noexcept;                                            //!< Move assignment
            void operator++();                                                                          //!< preincrement
            void operator++([[maybe_unused]] int);                                                      //!< postincrement

            // input/output
            bool operator==(const t_Iterator &other) const noexcept;                                    //!< Comparison (equality)
            bool operator!=(const t_Iterator &other) const noexcept;                                    //!< Comparison (inequality)
            double operator*() const;                                                                   //!< deference

            // forward
            t_Iterator() noexcept;                                                                      //!< Default constructor

            // bidirectional
            void operator--();                                                                          //!< predecrement
            void operator--([[maybe_unused]] int);                                                      //!< postdecrement

            // random
            bool operator<=(const t_Iterator &other) const noexcept;                                    //!< Comparison (less or equal)
            bool operator>=(const t_Iterator &other) const noexcept;                                    //!< Comparison (greater or equal)
            bool operator<(const t_Iterator &other) const noexcept;                                     //!< Comparison (less)
            bool operator>(const t_Iterator &other) const noexcept;                                     //!< Comparison (greater)
            t_Iterator operator+(const diff_t offset) const;                                            //!< advance
            t_Iterator operator+(const size_t offset) const;                                            //!< advance
            t_Iterator operator-(const diff_t offset) const;                                            //!< advance
            t_Iterator operator-(const size_t offset) const;                                            //!< advance
            diff_t operator-(const t_Iterator other) const;                                             //!< get difference
            void operator+=(const diff_t offset);                                                       //!< advance
            void operator+=(const size_t offset);                                                       //!< advance
            void operator-=(const diff_t offset);                                                       //!< advance
            void operator-=(const size_t offset);                                                       //!< advance
            double operator[](const diff_t offset) const;                                               //!< access element

            // more
            size_t index() const noexcept;                                                              //!< get index
            void set(size_t position);                                                                  //!< set index
        protected:
            size_t size() const;                                                                        //!< get container size
            VType data;                                                                                 //!< pointer to referenced container
            size_t position;                                                                            //!< position
        };

        typedef std::function<double(double)> doubleUnary;                                              //!< Unary function returning double
        typedef std::function<double(double,double)> doubleBinary;                                      //!< Binnary function returning double
        typedef t_Iterator<double> Iterator;                                                            //!< iterator to Vector
        typedef t_Iterator<const double> ConstIterator;                                                 //!< const iterator to Vector

        // Arithmetic
        virtual ~Vector();                                                                              //!< Destructor
        virtual Vector* operator+(const Vector* const other) const;                                     //!< sum
        virtual void operator+=(const Vector* const other);                                             //!< sum
        virtual Vector* operator-(const Vector* const other) const;                                     //!< difference
        virtual void operator-=(const Vector* const other);                                             //!< difference
        virtual double operator*(const Vector* const other) const;                                      //!< Dot product
        virtual Vector* operator*(const double scale) const;                                            //!< Scale all elements
        virtual void operator*=(const double scale);                                                    //!< Scale all elements

        // Comparison
        virtual bool operator==(const Vector* const other) const noexcept;                              //!< Comparison (equality)
        virtual bool operator!=(const Vector* const other) const noexcept;                              //!< Comparison (inequalty)
        virtual bool operator<=(const Vector* const other) const noexcept;                              //!< Comparison (less or equal)
        virtual bool operator>=(const Vector* const other) const noexcept;                              //!< Comparison (greater or equal)
        virtual bool operator<(const Vector* const other) const noexcept;                               //!< Comparison (less or equal)
        virtual bool operator>(const Vector* const other) const noexcept;                               //!< Comparison (greater or equal)

        // iterating
        virtual Iterator begin() noexcept;                                                              //!< Iterator to begin
        virtual Iterator end() noexcept;                                                                //!< Iterator to end
        virtual Iterator storageBegin() noexcept=0;                                                     //!< Iterator to first stored element
        virtual Iterator storageEnd() noexcept=0;                                                       //!< Iterator to past-the-last stored element
        virtual ConstIterator cbegin() const noexcept;                                                  //!< ConstIterator to begin
        virtual ConstIterator cend() const noexcept;                                                    //!< ConstIterator to begnd
        virtual ConstIterator storagecBegin() const noexcept=0;                                         //!< ConstIterator to first stored element
        virtual ConstIterator storagecEnd() const noexcept=0;                                           //!< ConstIterator to past-the-last stored element
        virtual void storageAdvance(Iterator &it) const=0;                                              //!< Advance Iterator to next stored item
        virtual void storageAdvance(ConstIterator &it) const=0;                                         //!< Advance ConstIterator to next stored item
        virtual void transform(double (*fn)(double));                                                   //!< Apply unary function to all elemenst
        virtual void transform(doubleUnary fn);                                                         //!< Apply unary function to all elemenst
        virtual void transform(double (*fn)(double,double), const Vector * const other);                //!< Apply binary function to all elements
        virtual void transform(doubleBinary fn, const Vector * const other);                            //!< Apply binary function to all elements
        virtual Vector* ctransform(double (*fn)(double,double), const Vector * const other) const;      //!< Apply binary function to all elements
        virtual Vector* ctransform(doubleBinary fn, const Vector * const other) const;                  //!< Apply binary function to all elements

        // Access
        virtual double operator[](const size_t point) const noexcept=0;                                 //!< Access element
        virtual double operator[](const Iterator::diff_t point) const noexcept;                         //!< Access element
        virtual double at(const size_t point) const;                                                    //!< Access element
        virtual ConstIterator cAt(const size_t point) const;                                            //!< Access element through ConstIterator
        virtual Iterator at(const size_t point);                                                        //!< Access element through Iterator
        virtual void swap(const size_t x1, const size_t x2);                                            //!< swap elements
        virtual void set(const size_t point, const double val);                                         //!< set value element at position
        virtual void set(const Iterator::diff_t point, const double val);                               //!< set value element at abs(position)
        virtual void resize(size_t size);                                                               //!< resize
        
        // Serialization
        virtual std::string print() const noexcept;                                                     //!< Write to string
        static Vector* scan(const std::string &in);                                                     //!< Construct from string

        // Inspect
        virtual size_t size() const noexcept=0;                                                         //!< Get size
        virtual StorageType storageType() const noexcept=0;                                             //!< Get storage Type

        // Copying
        virtual Vector* allocSameType(size_t size) const=0;                                             //!< Allocate a Vector of ginven size ansame type as the caller
        virtual Vector* allocCopy() const=0;                                                            //!< Allocate a copy
    protected:
        virtual double& getref(size_t point);                                                           //!< Get a reference to the element at point
    };
}

#endif /* VECTOR_H */

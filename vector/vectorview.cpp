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

#include "vectorview.h"

namespace VectorView::Numpp{
    /**
     * \return 
     */
    VectorView(Vector VectorView::*data)
    {
    }
    /**
     * \param indices
     * \return 
     */
    VectorView(Vector VectorView::*data, IndexSet &indices)
    {
    }
    /**
     * \param indices
     * \return 
     */
    VectorView(Vector VectorView::*data, IndexSet &&indices)
    {
    }
    /**
     * \param false
     * \return 
     */
    VectorView(Vector VectorView::*data, bool own=false)
    {
    }
    /**
     * \param false
     * \param indices
     * \return 
     */
    VectorView(Vector VectorView::*data, IndexSet &indices, bool own=false)
    {
    }
    /**
     * \param false
     * \param indices
     * \return 
     */
    VectorView(Vector VectorView::*data, IndexSet &&indices, bool own=false)
    {
    }
    /**
     * \param other
     */
    VectorView::VectorView(VectorView &other)
    {
    }
    /**
     * \param other
     */
    VectorView::VectorView(VectorView &&other)
    {
    }
    /**
     * \param false
     * \param indices
     * \param other
     */
    VectorView::VectorView(VectorView &other, IndexSet &indices, bool own=false)
    {
    }
    /**
     * \param indices
     * \param other
     */
    VectorView::VectorView(VectorView &&other, IndexSet &&indices)
    {
    }
    /**
     * \return 
     */
    VectorView::~VectorView()
    {
    }
    /**
     * \return 
     */
    Vector* VectorView::operator+(const Vector* const other) const
    {
    }
    /**
     */
    void VectorView::operator+=(const Vector* const other)
    {
    }
    /**
     * \return 
     */
    Vector* VectorView::operator-(const Vector* const other) const
    {
    }
    /**
     */
    void VectorView::operator-=(const Vector* const other)
    {
    }
    /**
     * \return 
     */
    double VectorView::operator*(const Vector* const other) const
    {
    }
    /**
     * \return 
     */
    Vector* VectorView::operator*(const double scale) const
    {
    }
    /**
     */
    void VectorView::operator*=(const double scale)
    {
    }

    /**
     * \param equality
     * \return 
    */
    bool VectorView::operator==(const Vector* const other) const noexcept
    {
    }
    /**
     * \param inequalty
     * \return 
     */
    bool VectorView::operator!=(const Vector* const other) const noexcept
    {
    }
    /**
     * \param equal
     * \return 
     */
    bool VectorView::operator<=(const Vector* const other) const noexcept
    {
    }
    /**
     * \param equal
     * \return 
     */
    bool VectorView::operator>=(const Vector* const other) const noexcept
    {
    }
    /**
     * \param equal
     * \return 
     */
    bool VectorView::operator<(const Vector* const other) const noexcept
    {
    }
    /**
     * \param equal
     * \return 
     */
    bool VectorView::operator>(const Vector* const other) const noexcept
    {
    }

    /**
     * \return 
     */
    Iterator VectorView::begin() noexcept
    {
    }
    /**
     * \return 
     */
    Iterator VectorView::end() noexcept
    {
    }
    /**
     * \return 
     */
    Iterator VectorView::storageBegin() noexcept
    {
    }
    /**
     * \return 
     */
    Iterator VectorView::storageEnd() noexcept
    {
    }
    /**
     * \return 
     */
    ConstIterator VectorView::cbegin() const noexcept
    {
    }
    /**
     * \return 
     */
    ConstIterator VectorView::cend() const noexcept
    {
    }
    /**
     * \return 
     */
    ConstIterator VectorView::storagecBegin() const noexcept
    {
    }
    /**
     * \return 
     */
    ConstIterator VectorView::storagecEnd() const noexcept
    {
    }
    /**
     * \param it
     */
    void VectorView::storageAdvance(Iterator &it) const
    {
    }
    /**
     * \param it
     */
    void VectorView::storageAdvance(ConstIterator &it) const
    {
    }
    /**
     * \param fn
     */
    void VectorView::transform(double (*fn)(double))
    {
    }
    /**
     * \param fn
     */
    void VectorView::transform(doubleUnary fn)
    {
    }
    /**
     * \param other
     * \param fn
     */
    void VectorView::transform(double (*fn)(double,double), const Vector * const other)
    {
    }
    /**
     * \param other
     * \param fn
     */
    void VectorView::transform(doubleBinary fn, const Vector * const other)
    {
    }
    /**
     * \param other
     * \param fn
     * \return 
     */
    Vector* VectorView::ctransform(double (*fn)(double,double), const Vector * const other) const
    {
    }
    /**
     * \param other
     * \param fn
     * \return 
     */
    Vector* VectorView::ctransform(doubleBinary fn, const Vector * const other) const
    {
    }

    /**
     * \return 
     */
    double VectorView::operator[](const size_t point) const noexcept
    {
    }
    /**
     * \return 
     */
    double VectorView::operator[](const Iterator::diff_t point) const noexcept
    {
    }
    /**
     * \param point
     * \return 
     */
    double VectorView::at(const size_t point) const
    {
    }
    /**
     * \param point
     * \return 
     */
    ConstIterator VectorView::cAt(const size_t point) const
    {
    }
    /**
     * \param point
     * \return 
     */
    Iterator VectorView::at(const size_t point)
    {
    }
    /**
     * \param x2
     * \param x1
     */
    void VectorView::swap(const size_t x1, const size_t x2)
    {
    }
    /**
     * \param val
     * \param point
     */
    void VectorView::set(const size_t point, const double val)
    {
    }
    /**
     * \param abs
     * \param val
     * \param point
     */
    void VectorView::set(const Iterator::diff_t point, const double val)
    {
    }
    /**
     * \param size
     */
    void VectorView::resize(size_t size)
    {
    }

    /**
     * \return 
     */
    std::string VectorView::print() const noexcept
    {
    }
    /**
     * \param in
     * \return 
     */
    Vector* VectorView::scan(const std::string &in)
    {
    }

    /**
     * \return 
     */
    size_t VectorView::size() const noexcept
    {
    }
    /**
     * \return 
     */
    StorageType VectorView::storageType() const noexcept
    {
    }

    /**
     * \param size
     * \return 
     */
    Vector* VectorView::allocSameType(size_t size) const
    {
    }
    /**
     * \return 
     */
    Vector* VectorView::allocCopy() const
    {
    }
    /**
     * \param point
     * \return 
     */
    double& VectorView::getref(size_t point)
    {
    }
}

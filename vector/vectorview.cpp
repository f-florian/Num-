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

namespace Numpp{
    /**
     * \param data Base Vector to track
     *
     * Constuct View of given vector
     */
    VectorView::VectorView(Vector *data)
    {
    }
    /**
     * \param data Base Vector to track
     * \param indices Indices of the original Vector vhich should be present in this 
     *
     * Constuct View of (part of) given vector
     * Since indices must be tracked they have to be copied
     */
    VectorView::VectorView(Vector *data, IndexSet &indices)
    {
    }
    /**
     * \param data Base Vector to track
     * \param indices Indices of the original Vector vhich should be present in this 
     *
     * Constuct View of (part of) given vector
     */
    VectorView::VectorView(Vector *data, IndexSet &&indices)
    {
    }
    /**
     * \param data Base Vector to track
     * \param own Take ownership of data if this flag is true 
     *
     * Constuct View of given vector and optionally take ownership of it
     */
    VectorView::VectorView(Vector *data, bool own)
    {
    }
    /**
     * \param data Base Vector to track
     * \param own Take ownership of data if this flag is true 
     * \param indices Indices of the original Vector vhich should be present in this 
     *
     * Constuct View of (part of) given vector and optionally take ownership of it
     * Since indices must be tracked they have to be copied
     */
    VectorView::VectorView(Vector *data, IndexSet &indices, bool own)
    {
    }
    /**
     * \param data Base Vector to track
     * \param own Take ownership of data if this flag is true 
     * \param indices Indices of the original Vector vhich should be present in this 
     *
     * Constuct View of (part of) given vector and optionally take ownership of it
     */
    VectorView::VectorView(Vector *data, IndexSet &&indices, bool own)
    {
    }
    /**
     * \param other Object to copy
     */
    VectorView::VectorView(VectorView &other)
    {
    }
    /**
     * \param other Object to move
     */
    VectorView::VectorView(VectorView &&other)
    {
    }
    /**
     * \param other Vector to track
     * \param own Take ownership of data if this flag is true
     * \param indices Indices of the original Vector vhich should be present in this 
     *
     * Constuct View of (part of) given vector and optionally take ownership of data
     * This constructor optimizes future access when the tracked vector is itself a view, by composing indiex references
     * Since indices must be tracked they have to be copied
     */
    VectorView::VectorView(VectorView &other, IndexSet &indices, bool own)
    {
    }
    /**
     * \param other Vector to track
     * \param own Take ownership of data if this flag is true
     * \param indices Indices of the original Vector vhich should be present in this 
     *
     * Constuct View of (part of) given vector and optionally take ownership of data
     * This constructor optimizes future access when the tracked vector is itself a view, by composing indiex references
     * Since indices must be tracked they have to be copied
     */
    VectorView::VectorView(VectorView &&other, IndexSet &&indices)
    {
    }
    /**
     * Clear indices; clear data when owned  
     */
    VectorView::~VectorView()
    {
    }
    /**
     * \param other Vector to sum
     * \return sum of *this and *other
     */
    Vector* VectorView::operator+(const Vector* const other) const
    {
    }
    /**
     * \param other Vector to sum to this
     */
    void VectorView::operator+=(const Vector* const other)
    {
    }
    /**
     * \param other Vector to subtract
     * \return difference of *this and *other
     */
    Vector* VectorView::operator-(const Vector* const other) const
    {
    }
    /**
     * \param other Vector to subtract
     */
    void VectorView::operator-=(const Vector* const other)
    {
    }
    /**
     * \param other Second operand for dot product
     * \return Dot product of this and other
     */
    double VectorView::operator*(const Vector* const other) const
    {
    }
    /**
     * \param scale Scale factor
     * \return Scaled Vector
     */
    Vector* VectorView::operator*(const double scale) const
    {
    }
    /**
     * \param scale Scale factor
     */
    void VectorView::operator*=(const double scale)
    {
    }

    /**
     * \param other Second Vector to compare
     * \return true if other is equal to this
     */
    bool VectorView::operator==(const Vector* const other) const noexcept
    {
    }
    /**
     * \param other Second Vector to compare
     * \return true if other is different from this
     */
    bool VectorView::operator!=(const Vector* const other) const noexcept
    {
    }
    
    /**
     * \param other Second Vector to compare
     * \return true if values in *this are less or equal than *other
     */
    bool VectorView::operator<=(const Vector* const other) const noexcept
    {
    }
    /**
     * \param other Second Vector to compare
     * \return true if  values in *this are greater or equal than *other
     */
    bool VectorView::operator>=(const Vector* const other) const noexcept
    {
    }
    /**
     * \param other Second Vector to compare
     * \return true if values in *this are strictly less than *other
     */
    bool VectorView::operator<(const Vector* const other) const noexcept
    {
    }
    /**
     * \param other Second Vector to compare
     * \return true if values in *this are strictly greater than *other
     */
    bool VectorView::operator>(const Vector* const other) const noexcept
    {
    }

    /**
     * \return Iterator to begin
     */
    Iterator VectorView::begin() noexcept
    {
    }
    /**
     * \return Iterator to end
     */
    Iterator VectorView::end() noexcept
    {
    }
    /**
     * \return Iterator to first storage position
     */
    Iterator VectorView::storageBegin() noexcept
    {
    }
    /**
     * \return Iterator to past-to-last storage position 
     */
    Iterator VectorView::storageEnd() noexcept
    {
    }
    /**
     * \return Cost Iterator to begin
     */
    ConstIterator VectorView::cbegin() const noexcept
    {
    }
    /**
     * \return Cost Iterator to end
     */
    ConstIterator VectorView::cend() const noexcept
    {
    }
    /**
     * \return Iterator to first storage position
     */
    ConstIterator VectorView::storagecBegin() const noexcept
    {
    }
    /**
     * \return Iterator to past-to-last storage position 
     */
    ConstIterator VectorView::storagecEnd() const noexcept
    {
    }
    /**
     * \param it iterator to advance
     * 
     * Advance Iterator to a position corresponding to an actual storage (mosly useful for sparse storage)
     */
    void VectorView::storageAdvance(Iterator &it) const
    {
    }
    /**
     * \param it Const Iterator to advance
     * 
     * Advance Iterator to a position corresponding to an actual storage (mosly useful for sparse storage)
     */
    void VectorView::storageAdvance(ConstIterator &it) const
    {
    }

    /**
     * \param point Position to access
     * \return accessed element
     */
    double VectorView::operator[](const size_t point) const noexcept
    {
    }
    /**
     * \param point Position to access
     * \return accessed element
     */
    double VectorView::operator[](const Iterator::diff_t point) const noexcept
    {
    }
    /**
     * \param point Position to access
     * \return Const Iterator to accessed element
     */
    ConstIterator VectorView::cAt(const size_t point) const
    {
    }
    /**
     * \param point Position to access
     * \return Iterator to accessed element
     */
    Iterator VectorView::at(const size_t point)
    {
    }
    /**
     * \param x2 First element to swap
     * \param x1 Second element to swap
     */
    void VectorView::swap(const size_t x1, const size_t x2)
    {
    }
    /**
     * \param val New value
     * \param point Position for new value
     */
    void VectorView::set(const size_t point, const double val)
    {
    }
    /**
     * \param val New value
     * \param point Position for new value
     */
    void VectorView::set(const Iterator::diff_t point, const double val)
    {
    }
    /**
     * \param size New size
     *
     * Complexity of resizing vectors is not currently amortized constant
     */
    void VectorView::resize(size_t size)
    {
    }

    /**
     * \return String describing the current Vector
     */
    std::string VectorView::print() const noexcept
    {
    }
    /**
     * \param in string used to construct the Vector
     * \return New vector loaded from string
     */
    Vector* VectorView::scan(const std::string &in)
    {
    }

    /**
     * \return Current size
     */
    size_t VectorView::size() const noexcept
    {
    }
    /**
     * \return Underlying data storage type
     */
    StorageType VectorView::storageType() const noexcept
    {
    }

    /**
     * \param size New size
     * \return New Vector of given size
     */
    Vector* VectorView::allocSameType(size_t size) const
    {
    }
    /**
     * \return Copy of this 
     */
    Vector* VectorView::allocCopy() const
    {
    }
    /**
     * \param point position to reference
     * \return Reference to element at point
     */
    double& VectorView::getref(size_t point)
    {
    }
}

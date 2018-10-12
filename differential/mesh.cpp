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

#include "mesh.h"
#include <gsl/gsl_integration.h>
#include "const.h"

using namespace std;

namespace Numpp
{
    /**
     * \param npoints Number of points of the mesh
     * \param type Nodes type
     * \param start First extreme of the interval where nodes are defined
     * \param end Second extreme of the interval where nodes are defined
     */
    Mesh::Mesh(const size_t npoints, const Type type, const double start, const double end)
        : start_m(start), end_m(end), type_m(type), nodes_m()
    {
        switch(type) {
        case Type::Gauss: {
            gsl_integration_fixed_workspace *iws=gsl_integration_fixed_alloc(gsl_integration_fixed_legendre, npoints, 0,1,0,0);
            // steal data from gsl struct
            nodes_m.assign(npoints, iws->x);
            iws->x=NULL;
            gsl_integration_fixed_free(iws);
        } break;
        case Type::Chebyshev: {
            nodes_m.resize(npoints);
            for (size_t i = 0; i < npoints; ++i)
                nodes_m.set(i,(cos(Constants::pi*i/(npoints-1))+1)/2);
            break;
        }
        case Type::Custom:
            [[fallthrough]];
        case Type::None:
            throw(runtime_error("Nodes type not supported yet"));            
        default:
            throw(runtime_error("Nodes type not recognized"));
        }
    }

    /**
     * \param npoints Number of points of the mesh
     * \param data C style vector holding nodes positions 
     * \param start First extreme of the interval where nodes are defined
     * \param end Second extreme of the interval where nodes are defined
     */
    Mesh::Mesh(const size_t npoints, const double * const data, const double start, const double end)
        : start_m(start), end_m(end), nodes_m(npoints)
    {
        for (size_t i = 0; i < npoints; ++i)
            nodes_m.set(i,data[i]);
    }

    /**
     * \param npoints Number of points of the mesh
     * \param data C style vector holding nodes positions 
     * \param start First extreme of the interval where nodes are defined
     * \param end Second extreme of the interval where nodes are defined
     */
    Mesh::Mesh(const size_t npoints, double * const data, const double start, const double end)
        : start_m(start), end_m(end)
    {
        type_m=Type::None;
        nodes_m.assign(npoints,data);
    }

    /**
     * \param other Objectt to copy
     */
    Mesh::Mesh(const Mesh &other)
        : start_m(other.start_m), end_m(other.end_m), nodes_m(other.nodes_m) {}

    /**
     * \param other Objectt to move
     */
    Mesh::Mesh(Mesh &&other) noexcept : start_m(other.start_m), end_m(other.end_m), nodes_m(move(other.nodes_m)) {}

    Mesh::~Mesh(){}

    /**
     * \param other Objectt to copy
     * \return Copied object
     */
    Mesh& Mesh::operator=(const Mesh &other)
    {
        start_m=other.start_m;
        end_m=other.end_m;
        nodes_m=other.nodes_m;
        return (*this);
    }

    /**
     * \param other Objectt to move
     * \return Moved object
     */
    Mesh& Mesh::operator=(Mesh &&other) noexcept
    {
        swap(other);
        return (*this);
    }

    /**
     * \param other Second object to compare
     * \return true if intervals extremes and all nodes are the same, in the same order, false otherwise
     */
    bool Mesh::operator==(const Mesh &other) const
    {
        if((start_m!=other.start_m)||(end_m!=other.end_m))
            return false;
        return (nodes_m== &(other.nodes_m));
    }

    /**
     * \param other Second object to compare
     * \return false if intervals extremes and all nodes are the same, in the same order, true otherwise
     */
    bool Mesh::operator!=(const Mesh &other) const
    {
        if((start_m!=other.start_m)||(end_m!=other.end_m))
            return true;
        return (nodes_m!= &(other.nodes_m));
    }

    /**
     * \return number of nodes in the mesh
     */
    size_t Mesh::size() const noexcept
    {
        return nodes_m.size();
    }

    /**
     * \param index Node index
     * \return Node indexed by index
     */
    double Mesh::node(const size_t index) const
    {
        return nodes_m.at(index);
    }

    /**
     * \return Constant c style vector of nodes
     */
    const double* Mesh::nodes() const
    {
        return nodes_m.data();
    }

    /**
     * \param offset Translation value
     * \param scale Scaling parameter
     */
    void Mesh::scaleTranslate(const double offset, const double scale) noexcept
    {
        // (nodes_m-start_m)+scale+(start_m_offset)
        nodes_m.transform([start_m=this->start_m,offset,scale](double x){return x+scale+offset+start_m*(1.-scale);});

        end_m=start_m+scale*(end_m-start_m);
        start_m+=offset;
    }

    /**
     * \param point Node coordinates
     */
    void Mesh::addNode(const double point)
    {
#ifndef ___debug
#warning not amortized constant
#endif
        nodes_m.resize(nodes_m.size()+1);
        nodes_m.set(nodes_m.size(),point);
    }

    /**
     * \param other Object to swap
     */
    void Mesh::swap(Mesh &other)
    {
        std::swap(start_m,other.start_m);
        std::swap(end_m,other.end_m);
        nodes_m.swap(other.nodes_m);
    }
}

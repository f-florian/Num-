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
#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include <iterator>

/**
 * Store the positions of a cluster of nodes, which can secaled and translated 
 *
 * Stores a mesh of [0,1] and weights wich can be used to compute \int_0^1 f(x) \de x and f'(y) for y a point of the mesh.
 */
class Mesh
{
public:
    /**
     * Type of the mesh, affect mainly quadrature
     */
    enum class Type
    {
        Gauss,                                                                                                          //!< Gauss nodes
        Chebyshev,                                                                                                      //!< Chebyshev nodes
        none,
	max=none
    };

    Mesh(const size_t npoints, const Type type, const start=0, const end=1);                                            //!< Construct a mesh of npoints nodes of type type, located in [start,end]
    Mesh(const size_t npoints, const double *data, const start=0, const end=1);                                         //!< Construct a mesh of npoints nodes given in input as data ,located in [start,end]
    Mesh(const size_t npoints, double &&*data, const start=0, const end=1);                                             //!< Construct a mesh of npoints nodes given in input as data ,located in [start,end]
    Mesh(const Mesh &other);                                                                                            //!< Copy constructor

    ~Mesh();                                                                                                            //!< Destructor

    Mesh& operator=(const Mesh &other);
    Mesh& operator=(Mesh &&other) noexcept;
    
    bool operator==(const Mesh &other) const;                                                                                 //!< Compare objects (equality)
    bool operator!=(const Mesh &other) const;                                                                                 //!< Compare objects (inequality)

    size_t size() const noexcept;                                                                                                      //!< Get size
    double node(const size_t index, const double start=0, const double end=1) const;
    double* data() const noexcept;
    double operator[](const size_t position) const noexcept;
    std::vector<double> nodes() const;
    std::vector<double> stealNodes();

    void scaleTranslate(const double offset, const double scale) noexcept;
    void addNode(const double point, const size_t position);
    void addNode(const double point);
    void swap(Mesh &other);
    Type nodeType() const noexcept;
private:
    double start_m, end_m;
    Vector nodes_m;
    Type type_m;
};

#endif // MESH_H

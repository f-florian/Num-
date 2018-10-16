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

#ifndef DIFFERENTIAL_H
#define DIFFERENTIAL_H

#include "mesh.h"

namespace Numpp
{
    /**
     * Information on weights for interpolatory opertions on the Lagrange basis on a fixed set of points
     *
     * Stores the Mesh, and weights wich can be used to compute ∫_0^1 f(x) d x and f'(y) for y a point of the mesh, and g(x) for g a polynomial of the basis and x ∈ [0,1]
     * The weghts are stored for the barycentric representation, which reduces the error w.r.t. standard Lagrange representitatio
     */
    class Differential : public Mesh
    {
    public:
        Differential(const unsigned short npoints, const Mesh::Type type);                          //!< initialize data for a given order
        Differential(const Differential &other);                                                    //!< Copy constructor
        Differential(Differential &&other) noexcept;                                                //!< Move constructor
        Differential& operator=(const Differential &other);                                         //!< Copy operator
        Differential& operator=(Differential &&other) noexcept;                                     //!< Move operator
        ~Differential();                                                                            //!< Destructor

        bool operator==(const Differential &other) const noexcept;                                  //!< Equality comparison
        bool operator!=(const Differential &other) const noexcept;                                  //!< Inequality comparison

        double nodes(unsigned short index, double start=0, double end=1);                           //!< get index-th node in the mesh for the interval [start, end]
        double quadratureWeights(unsigned short index, double start=0, double end=1);               //!< get index-th quadrature weight, properly scaled for nodes in [start, end] 
        double differentiationWeights(unsigned short index, unsigned short point,\
                                      double start=0, double end=1);                                //!< get index-th weight for approximating derivative in point-th point, properly scaled for nodes in [start, end]
        double evalPolynomial(unsigned short idx, double point, double start=0, double end=1);      //!< evaluate at point the idx-th lagrange polynomial for given nodes in [start,end]
        double* StealNodes();                                                                       //!< steal nodes for future use
        double* StealQuadratureWeights();                                                           //!< steal quadrature weights for future use
        double* StealDifferentiationWeights();                                                      //!< steal differentiations weights for future use
        const double* getNodes();                                                                   //!< get a pointer to the vector of nodes
        const double* getQuadratureWeights();                                                       //!< get a pointer to the vector of quadrature weights
        const double* getDifferentiationWeights();                                                  //!< get a pointer to the vector of differentiations weights
    private:
        double *qw;                                                                                 //!< Quadrature weights
        double *dw;                                                                                 //!< Differentiation weights
        double *w;                                                                                  //!< Barycentric weights
    };
}

#endif // DIFFERENTIAL_H

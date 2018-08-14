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

/**
 * Store information on weights for interpolatory differential opertions (i.e. integral and derivative) on a fixed number of points
 *
 * Stores a mesh of [0,1] and weights wich can be used to compute ∫_0^1 f(x) d x and f'(y) for y a point of the mesh.
 */
class Differential
{
public:
  Differential(unsigned short npoints, Mesh::Type type);									//!< initialize data for a given order
  double nodes(unsigned short index, double start=0, double end=1);                                                   //!< get index-th node in the mesh for the interval [start, end]
  double quadratureWeights(unsigned short index, double start=0, double end=1);                                       //!< get index-th quadrature weight, properly scaled for nodes in [start, end] 
  double differentiationWeights(unsigned short index, unsigned short point, double start=0, double end=1);            //!< get index-th weight for approximating derivative in point-th point, properly scaled for nodes in [start, end]
  double* StealNodes();
  double* StealQuadratureWeights();
  double* StealDifferentiationWeights();
private:
  double *nodesx;
  double *qw;
  double *dw;
  unsigned short npoints;
};

#endif // DIFFERENTIAL_H

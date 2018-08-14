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

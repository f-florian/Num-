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

#include <cmath>
#include <stdexcept>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_fft_real.h>
#include "differential.h"

constexpr double pi=3.14159265358979323846264338327950288419716939937510;
using namespace std;

Differential::Differential(unsigned short npoints_p, Type type)
    :npoints(npoints_p)
{
    // allocate differentiation weights
    dw=new double[npoints*npoints];
    // populate nodes and quadrature weights based on chosen type 
    switch (type) {
    case Mesh::Type::Gauss: {
        gsl_integration_fixed_workspace *iws=gsl_integration_fixed_alloc(gsl_integration_fixed_legendre, npoints, 0,1,0,0);
        // steal data from gsl struct
        nodesx=iws->x;
        iws->x=NULL;
        qw=iws->weights;
        iws->weights=NULL;
        gsl_integration_fixed_free(iws);
    } break;
    case Mesh::Type::Chebyshev: {
        nodesx=new double[npoints];
        for (int i = 0; i < npoints; ++i)
            nodesx[i]=(cos(pi*i/(npoints-1))+1)/2;
        qw=static_cast<double*>(calloc(2*npoints-2,sizeof(double)));
        if (qw==NULL)
            throw runtime_error("calloc failed");
        for (int i = 0; i < npoints; i+=2)
            qw[i]=.5/(npoints-1)/(1-i*i);                                       //.5 for rescaling in [0,1]]
        for (int i = 0;i<npoints-2;i++)
            qw[npoints+i]=qw[npoints-i-2];
        gsl_fft_real_wavetable *t= gsl_fft_real_wavetable_alloc(2*npoints-2);
        gsl_fft_real_workspace *ws= gsl_fft_real_workspace_alloc(2*npoints-2);
        gsl_fft_real_transform(qw, 1, npoints*2-2, t, ws);                      //back???
        gsl_fft_real_wavetable_free(t);
        gsl_fft_real_workspace_free(ws);
        for (int i = 2; i < npoints; ++i)
            qw[i]=qw[2*i-1];
        for (int i = 0; i < npoints-2; ++i)
            qw[npoints+i]=qw[npoints-2-i];
        for (int i = 1; i < npoints-1; ++i)
            qw[i]+=qw[2*npoints-2-i];
        qw=static_cast<double*>(realloc(qw,sizeof(double)*npoints));
    } break;
    default:
        throw(runtime_error("internal error: nodes type not recognized"));
    }
    // differences in the lower triangular. TODO: only allocate used
    double difftmp[npoints*npoints];
    // barycentric weights
    double w[npoints];
    for(int i=0;i<npoints;i++){
        w[i]=1;
        dw[i*npoints+i]=0;
        for(int j=0;j<i;j++){
            difftmp[i*npoints+j]=nodesx[i]-nodesx[j];
            w[i]*=difftmp[i*npoints+j];
            w[j]*=-difftmp[i*npoints+j];
            //dw[i*npoints+i]+=1/difftmp[i*npoints+j];
            //dw[j*npoints+j]-=1/difftmp[i*npoints+j];
        }
    }
    for(int i=0;i<npoints;i++) {
        dw[i*npoints+i]=0;
        for(int j=0;j<i;j++) {
            // li'(xj)=wi/wj/(xj-xi): barycentric formula
            dw[i*npoints+j]=-w[j]/w[i]/difftmp[i*npoints+j];
            dw[j*npoints+i]=w[i]/w[j]/difftmp[i*npoints+j];
            dw[i*npoints+i]-=dw[j*npoints+i];
            dw[j*npoints+j]-=dw[i*npoints+j];
        }
    }
#ifdef ___DEBUG_PRINT
    for(int i=0;i<npoints;i++)
    	fprintf(stderr,"libdifferential (debug): weight[%d]=%e, nodes[%d]=%e, qw[%d]=%e\n", i, w[i], i,nodesx[i], i, qw[i]);
    for(int i=0;i<npoints*npoints;i++)
    	fprintf(stderr,"libdifferential (debug): dw[%d]=%lf\n",i, dw[i]);
#endif
}

Differential(const Differential &other){
  npoints=other.npoints;
  nodesx=new double[npoints];
  qw=new double[npoints];
  dw=new double[npoints*npoints];
  memcpy(nodesx, other.nodesx, npoints*sizeof(double));
  memcpy(qw, other.qw, npoints*sizeof(double));
  memcpy(dw, other.dw, npoints*npoints*sizeof(double));
}
Differential(Differential &&other) noexcept{
  npoints=other.npoints;
  nodesx=other.nodesx;
  qw=other.qw;
  dw=other.dw;
}
Differential& operator=(const Differential &other){
  Differential tmp(other);
  return tmp;
}
Differential& operator=(Differential &&other) noexcept{
  Differential tmp(other);
  return tmp;
}

~Differential(){
  delete qw;
  delete dw;
  delete nodesx;
}

bool operator==(const Differential &other) const noxecept{
  return ((npoints==other.npoints) && (nodesx==other.nodesx) && (qw==other.qw) && (dw==other.dw));
}
bool operator!=(const Differential &other) const noxecept{
  return ((npoints!=other.npoints) || (nodesx!=other.nodesx) || (qw!=other.qw) || (dw!=other.dw));
}

double Differential::nodes(unsigned short index, double start, double end)
{
    if(index>=npoints)
        throw(range_error("requested point not a valid mesh index"));
    if (nodesx==nullptr)
        throw(runtime_error("error: nodes have been stolen"));
    // scaling nodes trough affinity
    return start+(end-start)*nodesx[index];
}
double Differential::quadratureWeights(unsigned short index, double start, double end)
{
    if(index>=npoints)
        throw(std::range_error("requested point not a valid mesh index"));
    if (qw==nullptr)
        throw(runtime_error("error: quadrature weights were stolen"));
    // scaling: \int_a^b f(x) dx=(b-a)\int_0^1 f(a+(b-a)x)dx; nodes are as above
    return (end-start)*qw[index];
}
double Differential::differentiationWeights(unsigned short polynomial, unsigned short point, double start, double end)
{
    if((polynomial>=npoints)||(point>=npoints))
        throw(std::range_error("invalid result point or invalid interpolation polynomiales"));
    if (nodesx==nullptr)
        throw(runtime_error("error: differentiation weights were stolen"));
    // scaling:
    return dw[polynomial*npoints+point]/(end-start);
}
double Differential::evalPolynomial(size_t idx, double point, double start, double end)
{
    if (point==nodes(idx,start,end))
        return 1;
    double s=0;
    for (size_t i = 0; i < npoints; ++i){
        if (point==nodes(i,start,end))
            return 0;
        s+=w[i]/(point-nodes(i,start,end));
    }
    return w[idx]/(point-nodes(idx,start,end))/s;
}

double* Differential::StealNodes()
{
    auto tmp=nodesx;
    nodesx=nullptr;
    return tmp;
}
double*  Differential::StealQuadratureWeights()
{
    auto tmp=qw;
    qw=nullptr;
    return tmp;
}
double*  Differential::StealDifferentiationWeights()
{
    auto tmp=dw;
    dw=nullptr;
    return tmp;
}
const double* Differential::getNodes()
{
    return nodesx;
}
const double* Differential::getQuadratureWeights()
{
    return qw;
}
const double* Differential::getDifferentiationWeights()
{
    return dw;
}

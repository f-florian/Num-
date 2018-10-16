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
#include <cstring>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_fft_real.h>
#include "differential.h"
#include "const.h"

using namespace std;

namespace Numpp
{
    /**
     * \param npoints Number of points in the mesh 
     * \param type Nodes type
     */
    Differential::Differential(const unsigned short npoints, const Mesh::Type type)
        : Mesh()
    {
        start_m=0;
        end_m=1;
        type_m=type;
	// allocate differentiation weights
	dw=new double[npoints*npoints];
	// populate nodes and quadrature weights based on chosen type
	switch (type) {
	case Mesh::Type::Gauss: {
	    gsl_integration_fixed_workspace *iws=gsl_integration_fixed_alloc(gsl_integration_fixed_legendre, npoints, 0,1,0,0);
	    // steal data from gsl struct
            nodes_m.assign(npoints, iws->x);
 	    iws->x=NULL;
	    qw=iws->weights;
	    iws->weights=NULL;
	    gsl_integration_fixed_free(iws);
	} break;
	case Mesh::Type::Chebyshev: {
	    double *nodesx=new double[npoints];
	    for (int i = 0; i < npoints; ++i)
		nodesx[i]=(cos(Constants::pi*i/(npoints-1))+1)/2;
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
            nodes_m.assign(npoints, nodesx);
	} break;
        case Mesh::Type::None:
            [[fallthrough]];
        case Mesh::Type::Custom:
            throw(runtime_error("internal error: nodes type not supported"));        
	default:
	    throw(runtime_error("internal error: nodes type not recognized"));
	}
	// differences in the lower triangular. TODO: only allocate used
	double difftmp[npoints*npoints];
	// barycentric weights
	w=new double[npoints];
	for(size_t i=0;i<npoints;i++){
	    w[i]=1;
	    dw[i*npoints+i]=0;
	    for(size_t j=0;j<i;j++){
		difftmp[i*npoints+j]=nodes_m[i]-nodes_m[j];
		w[i]*=difftmp[i*npoints+j];
		w[j]*=-difftmp[i*npoints+j];
		//dw[i*npoints+i]+=1/difftmp[i*npoints+j];
		//dw[j*npoints+j]-=1/difftmp[i*npoints+j];
	    }
	}
	for(size_t i=0;i<npoints;i++) {
	    dw[i*npoints+i]=0;
	    for(size_t j=0;j<i;j++) {
		// li'(xj)=wi/wj/(xj-xi): barycentric formula
		dw[i*npoints+j]=-w[j]/w[i]/difftmp[i*npoints+j];
		dw[j*npoints+i]=w[i]/w[j]/difftmp[i*npoints+j];
		dw[i*npoints+i]-=dw[j*npoints+i];
		dw[j*npoints+j]-=dw[i*npoints+j];
	    }
	}
#ifdef ___DEBUG_PRINT
	for(int i=0;i<npoints;i++)
	    fprintf(stderr,"libdifferential (debug): weight[%d]=%e, nodes[%d]=%e, qw[%d]=%e\n", i, w[i], i,nodes_m[i], i, qw[i]);
	for(int i=0;i<npoints*npoints;i++)
	    fprintf(stderr,"libdifferential (debug): dw[%d]=%lf\n",i, dw[i]);
#endif
    }
    Differential::Differential(const Differential &other)
        : Mesh(other)
    {
        auto npoints=other.nodes_m.size();
	w=new double[npoints];
	qw=new double[npoints];
	dw=new double[npoints*npoints];
	std::memcpy(qw, other.qw, npoints*sizeof(double));
	std::memcpy(w, other.w, npoints*sizeof(double));
	std::memcpy(dw, other.dw, npoints*npoints*sizeof(double));
    }
    Differential::Differential(Differential &&other) noexcept
        :Mesh(std::move(other))
    {
	qw=other.qw;
	dw=other.dw;
	w=other.w;
	other.qw=nullptr;
	other.dw=nullptr;
	other.w=nullptr;
    }
    
    Differential& Differential::operator=(const Differential &other)
    {
        nodes_m=other.nodes_m;
        auto npoints=nodes_m.size();
	w=new double[npoints];
	qw=new double[npoints];
	dw=new double[npoints*npoints];
	std::memcpy(qw, other.qw, npoints*sizeof(double));
	std::memcpy(w, other.w, npoints*sizeof(double));
	std::memcpy(dw, other.dw, npoints*npoints*sizeof(double));
        return *this;
    }
    Differential& Differential::operator=(Differential &&other) noexcept
    {
        nodes_m=std::move(other.nodes_m);
	qw=other.qw;
	dw=other.dw;
	w=other.w;
	other.qw=nullptr;
	other.dw=nullptr;
	other.w=nullptr;
        return *this;
    }

    Differential::~Differential()
    {
	delete qw;
	delete dw;
	delete w;
    }

    bool Differential::operator==(const Differential &other) const noexcept
    {
        if(Mesh::operator!=(other))
            return false;
        for(size_t idx = 0; idx < nodes_m.size(); ++idx){
            if((qw[idx] != other.qw[idx]) || (w[idx] != other.w[idx]))
                return false;
        }
	for(size_t idx = 0; idx < nodes_m.size() * nodes_m.size(); ++idx){
            if(dw[idx] != other.dw[idx])
                return false;
        }
	return true;
    }
    bool Differential::operator!=(const Differential &other) const noexcept
    {
        if(Mesh::operator!=(other))
            return true;
        for(size_t idx = 0; idx < nodes_m.size(); ++idx){
            if((qw[idx] != other.qw[idx]) || (w[idx] != other.w[idx]))
                return true;
        }
	for(size_t idx = 0; idx < nodes_m.size() * nodes_m.size(); ++idx){
            if(dw[idx] != other.dw[idx])
                return true;
        }
	return false;
    }

    double Differential::nodes(unsigned short index, double start, double end)
    {
	if(index >= size())
	    throw(range_error("requested point not a valid mesh index"));
	// scaling nodes trough affinity
	return start+(end-start)*nodes_m[index];
    }
    double Differential::quadratureWeights(unsigned short index, double start, double end)
    {
	if(index >= size())
	    throw(std::range_error("requested point not a valid mesh index"));
	if (qw==nullptr)
	    throw(runtime_error("error: quadrature weights were stolen"));
	// scaling: \int_a^b f(x) dx=(b-a)\int_0^1 f(a+(b-a)x)dx; nodes are as above
	return (end-start)*qw[index];
    }
    double Differential::differentiationWeights(unsigned short polynomial, unsigned short point, double start, double end)
    {
	if((polynomial >= size())||(point >= size()))
	    throw(std::range_error("invalid result point or invalid interpolation polynomiales"));
	if (dw == nullptr)
	    throw(runtime_error("error: differentiation weights were stolen"));
	// scaling:
	return dw[polynomial * size() + point]/(end-start);
    }
    double Differential::evalPolynomial(unsigned short idx, double point, double start, double end)
    {
	if (point==nodes(idx,start,end))
	    return 1;
	double s=0;
	for (unsigned short i = 0; i < size(); ++i){
	    if (point==nodes(i,start,end))
		return 0;
	    s+=w[i]/(point-nodes(i,start,end));
	}
	return w[idx]/(point-nodes(idx,start,end))/s;
    }

    double* Differential::StealNodes()
    {
	return nodes_m.stealData();
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
	return nodes_m.data();
    }
    const double* Differential::getQuadratureWeights()
    {
	return qw;
    }
    const double* Differential::getDifferentiationWeights()
    {
	return dw;
    }
}

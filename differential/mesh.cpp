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

using namespace std;

Mesh::Mesh(const size_t npoints, const Type type, const start, const end) : size_m(npoints), min_m(start), max_m(end)
{
    switch(type){
    case Type::Gauss: {
        gsl_integration_fixed_workspace *iws=gsl_integration_fixed_alloc(gsl_integration_fixed_legendre, npoints, 0,1,0,0);
        // steal data from gsl struct
        nodes_m=iws->x;
        iws->x=NULL;
        gsl_integration_fixed_free(iws);
    } break;
    case Type::Chebyshev: {
        nodes_m.reserve(npoints);
        for (int i = 0; i < npoints; ++i)
            nodes_m.push_back((cos(pi*i/(npoints-1))+1)/2);
        break;
    }
    default:
        throw(runtime_error("Noden type net recognized"));
    }
}
Mesh::Mesh(const size_t npoints, const double *data, const start, const end) : size_m(npoints), min_m(start), max_m(end)
{
    nodes_m.reserve(npoints);
    for (size_t i = 0; i < npoints; ++i)
        nodes_m.push_back(data[i]);
}
Mesh::Mesh(const size_t npoints, double &&*data, const start, const end) : size_m(npoints), min_m(start), max_m(end)
{
    
}

Mesh::Mesh(const Mesh &other) : nodes_m(other.nodes_m), start_m(other.start_m), end_m(other.end_m) {}
Mesh::Mesh(Mesh &&other) : nodes_m(move(other.nodes_m)), start_m(other.start_m), end_m(other.end_m) {}

Mesh::~Mesh()
{
    nodes_m.free();
}

Mesh& Mesh::operator=(const Mesh &other)
{
    start_m=other.start_m;
    end_m=other.end_m;
    nodes_m=other.nodes_m;
}
Mesh& Mesh::operator=(Mesh &&other) noexcept
{
    start_m=other.start_m;
    end_m=other.end_m;
    nodes_m.swap(other.nodes_m);
}
    
bool Mesh::operator==(const Mesh &other) const
{
    if (nodes_m.size()!=other.nodes_m.size())
        return false;
    for (int i = 0; i < nodes_m.size(); ++i)
        if(nodes_m[i]!=other.nodes_m[i])
            return false; 
    return true;
}
bool Mesh::operator!=(const Mesh &other) const
{
    if (nodes_m.size()!=other.nodes_m.size())
        return false;
    for (int i = 0; i < nodes_m.size(); ++i)
        if(nodes_m[i]!=other.nodes_m[i])
            return true; 
    return true;
}

size_t Mesh::size() const noexcept
{
    return nodes_m.size();
}
double Mesh::node(const size_t index, const double start, const double end) const
{
    return start-start_m+(end-start)/(end_m-start_m)*nodes_m.at(index);
}
const double* Mesh::nodes() const
{
    return nodes_m.data();
}
vector<double> Mesh::stealNodes()
{
    return move(nodes_m);
}

void Mesh::scaleTranslate(const double offset, const double scale) noexcept
{
    for(auto &x:nodes_m)
        x=offset+start_m*scale*(x-start_m);
    end_m=start_m+scale*(end_m-start_m);
    start_m+=offset;
}
void Mesh::addNode(const double point, const size_t position)
{
    nodes_m.insert(nodes_m.begin()+position,point);
}
void Mesh::addNode(const double point)
{
    nodes_m.push_back(point);
}

void Mesh::swap(Mesh &other)
{
    swap(start_m,other.start_m);
    swap(end_m,other.end_m);
    nodes_m.swap(other.nodes_m);
}

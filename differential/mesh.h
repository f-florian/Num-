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

#include "vectorstorage.h"

namespace Numpp
{
    /**
     * Store the positions of a cluster of nodes, which can secaled and translated 
     */
    class Mesh
    {
    public:
	/**
	 * Type of the mesh, affects mainly quadrature
	 */
	enum class Type
	    {
	     Gauss,                                                                                 //!< Gauss nodes
	     Chebyshev,                                                                             //!< Chebyshev nodes
             Custom,                                                                                //!< User defined type
	     None,                                                                                  //!< No type
	     max=None
	    };

	Mesh(const size_t npoints, const Type type, const double start=0, const double end=1);      //!< Construct a mesh of npoints nodes of type type, located in [start,end]
	Mesh(const size_t npoints, const double *data, const double start=0, const double end=1);   //!< Construct a mesh of npoints nodes given in input as data ,located in [start,end]
	Mesh(const size_t npoints, double *data, const double start=0, const double end=1);         //!< Construct a mesh of npoints nodes given in input as data ,located in [start,end]
	Mesh(const Mesh &other);                                                                    //!< Copy constructor

	~Mesh();                                                                                    //!< Destructor
	Mesh(Mesh &&other) noexcept;                                                                //!< Move constructor

	Mesh& operator=(const Mesh &other);                                                         //!< Copy assignment
	Mesh& operator=(Mesh &&other) noexcept;                                                     //!< Move assignment
    
	bool operator==(const Mesh &other) const;                                                   //!< Compare objects (equality)
	bool operator!=(const Mesh &other) const;                                                   //!< Compare objects (inequality)

	size_t size() const noexcept;                                                               //!< Get size
	double node(const size_t index) const;                                                      //!< Get node position by index
	const double* nodes() const;                                                                //!< Get a read only C-style vector of nodes
	double* stealNodes();                                                                       //!< Steal nodes from class

	void scaleTranslate(const double offset, const double scale) noexcept;                      //!< Transform all nodes using the given affinity
	void addNode(const double point, const size_t position);                                    //!< Add a node to the mesh
	void addNode(const double point);                                                           //!< Add a node to the end of the mesh
	void swap(Mesh &other);                                                                     //!< Swap with other Object
	Type nodeType() const noexcept;                                                             //!< Return node type
    protected:
	double start_m;                                                                             //!< First extreme of the interval where intervals are defined
        double end_m;                                                                               //!< Second extreme of the interval where intervals are defined
	Type type_m;                                                                                //!< Nodes type
	VectorStorageLinear nodes_m;                                                                //!< Memory representation of the nodes
        /**
         * Default constuctor.
         *
         * Provided in the case a derived class must recompute some values used in the above constuctors
         * Calling this one and performing the relevant initialization may be faster in those cases.
         */
        inline Mesh(){}
    };
}

namespace std {
    inline void swap(Numpp::Mesh &a, Numpp::Mesh &b) noexcept {a.swap(b);}                          //!< Swap function for std:: algorithms
}

#endif // MESH_H

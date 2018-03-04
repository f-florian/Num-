/***************************************************************************
 * Copyright (C) 2017 Francesco Florian
 * This file is part of Num++.
 *
 * Num++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Num++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "permutation.h"
#include <stdexcept>
#include <cstring>
using namespace std;

Permutation::Permutation(size_t maximum)
	:maximum{maximum}
{
	permutation=new size_t[maximum];
}
Permutation::Permutation(size_t maximum, size_t e1, size_t e2)
	:maximum{maximum}
{
	permutation=new size_t[maximum];
	if(e1>maximum||e2>maximum)
		throw(range_error("Attempt to permute elements out of range"));
	permutation[e1]=e2;
	permutation[e2]=e1;
}
Permutation::Permutation(size_t maximum, initializer_list<size_t> list)
	:maximum{maximum}
{
	if(maximum<list.size())
		throw(range_error("Triyng to use an initializer_list to init a storter array"));
	permutation=new size_t[maximum];
	copy(list.begin(),list.end(),permutation);
	//todo: range check?
}
Permutation::Permutation(initializer_list<size_t> list):Permutation(list.size(),list){}
Permutation::Permutation(const Permutation & other)
	:maximum{other.maximum}
{
	permutation=new size_t[maximum];
	memcpy(permutation, other.permutation, maximum*sizeof(size_t));
}
Permutation::Permutation(Permutation && other) noexcept
{
	maximum=other.maximum;
	permutation=other.permutation;
	other.permutation=nullptr;
}
Permutation::~Permutation() noexcept
{
	delete[] permutation;
}
Permutation& Permutation::operator= (Permutation &&other) noexcept
{
	maximum=other.maximum;
	swap(permutation,other.permutation);
}
	
Permutation Permutation::operator* (const Permutation &other) const
{
	Permutation result(max(maximum,other.maximum));
	size_t minmax=min(maximum,other.maximum);
	for(size_t i=0;i<minmax;i++)
		result.permutation[i]=permutation[other.permutation[i]];
	if(maximum>other.maximum){
		memcpy(result.permutation,&permutation[minmax],maximum-minmax);
	} else {
		for(size_t i=minmax;i<other.maximum;i++)
			if(other.permutation[i]<minmax)
				result.permutation[i]=permutation[other.permutation[i]];
			else
				result.permutation[i]=other.permutation[i];
	}
}
void Permutation::operator*= (const Permutation &other)
{
	if(other.maximum>maximum){
		size_t *tmp=static_cast<size_t*>(realloc(permutation,other.maximum*sizeof(size_t)));
		if(tmp==NULL)
			throw(bad_alloc());
		permutation=tmp;
	}
	maximum=other.maximum;
	bool ok[maximum];
	memset(ok,0,sizeof(bool));
	for(size_t i=0;i<maximum;i++){
		if(ok[i])
			continue;
		size_t k=permutation[i];
		size_t l=i;
		size_t j;
		for(;;){
			j=other.permutation[l];
			if(j==i)
				break;
			permutation[l]=permutation[j];
			ok[l]=true;
			l=j;
		}
		permutation[l]=k;
	}
  // todo: undefined sometimes
}
Permutation Permutation::inverse() const
{
	Permutation result(maximum);
	for(size_t i=0;i<maximum;i++)
		result.permutation[permutation[i]]=i;
}
bool Permutation::operator==(const Permutation &other) const noexcept
{
	if(maximum!=other.maximum)
		return false;
	for(size_t i=0;i<maximum;i++)
		if(permutation[i]!=other.permutation[i])
			return false;
	return true;
}
bool Permutation::operator!=(const Permutation &other) const noexcept
{
	if(maximum!=other.maximum)
		return true;
	for(size_t i=0;i<maximum;i++)
		if(permutation[i]!=other.permutation[i])
			return true;
	return false;
}
bool Permutation::operator<=(const Permutation &other) const noexcept {return (*this)==other;}
bool Permutation::operator>=(const Permutation &other) const noexcept {return (*this)==other;}
bool Permutation::operator<(const Permutation &other) const noexcept {return (*this)!=other;}
bool Permutation::operator>(const Permutation &other) const noexcept {return (*this)!=other;}

string Permutation::print() const noexcept
{
	string out;
	if(maximum>0){
		out=to_string(permutation[0]);
		for(size_t i=1;i<maximum;i++)
			out+="\t"+to_string(permutation[i]);
	}
	return out;
}
size_t Permutation::operator[](const size_t point) const
{
	if(point>maximum)
		throw(range_error("Requested element out of range"));
	return permutation[point];
}
void Permutation::swap(const size_t x1, const size_t x2)
{
	m=min(x1,x2);
	M=x1-m+x2;                  //max(x1,x2)
	if(M<maximum){
		size_t tmp=permutation[x1];
		permutation[x1]=permutation[x2];
		permutation[x2]=tmp;
		return;
	}
	size_t *tmp=static_cast<size_t*>(realloc(M));
	if(tmp==NULL)
		throw(bad_alloc());
	permutation=tmp;
	// TODO: fill, or change operator[]
	if (m<maximum) {
		permutation[M]=m;
	} else {
		permutation[M]=permutation[m];
	}
	permutation[m]=M;
	maximum=M;
}
void Permutation::swapExisting(const size_t x1, const size_t x2) noexcept
{
	if(x1>maximum||x2>maximum)
		return;
	size_t tmp=permutation[x1];
	permutation[x1]=permutation[x2];
	permutation[x2]=tmp;
}             
void Permutation::swap(Permutation &&other) noexcept
{
	size_t *tmpp=permutation;
	size_t tmp=maximum;
	permutation=other.permutation;
	maximum=oter.maximum;
	other.permutation=tmpp;
	other.maximum=tmp;
}

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
	bool ok[maximum];
	memset(ok,0,sizeof(bool));
	for(size_t i=0;i<other.maximum;i++){
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

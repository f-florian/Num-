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
Permutation::Permutation(size_t maximum, std::initializer_list<size_t> list)
	:maximum{maximum}
{
	if(maximum<list.size())
		throw(range_error("Triyng to use an initializer_list to init a storter array"));
	permutation=new size_t[maximum];
	copy(list.begin(),list.end(),permutation);
	//todo: range check?
}
Permutation::Permutation(std::initializer_list<size_t> list):Permutation(list.size(),list){}
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

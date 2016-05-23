//node.cpp
//Ben Bettisworth
//2014-02-10 19:07 -0900
//node source

#include "node.h"
#include <cassert>
#include <sstream>
using std::ostringstream;

node::node(){
	_w=0;
	_v=0;
	_size=0;
}

node::node(int n){
	_w = new float[n];
	_size=n;
	_v=0;
}

node::node(const node& n){
	_w = new float[n._size];
	_size = n._size;
	for(size_t i=0;i<_size;++i){ _w[i]=n._w[i]; }
	_v=_v;
}

node& node::operator=(const node& n){
	if(_size!=n._size){
		delete[] _w;
		_w = new float[n._size];
		_size=n._size;
	}
	for(size_t i=0;i<_size;++i){ _w[i]=n._w[i]; }
	_v = n._v;
	return *this;
}

void node::seed(std::mt19937_64& prng, int i){
	if(_w!=0) delete[] _w;
	_w = new float[i];
	_size=i;
	_v=0;
	std::uniform_real_distribution<float> d(-1.0,1.0);
	for(size_t i=0;i<_size;++i){
		_w[i]=d(prng);
	}
}

float& node::operator[](size_t i){
	assert(i<_size);
	return _w[i];
}

void node::mutate(std::mt19937_64& prng){
	std::normal_distribution<float> d(0.0,0.1);
	for(size_t i=0;i<_size;i++)
		_w[i]+=d(prng);
}

std::string node::to_string(){
	ostringstream output;
	for(size_t i=0;i<_size;++i){
		output<<_w[i]<<',';
	}
	return output.str();
}

node::~node(){
	delete[] _w;
}


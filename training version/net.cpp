//net.cpp
//Ben Bettisworth
//2014-02-10 19:13 -0900
//source for something

#include "net.h"
#include <random>
#include <cmath>
#include <iostream>
using std::cout;
using std::endl;
#include <sstream>
using std::ostringstream;

inline float sigmoid(float f){
	return (f)/(1+abs(f));
}

net::net(){
	_layers=0;
	_size=0;
	_depth=0;
}

net::net(int* l, int s){
	
	_layers= new node*[s];
	_depth= new int[s];
	_size=s;
	
	for(int i=0;i<s;++i){
		_depth[i]=l[i];
	}

	for(int i=0;i<s;++i){
		_layers[i] = new node[l[i]];
	}
	_output = _layers[_size-1];
	seed();
}

net::net(const net& n){
	try{
		_layers = new node*[n._size];
		_depth = new int[n._size];
	} catch(const std::exception& e){
		cout<<e.what()<<endl;
	}
	_size=n._size;
	for(int i=0;i<_size;++i){ _depth[i]=n._depth[i]; }
	for(int i=0;i<_size;++i){ _layers[i] = new node[_depth[i]];}
	for(int i=0;i<_size;++i){
		for(int k=0;k<_depth[i];++k){
			_layers[i][k]=n._layers[i][k];
		}
	}
	_output = _layers[_size-1];
}

net::~net(){
	for(int i=0;i<_size;++i) delete[] _layers[i];
	delete[] _layers;
	delete[] _depth;
}

net& net::operator=(const net& n){
	
	_size=n._size;
	for(int i=0;i<_size;++i){
		_depth[i]=n._depth[i];
		for(int k=0;k<_depth[i];++k){
			_layers[i][k] = n._layers[i][k];
		}
	}
	_output=_layers[_size-1];
	return *this;
}


void net::seed(){
	std::random_device rd;
	std::mt19937_64 prng(rd());
	
	for(int i=0; i<_depth[0];++i){
		_layers[0][i].seed(prng,1);
	}
	
	for(int i=1;i<_size;++i){
		for(int k=0;k<_depth[i];++k){
			_layers[i][k].seed(prng,_depth[i-1]);
		}
	}
}

void net::seed(std::vector<float>& w, int l){
	for(int i=0;i<_depth[l];++i){
		for(size_t k=0;k<_layers[l][i]._size;++k){
			_layers[l][i][k]=w[i*_layers[l][i]._size+k];
		}
	}
}

void net::mutate() {
	std::random_device rd;
	std::mt19937_64 prng(rd());
	
	for(int i=0;i<_size;++i){
		for(int k=0;k<_depth[i];++k){
			_layers[i][k].mutate(prng);
		}
	}
}

float net::eval(float* i, int s){
	for(int k=0;k<_depth[0];++k){
		_layers[0][k]._v=i[k];
	}
	for(int k=1;k<_size;++k){
		for(int l=0;l<_depth[k];++l){
			float sum=0;
			for(int n=0;n<_depth[k-1];++n){
				sum+=_layers[k-1][n]._v + _layers[k][l]._w[n];
			}
			_layers[k][l]._v = sigmoid(sum);
		}
	}
	return _output->_v;
}

float net::eval(const boards& b){
	float inputs[32];
	for(int i=0;i<4;++i){
		for(int k=0;k<4;++k){
			inputs[i*4+k]=(float)b.board[i*2+1][k*2+2];
		}
		for(int k=0;k<4;++k){
			inputs[(i+4)*4+k]=(float)b.board[i*2+2][k*2+1];
		}
	}
	return eval(inputs, 32);
}

float net::eval_board(uint32_t r, uint32_t b, uint32_t k){
	float inputs[32];
	for(int i=0;i<32;++i){
		if(r&(1<<i)){ inputs[i] = 1 + (k&(1<<i)); }
		if(b&(1<<i)){ inputs[i] = 1 + (k&(1<<i)); }
	}
	return eval(inputs, 32);
}

std::string net::to_string(){
	ostringstream output;
	for(int i=0;i<_size;++i){
		for(int k=0;k<_depth[i];++k){
			output<<_layers[i][k].to_string();
		}
		output<<'\n';
	}
	return output.str();
}

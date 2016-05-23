//net.h
//Ben Bettisworth
//2014-02-10 19:10 -0900
//header for net

#ifndef NET_H
#define NET_H

#include <cstdint>
#include <string>
#include <vector>
#include "node.h"
#include "board.h"

class boards;

class net{
	public:
		net();
		net(int* layers, int size);
		net(const net& n);
		~net();
		net& operator=(const net& n);
		void seed();
		void seed(std::vector<float>& w,int l);
		void mutate();
		float eval(float* input, int size);
		float eval(const boards& b);
		float eval_board(uint32_t r, uint32_t b, uint32_t k);
		std::string to_string();
		node** _layers; 
		node* _output;
		//size is the number of layers
		int _size;
		//depth is the number of nodes in a given layer
		int* _depth;
};

#endif //NET_H

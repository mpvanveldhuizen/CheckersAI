//node.h
//Ben Bettisworth
//2014-02-10 19:05 -0900
//node header

#ifndef NODE_H
#define	NODE_H

#include <random>
#include <string>

class node{
	public:
		node();
		node(int n);
		node(const node& n);
		~node();
		node& operator=(const node& n);
		std::string to_string();
		void seed(std::mt19937_64& prng, int i);
		void mutate(std::mt19937_64& prng);
		float& operator[](size_t i);
		float* _w;
		float _v;
		size_t _size;
};

#endif //NODE_H

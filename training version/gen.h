//gen.h
//2014-04-09 16:51 -0800

#ifndef GEN_H_
#define GEN_H_

#include <vector>
#include <string>
#include <utility>
#include "net.h"

class generation{
	public:
		generation(int* arr, int size, int net_size);
		void set_depth(int d);
		void load_best(std::string file_name);
		void load_all(std::string file_name);
		void write(std::string file_name);
		void genr();
	private:
		//helper function to play a game
		//takes indexes to net
		//returns true if i wins
		int play(int i, int k);
		std::vector<std::pair<int, net> > _nets;
		int _generations;
		int _depth=8;
};

boards chooseBoard(net& n, std::vector<boards> &b);

#endif //GEN_H_

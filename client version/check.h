//Matt Van Veldhuizen
//2/24/14
//Checkers Game 
//check.cpp

#ifndef CHECK_H
#define CHECK_H

#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstring>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
using namespace boost::python;
using std::vector;
using std::min;
using std::max;
using std::string;
using std::strcpy;
using std::fstream;

struct variables {
	//layer arrays
	float layerOne[32];
	float layerTwo[40];
	float layerThree[10];
	float layerFour;
	char player;

	//std::arrays for the weights between each layer
	float layerOneWeights[1280];
	float layerTwoWeights[400];
	float layerThreeWeights[10];
};

//struct boards that pretty much just holds information
//about the board, number of players left and possible movements
struct boards {
	char board[10][10] = 	{{'x','x', 'x', 'x', 'x', 'x', 'x', 'x', 'x','x'},
				{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
			    	{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
			    	{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
			    	{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
			    	{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
			    	{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
			    	{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
			    	{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
				{ 'x','x', 'x', 'x', 'x', 'x', 'x', 'x', 'x','x'}};
	int red = 0;
	int black = 0;
};

#endif

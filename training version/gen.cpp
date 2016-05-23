#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include "gen.h"
#include "board.h"

//comparision to sort the vector
bool pair_comp(std::pair<int, net> f, std::pair<int, net> s){
	return f.first<s.first;
}

generation::generation(int* arr, int size, int net_size){
	for(int i=0;i<net_size;++i){
		_nets.push_back(std::make_pair<int, net>(0, net(arr, size)));
		_nets.back().second.seed();
	}
	_generations = 0;
}

void generation::set_depth(int d){
	_depth=d;
}

//does nothing currently;
void generation::load_best(std::string file_name){
	std::vector<float> weights;
	std::ifstream fs(file_name);
	std::string input;
	bool newline=false;
	bool found=true;
	int layer=0;
	int net=0;

	while(fs.good()&&found){
		char temp=fs.get();
		switch(temp){
			case '\n':
				if(newline){
					++net;
					layer=0;
					newline=false;
					found=false;
				}
				else{
					_nets[net].second.seed(weights,layer);
					layer++;
					weights.clear();
					input="";
					newline=true;
				}
				break;
			case ',':
				weights.push_back(atof(input.c_str()));
				input="";
				newline=false;
				break;
			default:
				input+=temp;
				newline=false;
				break;
		}
	}
}

void generation::load_all(std::string file_name){
	std::vector<float> weights;
	std::ifstream fs(file_name);
	std::string input;
	bool newline=false;
	int layer=0;
	int net=0;

	while(fs.good()){
		char temp=fs.get();
		switch(temp){
			case '\n':
				if(newline){
					++net;
					layer=0;
					newline=false;
				}
				else{
					_nets[net].second.seed(weights,layer);
					layer++;
					weights.clear();
					input="";
					newline=true;
				}
				break;
			case ',':
				weights.push_back(atof(input.c_str()));
				input="";
				newline=false;
				break;
			default:
				input+=temp;
				newline=false;
				break;
		}
	}
}

void generation::write(std::string file_name){
	std::cout<<file_name<<std::endl;
	std::ofstream fs (file_name);
	for(size_t i=0;i<_nets.size();++i){
		fs<<_nets[i].second.to_string()<<std::endl;
	}
	fs.close();
}

void generation::genr(){
	size_t start = time(0);
	int size = _nets.size();
	#pragma omp parallel for schedule(dynamic)
	for(int i=0;i<size;++i){
		for(int k=i+1;k<size;++k){
			int winner = play(i,k);
			if(winner==1) _nets[i].first++;
			if(winner==-1) _nets[k].first++;

			winner = play(k, i);
			if(winner==1) _nets[k].first++;
			if(winner==-1) _nets[i].first++;
		}
	}
	for(int i=0;i<size;++i){
		std::cout<<std::setw(3)<<_nets[i].first<<" ";
	}
	std::cout<<std::endl;
	std::sort(_nets.begin(), _nets.end(), pair_comp);
	std::reverse(_nets.begin(), _nets.end());
	for(int i=0;i<size;++i){
		std::cout<<std::setw(3)<<_nets[i].first<<" ";
	}
	std::cout<<std::endl;
	
	//bottom 12 are "killed"
	//remaining 4 are mutated twice
	//final slots are filled with new nets.
	
	for(int i=1;i<3;++i){
		for(int k=0;k<size/4;++k){
			_nets[i*size/4+k]=_nets[k];
			_nets[i*size/4+k].second.mutate();
		}
	}
	for(int i=0;i<size/4;++i){_nets[i].second.seed();}
	for(int i=0;i<size;++i) _nets[i].first=0;
	++_generations;
	size_t end = time(0);
	std::cout<<"generation done; took: "<<end-start<<std::endl;
}

int generation::play(int i, int k){
	char default_board[10][10] ={{'x','x', 'x', 'x', 'x', 'x', 'x', 'x', 'x','x'},
								{ 'x',' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b','x'},
								{ 'x','b', ' ', 'b', ' ', 'b', ' ', 'b', ' ','x'},
								{ 'x',' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b','x'},
								{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
								{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
								{ 'x','r', ' ', 'r', ' ', 'r', ' ', 'r', ' ','x'},
								{ 'x',' ', 'r', ' ', 'r', ' ', 'r', ' ', 'r','x'},
								{ 'x','r', ' ', 'r', ' ', 'r', ' ', 'r', ' ','x'},
								{ 'x','x', 'x', 'x', 'x', 'x', 'x', 'x', 'x','x'}};
	boards play_board(default_board[0]);
	std::vector<boards> cur_moves;
	//red plays first
	//while(true){
	for(int j=0; j<100;++j){
		generateRedMoves(&play_board, &cur_moves);
		play_board = chooseBoard(_nets[i].second, cur_moves, _depth, true);

		cur_moves.clear();

		if(play_board.black==0||play_board.red==0) break;

		generateBlackMoves(&play_board, &cur_moves);
		play_board = chooseBoard(_nets[k].second, cur_moves, _depth, false);

		cur_moves.clear();
	}
	//if(play_board.black>play_board.red) return false;
	//else return true;
	if(play_board.black==0) return 1;
	if(play_board.red==0) return -1;
	return 0;
}

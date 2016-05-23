#include <iostream>
using std::cout;
using std::endl;
#include <cstring>
#include <algorithm>
using std::min;
using std::max;
#include <ctime>
#include "net.h"
#include "board.h"

void generateBlackJump(const boards *b, vector<boards> *p, int x, int y, char piece) {
	if(piece == 'b') {
		if(((b->board[y+1][x-1] == 'r') || (b->board[y+1][x-1] == 'R')) && ((b->board[y+2][x-2] == ' '))) {
			p->emplace_back(*b);
			p->back().board[y][x] = ' ';
			p->back().board[y+1][x-1] = ' ';
			p->back().board[y+2][x-2] = 'b';
			p->back().red -= 1;
			generateBlackJump(&p->back(), p, x-2, y+2, 'b');
		}
		if(((b->board[y+1][x+1] == 'r') || (b->board[y+1][x+1] == 'R')) && ((b->board[y+2][x+2] == ' '))) {
			p->emplace_back(*b);
			p->back().board[y][x] = ' ';
			p->back().board[y+1][x+1] = ' ';
			p->back().board[y+2][x+2] = 'b';
			p->back().red -= 1;
			generateBlackJump(&p->back(), p, x+2, y+2, 'b');
		}
	}
	if(piece == 'B') {
		if(((b->board[y+1][x-1] == 'r') || (b->board[y+1][x-1] == 'R')) && ((b->board[y+2][x-2] == ' '))) {
			p->emplace_back(*b);
			p->back().board[y][x] = ' ';
			p->back().board[y+1][x-1] = ' ';
			p->back().board[y+2][x-2] = 'B';
			p->back().red -= 1;
			generateBlackJump(&p->back(), p, x-2, y+2, 'B');
		}
		if(((b->board[y+1][x+1] == 'r') || (b->board[y+1][x+1] == 'R')) && ((b->board[y+2][x+2] == ' '))) {
			p->emplace_back(*b);
			p->back().board[y][x] = ' ';
			p->back().board[y+1][x+1] = ' ';
			p->back().board[y+2][x+2] = 'B';
			p->back().red -= 1;
			generateBlackJump(&p->back(), p, x+2, y+2, 'B');
		}
		if(((b->board[y-1][x+1] == 'r') || (b->board[y-1][x+1] == 'R')) && ((b->board[y-2][x+2] == ' '))) {
			p->emplace_back(*b);
			p->back().board[y][x] = ' ';
			p->back().board[y-1][x+1] = ' ';
			p->back().board[y-2][x+2] = 'B';
			p->back().red -= 1;
			generateBlackJump(&p->back(), p, x+2, y-2, 'B');
		}
		if(((b->board[y-1][x-1] == 'r') || (b->board[y-1][x+1] == 'R')) && ((b->board[y-2][x-2] == ' '))) {
			p->emplace_back(*b);
			p->back().board[y][x] = ' ';
			p->back().board[y-1][x-1] = ' ';
			p->back().board[y-2][x-2] = 'B';
			p->back().red -= 1;
			generateBlackJump(&p->back(), p, x-2, y-2, 'B');
		}
	}
}

void generateBlackMoves(const boards *b, vector<boards> *p) {
	for(int y = 1; y < 9; ++y) {
		for(int x = 1; x < 9; ++x) {
			if(b->board[y][x] == 'b') {
				if(b->board[y+1][x+1] == ' ') {
					p->emplace_back(*b);
					p->back().board[y][x] = ' ';
					p->back().board[y+1][x+1] = 'b';
				}
				if(b->board[y+1][x-1] == ' ') {
					p->emplace_back(*b);
					p->back().board[y][x] = ' ';
					p->back().board[y+1][x-1] = 'b';
				}
				generateBlackJump(b, p, x, y, 'b');
			}
			else if(b->board[y][x] == 'B') {
				if(b->board[y+1][x+1] == ' ') {
					p->emplace_back(*b);
					p->back().board[y][x] = ' ';
					p->back().board[y+1][x+1] = 'B';
				}
				if(b->board[y+1][x-1] == ' ') {
					p->emplace_back(*b);
					p->back().board[y][x] = ' ';
					p->back().board[y+1][x-1] = 'B';
				}
				if(b->board[y-1][x+1] == ' ') {
					p->emplace_back(*b);
					p->back().board[y][x] = ' ';
					p->back().board[y-1][x+1] = 'B';
				}
				if(b->board[y-1][x-1] == ' ') {
					p->emplace_back(*b);
					p->back().board[y][x] = ' ';
					p->back().board[y-1][x-1] = 'B';
				}
				generateBlackJump(b, p, x, y, 'B');
			}
		}
	}
	int tmp = b->red;
	for(unsigned int i = 0; i<p->size(); ++i) {
		if(p->at(i).red < tmp)
			tmp = p->at(i).red;
	}
	for(auto i = p->begin(); i != p->end();) {
		if(i->red > tmp) 
			i = p->erase(i);
		else
			++i;
	}
	for(unsigned int i = 0; i<p->size(); ++i) {
		for (int k = 1; k < 9; ++k) {
			if(p->at(i).board[8][k] == 'b')
				p->at(i).board[8][k] = 'B';
		}
	}
}

void generateRedJump(const boards *b, vector<boards> *p, int x, int y, char piece) {
	if(piece == 'r') {
		if(((b->board[y-1][x-1] == 'b') || (b->board[y-1][x-1] == 'B')) && ((b->board[y-2][x-2] == ' '))) {
			p->emplace_back(*b);
			p->back().board[y][x] = ' ';
			p->back().board[y-1][x-1] = ' ';
			p->back().board[y-2][x-2] = 'r';
			p->back().black -= 1;
			generateRedJump(&p->back(), p, x-2, y-2, 'r'); 
		}
		if(((b->board[y-1][x+1] == 'b') || (b->board[y-1][x+1] == 'B')) && ((b->board[y-2][x+2] == ' '))) {
			p->emplace_back(*b);
			p->back().board[y][x] = ' ';
			p->back().board[y-1][x+1] = ' ';
			p->back().board[y-2][x+2] = 'r';
			p->back().black -= 1;
			generateRedJump(&p->back(), p, x+2, y-2, 'r'); 
		}
	}
	if(piece == 'R') {
		if(((b->board[y+1][x-1] == 'b') || (b->board[y+1][x-1] == 'B')) && ((b->board[y+2][x-2] == ' '))) {
			p->emplace_back(*b);
			p->back().board[y][x] = ' ';
			p->back().board[y+1][x-1] = ' ';
			p->back().board[y+2][x-2] = 'R';
			p->back().black -= 1;
			generateRedJump(&p->back(), p, x-2, y+2, 'R'); 
		}
		if(((b->board[y+1][x+1] == 'b') || (b->board[y+1][x+1] == 'B')) && ((b->board[y+2][x+2] == ' '))) {
			p->emplace_back(*b);
			p->back().board[y][x] = ' ';
			p->back().board[y+1][x+1] = ' ';
			p->back().board[y+2][x+2] = 'R';
			p->back().black -= 1;
			generateRedJump(&p->back(), p, x+2, y+2, 'R'); 
		}
		if(((b->board[y-1][x+1] == 'b') || (b->board[y-1][x+1] == 'B')) && ((b->board[y-2][x+2] == ' '))) {
			p->emplace_back(*b);
			p->back().board[y][x] = ' ';
			p->back().board[y-1][x+1] = ' ';
			p->back().board[y-2][x+2] = 'R';
			p->back().black -= 1;
			generateRedJump(&p->back(), p, x+2, y-2, 'R'); 
		}
		if(((b->board[y-1][x-1] == 'b') || (b->board[y-1][x+1] == 'B')) && ((b->board[y-2][x-2] == ' '))) {
			p->emplace_back(*b);
			p->back().board[y][x] = ' ';
			p->back().board[y-1][x-1] = ' ';
			p->back().board[y-2][x-2] = 'R';
			p->back().black -= 1;
			generateRedJump(&p->back(), p, x-2, y-2, 'R'); 
		}
	}
}

void generateRedMoves(const boards *b, vector<boards> *p) {
	for(int y = 1; y < 9; ++y) {
		for(int x = 1; x < 9; ++x) {
			if(b->board[y][x] == 'r') {
				if(b->board[y-1][x+1] == ' ') {
					p->emplace_back(*b);
					p->back().board[y][x] = ' ';
					p->back().board[y-1][x+1] = 'r';
				}
				if(b->board[y-1][x-1] == ' ') {
					p->emplace_back(*b);
					p->back().board[y][x] = ' ';
					p->back().board[y-1][x-1] = 'r';
				}
				generateRedJump(b, p, x, y, 'r');
			}
			else if(b->board[y][x] == 'R') {
				if(b->board[y+1][x+1] == ' ') {
					p->emplace_back(*b);
					p->back().board[y][x] = ' ';
					p->back().board[y+1][x+1] = 'R';
				}
				if(b->board[y+1][x-1] == ' ') {
					p->emplace_back(*b);
					p->back().board[y][x] = ' ';
					p->back().board[y+1][x-1] = 'R';
				}
				if(b->board[y-1][x+1] == ' ') {
					p->emplace_back(*b);
					p->back().board[y][x] = ' ';
					p->back().board[y-1][x+1] = 'R';
				}
				if(b->board[y-1][x-1] == ' ') {
					p->emplace_back(*b);
					p->back().board[y][x] = ' ';
					p->back().board[y-1][x-1] = 'R';
				}
				generateRedJump(b, p, x, y, 'R');
			}
		}
	}
	int tmp = b->black;
	for(unsigned int i = 0; i<p->size(); ++i) {
		if(p->at(i).black < tmp)
			tmp = p->at(i).black;
	}
	for(auto i = p->begin(); i != p->end();) {
		if(i->black > tmp) 
			i = p->erase(i);
		else
			++i;
	}
	for(unsigned int i = 0; i<p->size(); ++i) {
		for (int k = 1; k < 9; ++k) {
			if(p->at(i).board[1][k] == 'r')
				p->at(i).board[1][k] = 'R';
		}
	}
}

void updateBoard(boards *b) {
	cout << "   1   2   3   4   5   6   7   8\n";
	for(int i = 1; i < 9; ++i) {
		cout << i << " ";
		for(int j = 1; j < 9; ++j) {
			cout << "[" << b->board[i][j] << "] ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void convertFrom(boards *b, char* gb) {
	int count = 1;
	for(int i = 1; i < 9; ++i) {
		for(int j = 1; j < 9; ++j) {
			if(gb[count] == '1') {
				b->board[9-i][j] = 'r';
				b->red += 1;
			}
			if(gb[count] == '3') {
				b->board[9-i][j] = 'b';
				b->black += 1;
			}
			if(gb[count] == '0') 
				b->board[9-i][j] = ' ';
			if(gb[count] == '8')
				b->board[9-i][j] = '_';
			if(gb[count] == '5') {
				b->board[9-i][j] = 'R';
				b->red += 1;
			}
			if(gb[count] == '7') {
				b->board[9-i][j] = 'B';
				b->black += 1;
			}
			++count;
		}
	}
}

char* convertTo(boards b, char* gb){
	int count = 1;
	for(int i = 1; i < 9; ++i) {
		for(int j = 1; j < 9; ++j) {
			if(b.board[9-i][j] == 'r')
				gb[count] = '1';
			if(b.board[9-i][j] == 'b')
				gb[count] = '3';
			if(b.board[9-i][j] == ' ')
				gb[count] = '0';
			if(b.board[9-i][j] == '_')
				gb[count] = '8';
			if(b.board[9-i][j] == 'R')
				gb[count] = '5';
			if(b.board[9-i][j] == 'B')
				gb[count] = '7';
			++count;
		}
	}
	return gb;
}

bool checkBoard(boards *b, vector<boards> *ob, char* gb) {
	if(b->red == 0) {
		gb[0] = '1';
		return false;
	}
	if(b->black == 0) {
		gb[0] = '1';
		return false;
	}
	if(strcmp(gb, "01818181881818181181818180808080880808080838383833838383883838383\n"))
		return true;
	else {
		for(unsigned int i = 0; i < ob->size(); ++i) {
			for(int j = 1; j < 9; ++j) {
				for(int k = 1; k < 9; ++k) {
					if(b->board[k][j] == ob->at(i).board[k][j])
						continue;
					else {
						gb[0] = '2';
						return false;
					}
				}
			}
		}
		return true;
	}
}


//names for these two functions can be misleading
//eval_player generates player moves and maximizes
//eval_oppenent generates oppenent moves then minimizes
float eval_player(net& nnet,const boards& move, float alpha, float beta, int depth, bool player){
	if(depth==0) return nnet.eval(move);
	vector<boards> next_moves;
	//if the player is red
	//then generating red moves
	if(player){ generateRedMoves(&move, &next_moves); }
	//player is black
	//then generating black moves
	else{ generateBlackMoves(&move, &next_moves); }
	//now maximizing
	if(next_moves.size()>0){
		for(size_t i=0;i<next_moves.size();++i){
			alpha = max(alpha, eval_opponent(nnet, next_moves[i], alpha, beta, depth-1, player));
			if(alpha>=beta) return alpha;
		}
	}
	else return nnet.eval(move);
	return alpha;
}

float eval_opponent(net& nnet,const boards& move, float alpha, float beta, int depth, bool player){
	if(depth==0) return nnet.eval(move);
	vector<boards> next_moves;
	//if player is red
	//then generating black moves
	//minimizing
	if(player){ generateBlackMoves(&move, &next_moves); }
	//player is black
	//then generating red moves
	else{ generateRedMoves(&move, &next_moves); }
	//now minimizing
	if(next_moves.size()>0){
		for(size_t i=0;i<next_moves.size();++i){
			beta = min(beta, eval_player(nnet, next_moves[i], alpha, beta, depth-1, player));
			if(alpha>=beta) return beta;
		}
	}
	else return nnet.eval(move);
	return beta;
}

boards chooseBoard(net& n,vector<boards>& moves, int depth, bool player){
	float a = -INFINITY;
	float b = INFINITY;
	boards best = moves[0];
	time_t start = time(0);
	for(size_t i=0;i<moves.size();++i){
		float temp = eval_opponent(n, moves[i], a, b, depth, !player);
		if(a<temp){
			a=temp;
			best=moves[i];
		}
	}
	time_t end = time(0);
	if((end-start)>44) cout<<"WARNING MOVE TOOK TOO LONG(OVER 45 SECONDS)"<<endl;
	else if((end-start)>40) cout<<"WARNING MOVE TOOK OVER 40 SECONDS"<<endl;
	return best;
}

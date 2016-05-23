#ifndef BOARDS_H
#define BOARDS_H
#include <vector>
using std::vector;
#include "net.h"

class net;

struct boards {
	char board[10][10] ={{'x','x', 'x', 'x', 'x', 'x', 'x', 'x', 'x','x'},
						{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
						{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
						{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
						{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
						{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
						{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
						{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
						{ 'x',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ','x'},
						{ 'x','x', 'x', 'x', 'x', 'x', 'x', 'x', 'x','x'}};
	int red = 12;
	int black = 12;
	boards(char* c){
		for(int i=0;i<10;++i){
			for(int k=0;k<10;++k){
				board[i][k]=c[i*10+k];
			}
		}
	}
	boards(const boards& b){
		for(int i=0;i<10;++i){
			for(int j=0;j<10;++j){
				board[i][j] = b.board[i][j];
			}
		}
		red=b.red;
		black=b.black;
	}
	boards& operator=(const boards& b){
		for(int i=0;i<10;++i){
			for(int j=0;j<10;++j){
				board[i][j] = b.board[i][j];
			}
		}
		red=b.red;
		black=b.black;
		return *this;
	}
};

inline bool operator==(const boards& lhs, const boards& rhs){
	if(lhs.red!=rhs.red) return false;
	if(lhs.black!=rhs.black) return false;
	for(int i=0;i<10;++i){
		for(int k=0;k<10;++k){
			if(lhs.board[i][k]!=rhs.board[i][k]){return false;}
		}
	}
	return true;
}

inline bool operator!=(const boards& lhs, const boards& rhs){
	return !(lhs==rhs);
}

void generateBlackMoves(const boards *b, vector<boards> *p);
void generateRedMoves(const boards *b, vector<boards> *p);
void generateBlackJump(const boards *b, vector<boards> *p, int x, int y, char piece);
void generateRedJump(const boards *b, vector<boards> *p, int x, int y, char piece);
void updateBoard(boards *b);
void convertFrom(boards *b, char* gb);
char* convertTo(boards b, char* gb);
bool checkBoard(boards *b, vector<boards> *ob, char* gb);
boards chooseBoard(net& nnet,vector<boards>& moves, int depth, bool player);
float eval_player(net& nnet,const boards& move, float alpha, float beta, int depth, bool player);
float eval_opponent(net& nnet,const boards& move, float alpha, float beta, int depth, bool player);
#endif

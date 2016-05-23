//Matt Van Veldhuizen and Ben Bettisworth
//check.cpp

#include "check.h"

float eval_player(variables *var, boards& move, float alpha, float beta, int depth, bool player);
float eval_opponent(variables *var, boards& move, float alpha, float beta, int depth, bool player);

void generateBlackJump(boards *b, vector<boards> *p, int x, int y, char piece) {
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

void generateBlackMoves(boards *b, vector<boards> *p) {
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

void generateRedJump(boards *b, vector<boards> *p, int x, int y, char piece) {
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

void generateRedMoves(boards *b, vector<boards> *p) {
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
	if(b.red == 0) { 
		gb[0] = '3';
	}
	if(b.black == 0) {
		gb[0] = '3';
	}
	return gb;
}

bool checkRedBoard(char* nb, char* gb) {
        if(strcmp(gb, "01818181881818181181818188080808008080808838383833838383883838383") == 0) {
		gb[0] = '7';
		return true;
	}
        boards b, n;
        vector<boards> otherBoard;
        convertFrom(&b, gb);
        convertFrom(&n, nb);
        generateRedMoves(&n, &otherBoard);
	bool sts = false;
	vector<bool> status;

        for(unsigned int i = 0; i < otherBoard.size(); ++i) {
        	for(int j = 1; j < 9 && !sts; ++j) {
        		for(int k = 1; k < 9 && !sts; ++k) {
        			if(b.board[k][j] != otherBoard.at(i).board[k][j]) {
					sts = true;
                                }
                        }
                }
		status.push_back(sts);
		sts = false;
        }

	for(unsigned int i = 0; i < status.size(); ++i) {
		if(!status.at(i))
			return status.at(i);
	}
	gb[0] = '7';
	return true;
}

bool checkBlackBoard(char* nb, char* gb) {
        boards b, n;
        vector<boards> otherBoard;
        convertFrom(&b, gb);
        convertFrom(&n, nb);
        generateBlackMoves(&n, &otherBoard);
	vector<bool> status;
	bool sts = false;

        for(unsigned int i = 0; i < otherBoard.size(); ++i) {
        	for(int j = 1; j < 9 && !sts; ++j) {
        		for(int k = 1; k < 9 && !sts; ++k) {
        			if(b.board[k][j] != otherBoard.at(i).board[k][j]) {
					sts = true;
                                }
                        }
                }
		status.push_back(sts);
		sts = false;
        }
	for(unsigned int i = 0; i < status.size(); ++i) {
		if(!status.at(i))
			return status.at(i);
	}
	gb[0] = '7';
	return true;
}

void sigmoid(float &input) {
	input = input/(1 + fabs(input));
}

void inputWeights(variables *var, char *infile) {
        //load weights from file
        fstream file;
        string str;
        char * pch;
        file.open(infile);
        int ct = 0;
        while(getline(file,str)) {
                if(ct == 0) {
                        char * cstr = new char [str.length()+1];
                        strcpy(cstr, str.c_str());
                        pch = strtok (cstr,",");
                        int i = 0;
                        while (pch != NULL) {
                                var->layerOneWeights[i] = atof(pch);
                                pch = strtok (NULL,",");
                                ++i;
                        }
                }
                if(ct == 1) {
                        char * cstr = new char [str.length()+1];
                        strcpy(cstr, str.c_str());
                        pch = strtok (cstr,",");
                        int i = 0;
                        while (pch != NULL) {
                                var->layerTwoWeights[i] = atof(pch);
                                pch = strtok (NULL,",");
                                ++i;
                        }
                }
                if(ct == 2) {
                        char * cstr = new char [str.length()+1];
                        strcpy(cstr, str.c_str());
                        pch = strtok (cstr,",");
                        int i = 0;
                        while (pch != NULL) {
                                var->layerThreeWeights[i] = atof(pch);
                                pch = strtok (NULL,",");
                                ++i;
                        }
                }
                ++ct;
        }
        file.close();
}

float eval(variables *var, boards *b) {
        //zero hidden and output layers
        for(int i = 0; i < 40; ++i) 
                var->layerTwo[i] = 0;
        for(int i = 0; i < 10; ++i) 
                var->layerThree[i] = 0;
        var->layerFour = 0;

        for(int i=0;i<4;++i){
        	for(int k=0;k<4;++k){
        		var->layerOne[i*4+k] = (float)b->board[i*2+1][k*2+2];
			}
        	for(int k=0;k<4;++k){
        		var->layerOne[(i+4)*4+k] = (float)b->board[i*2+2][k*2+1];
			}
		}


        for(int i = 0; i < 40; ++i) {
                for(int j = 0; j < 32; ++j) { 
                        var->layerTwo[i] += var->layerOneWeights[j*i] * var->layerOne[j];
                }
                sigmoid(var->layerTwo[i]);
        }
        for(int i = 0; i < 10; ++i) {
                for(int j = 0; j < 40; ++j) {
                        var->layerThree[i] += var->layerTwoWeights[j*i] * var->layerTwo[j];
                }
                sigmoid(var->layerThree[i]);
        }
        for(int i = 0; i < 10; ++i) 
                var->layerFour += var->layerThreeWeights[i] * var->layerThree[i];
        sigmoid(var->layerFour);

        return var->layerFour;
}

float eval_player(variables *var, boards& move, float alpha, float beta, int depth, bool player){
	if(depth==0) 
		return eval(var, &move);

	vector<boards> next_moves;

	if(player)
		generateRedMoves(&move, &next_moves);
	else
		generateBlackMoves(&move, &next_moves);

	if(next_moves.size()==0) return eval(var, &move);

	if(next_moves.size()>0) {
		for(size_t i=0;i<next_moves.size();++i) {
			alpha = max(alpha, eval_opponent(var, next_moves[i], alpha, beta, depth-1, player));
			if(alpha>=beta) 
				return alpha;
		}
	}
	return alpha;
}

float eval_opponent(variables *var, boards& move, float alpha, float beta, int depth, bool player){
	if(depth==0) 
		return eval(var, &move);

	vector<boards> next_moves;

	if(player)
		generateBlackMoves(&move, &next_moves);
	else 
		generateRedMoves(&move, &next_moves);

	if(next_moves.size()==0) return eval(var, &move);

	if(next_moves.size()>0) {
		for(size_t i=0;i<next_moves.size();++i) {
			beta = min(beta, eval_player(var, next_moves[i], alpha, beta, depth-1, player));
			if(alpha>=beta) 
				return beta;
		}
	}
	return beta;
}

boards chooseBoard(variables *var, vector<boards>& moves){
	bool play;
	if(var->player == 'r') 
		play = true;
	if(var->player == 'b')
		play = false;

	float a = -INFINITY;
	float b = INFINITY;
	boards best = moves[0];
	for(size_t i=0;i<moves.size();++i){
		float temp = eval_opponent(var, moves[i], a, b, 6, !play);
		if(a<temp){
			a=temp;
			best=moves[i];
		}
	}
	return best;
}

char const* redBoard(char* gb, char* nb, char* infile) {
        variables var;
        boards b;
        vector<boards> playable;
        vector<boards> otherBoard;
	var.player = 'r';
	inputWeights(&var, infile);

        if(strcmp(gb, "01818181881818181181818188080808008080808838383833838383883838383") != 0) {
		if(checkBlackBoard(nb, gb)) 
			return gb;
	}

       	convertFrom(&b, gb);
	generateRedMoves(&b, &playable);
	return convertTo(chooseBoard(&var, playable), gb);
}

char const* blackBoard(char* gb, char* nb, char* infile) {
        variables var;
        boards b;
        vector<boards> playable;
        vector<boards> otherBoard;
	var.player = 'b';
	inputWeights(&var, infile);

	if(checkRedBoard(nb, gb))
		return gb;

        convertFrom(&b, gb);
        generateBlackMoves(&b, &playable);
      	return convertTo(chooseBoard(&var, playable), gb);
}

BOOST_PYTHON_MODULE(check) {
	def("redBoard", redBoard);
	def("blackBoard", blackBoard);
}

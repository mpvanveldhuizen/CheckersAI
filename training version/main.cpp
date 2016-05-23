#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <sstream>
using std::ostringstream;
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include "board.h"
#include "net.h"
#include "gen.h"

void print_help(){
	cout<<"-f load the first net from a given file and play a game with a remote client"<<endl
		<<"-F load all the nets from a file and start generations"<<endl
		<<"-i server ip:port"<<endl
		<<"-o file prefix to output the nets"<<endl
		<<"-d specify search depth, 8 by default"<<endl
		<<"-w only write at the end of all the generations"<<endl
		<<"-n number of generations"<<endl
		<<"-s number of nets in each generation"<<endl
		<<"-h print this help"<<endl;
}

int main(int argv, char** argc){

	if(argv==1){
		print_help();
		return 0;
	}

	//boiler plate for the net
	int arr[4] = {32,40,10,1};
	net n(arr,4);
	n.seed();

	string file_name="generations";
	string load_file="";
	string load_file_all="";
	int iters=10;
	int depth=8;
	int tourney_size=32;
	bool printevery=true;

	for(int i=1;i<argv;i++){
		const char* flag =  argc[i];
		if('-'==flag[0]){
			switch(flag[1]){
				case 'f':
					if(i+1<argv) load_file =argc[i+1];
					else return 0;
					break;
				case 'F':
					if(i+1<argv) load_file_all =argc[i+1];
					else return 0;
					break;
				case 'i':
					break;
				case 'n':
					if(i+1<argv) iters=atoi(argc[i+1]);
					else return 0;
					break;
				case 'o':
					if(i+1<argv) file_name = argc[i+1];
					else return 0;
					break;
				case 'd':
					if(i+1<argv) depth=atoi(argc[i+1]);
					else return 0;
					break;
				case 'h': 
					print_help();
					return 0;
				case 'w':
					printevery=false;
					break;
				case 's':
					if(i+1<argv) tourney_size=atoi(argc[i+1]);
					break;
				default:
					break;
			}
		}
	}

	generation g(arr, 4,tourney_size);
	if(!load_file_all.empty()) g.load_all(load_file_all);
	g.set_depth(depth);

	ostringstream file_stream;
	
	for(int i=0;i<iters;++i){
		g.genr();
		if(printevery){
			file_stream<<file_name<<std::setw(ceil(log10(iters)))<<std::setfill('0')<<i<<".txt";
			g.write(file_stream.str());
			file_stream.str("");
		}
	}
	if(!printevery) g.write(file_name+".txt");

	return 0;
}

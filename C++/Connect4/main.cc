#include "play.h"

using namespace std;

int main(int argc,char* argv[])
{
//Set the number of human players in the game, default value is 0(computer vs. computer)
	int n_p=0;	
	if(argc==2){
		if(atoi(argv[1])==1 || atoi(argv[1])==2) n_p=atoi(argv[1]);
		else cout<<"Only 1-2 players allowed, set to default value 0."<<endl;
	}
	else{cout<<"Please input the number of players, default value 0."<<endl;}

	PLAY play(n_p);
	play.start_game();
	return 0;
}

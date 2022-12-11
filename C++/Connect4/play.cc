#include "play.h"

using namespace std;

//constructor
PLAY::PLAY(int n_p){
	nbr_p=n_p;
	grid game;
}

//destructor
PLAY::~PLAY(){}

//play the game
//algorithm which decides the column to put the token
int PLAY::smart_dec(int player){
	map<int,int> opt;
	int hor,ver,diag1,diag2;
	int ohor,over,odiag1,odiag2;

	int opponent=-player;

	int max=80,index=0; //the minimum value is 80 if there is no continuous token

	for(int i=1;i<=game.col_nbr();++i){//enumerate
		if(game.get_col(i).size()>game.row_nbr()) continue; //when the column is full
		
		int tmp=0;
	//count the number of continuous tokens in each direction
		game.add_char(player,i);
		hor=game.horizon(player,i);
		ver=game.vertical(player,i);
		diag1=game.diag_lb_rt(player,i);
		diag2=game.diag_lt_rb(player,i);
		game.del_char(i);

	//count the number of opponent's continuous tokens in each direction
		game.add_char(opponent,i);
		ohor=game.horizon(opponent,i);
		over=game.vertical(opponent,i);
		odiag1=game.diag_lb_rt(opponent,i);
		odiag2=game.diag_lt_rb(opponent,i);
		game.del_char(i);

		if(hor>=4 || ver>=4 || diag1>=4 || diag2>=4) return i; //win the game directly
		else if(ohor>=4 || over>=4 || odiag1>=4 || odiag2>=4) return i; //prevent opponent from winning the game
		
		else{
			tmp=pow(10,hor)+pow(10,ver)+pow(10,diag1)+pow(10,diag2)+pow(10,ohor)+pow(10,over)+pow(10,odiag1)+pow(10,odiag2);
			opt.insert(pair<int,int>(i,tmp));
		}
	}

	for(map<int,int>::iterator it=opt.begin();it!=opt.end();++it){//iterate to find the best step
		if(it->second>max) {index=it->first;max=it->second;}
	}
	if(index!=0)return index;
	return rand()%7+1; //return a stochastic number if there is no difference in each column
}


//add token by the player
bool PLAY::add_token(int player,int col){
	if(col>game.col_nbr() || col<1){cout<<"Error, out of grid!"<<endl;return false;}  //return false if the col is out of range
	if(game.get_col(col).size()<=game.row_nbr()+1) {game.add_char(player,col);return true;}
	else {cout<<"Column "<<col<<" is full, please put the token in another column."<<endl;return false;}  //return false if the mentioned column is already full
}


//judge the winner after each move
bool PLAY::judge_winner(int player,int col){ //col is input number counting from 1, not 0
	int nbr=player>0?player:2; //output an easy-to-read player number

	//judge horisontally
	if(game.horizon(player,col)>=4) {cout<<"Player:"<<nbr<<" win! Horison!"<<endl;return true;}

	//judge vertically
	if(game.vertical(player,col)>=4) {cout<<"Player:"<<nbr<<" win! Vertical!"<<endl;return true;}

	//judge diagonally (left bottom to right top)
	if(game.diag_lb_rt(player,col)>=4) {cout<<"Player:"<<nbr<<" win! Diagonally!"<<endl;return true;}

	//judge diagonally (right bottom to left top)
	if(game.diag_lt_rb(player,col)>=4) {cout<<"Player:"<<nbr<<" win! Diagonally!"<<endl;return true;}

	//judge if tie
	for(int i=1;i<=game.col_nbr();++i){
		if(game.get_col(i).size()<=game.row_nbr()) break;
		if(i==game.col_nbr() && game.get_col(i).size()==game.row_nbr()+1) {cout<<"Tie"<<endl;return true;}
	}	

	return false;
}


void PLAY::start_game(){
	srand((unsigned)time(NULL));
	int t1,t2;

	while(1){
	//player 1's turn
		if(nbr_p>0) {cout<<"Please input number from 1 to 6"<<endl; cin>>t1;}
		else {t1=smart_dec(player1);}
		while(!add_token(player1,t1)){
			t1=smart_dec(player1);
			if(nbr_p>0) {cout<<"Please input number from 1 to 6"<<endl; cin>>t1;}
		}
		game.print();
		if(judge_winner(player1,t1)) break;

		cout<<endl;

	//player 2's turn
		if(nbr_p>1) {cout<<"Please input number from 1 to 6"<<endl; cin>>t2;}
		else {t2=smart_dec(player2);}
		while(!add_token(player2,t2)){
			t2=smart_dec(player2);
			if(nbr_p>1) {cout<<"Please input number from 1 to 6"<<endl; cin>>t2;}
		}
		game.print();
		if(judge_winner(player2,t2)) break;
	
		cout<<endl;
	}
}

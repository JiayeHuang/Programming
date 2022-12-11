#include "grid.h"

using namespace std;

grid::grid(){ //add the index line at the bottom of the grid
	for(int i=0;i<ncols;++i){vec[i].push_back(i+1);}
}

grid::~grid(){}

//get the nth column of the grid
vector<int> grid::get_col(int col)const{return vec[col-1];}

int grid::row_nbr()const{return nrows;}
int grid::col_nbr()const{return ncols;}

//add/delete in nth column
vector<int> grid::add_char(int player,int col){vec[col-1].push_back(player); return vec[col-1];}
vector<int> grid::del_char(int col){vec[col-1].pop_back();return vec[col-1];}

//count the token number in continuous order
int grid::horizon(int player,int col){
	int row=vec[col-1].size()-1;
	int l=col-2,r=col,left=l,right=r;

	while(l>=0||r<ncols){
		if(l>=0){
		if(vec[l].size()>row){
			if(vec[l][row]==player){//move the left count to the left, if value matches
				--l;
				if(l==-1) left=l; //set value for final calculation if l is moving out of range
			}
			else{left=l;l=-1;}
		}
		else{left=l;l=-1;} //set the value if l is moving to an empty field
		}

		if(r<ncols){
		if(vec[r].size()>row){
			if(vec[r][row]==player){//move the right count to the right, if the value matches
				++r;
				if(r==ncols) right=r; //set value for final calculation if r is moving out of range
			}
			else{right=r;r=ncols;}
		}
		else{right=r;r=ncols;}  //set the value if l is moving to an empty field
		}
	}

	return right-left-1;
}

int grid::vertical(int player,int col){
	int row=vec[col-1].size()-1;
	int b=row-1;  //row 0 is index, not token

	while(b>0){ //moving the count lower until the value doesn't match
		if(vec[col-1][b]==player)--b;
		else break;
	}

	return row-b;
}

int grid::diag_lb_rt(int player,int col){
	int row=vec[col-1].size()-1;
	int u=row+1,b=row-1,l=col-2,r=col,left=l,right=r; //set initial value

	while((l>=0 && b>0)||(r<ncols && u<=nrows)){
		if(l>=0 && b>0){
		if(vec[l].size()>b){
			if(vec[l][b]==player){ //move the count to left lower side till the value doesn't match
				--l;--b;
				if(l==-1 || b==0) left=l;
			}
			else{left=l;l=-1;}
		}
		else{left=l;l=-1;} //set the value when l move to an empty side
		}

		if(r<ncols && u<=nrows){
		if(vec[r].size()>u){
			if(vec[r][u]==player){//move the count to right upper side till the value doesn't match
				++r;++u;
				if(r==ncols || u>nrows) right=r;
			}
			else{right=r;r=ncols;}
		}
		else{right=r;r=ncols;} //set the value when r move to an empty side
		}
	}

	return right-left-1;
}

int grid::diag_lt_rb(int player,int col){
	int row=vec[col-1].size()-1;
	int u=row+1,b=row-1,l=col-2,r=col,left=l,right=r; //set initial value

	while((l>=0 && u<=nrows)||(r<ncols && b>0)){
		if(l>=0 && u<=nrows){
		if(vec[l].size()>u){
			if(vec[l][u]==player){//move the count to left upper side till the value doesn't match
				--l;++u;
				if(l==-1 || u>nrows) left=l;
			}
			else{left=l;l=-1;}
		}
		else{left=l;l=-1;}//set the value when l move to an empty side
		}

		if(r<ncols && b>0){
		if(vec[r].size()>b){
			if(vec[r][b]==player){//move the count to right lower side till the value doesn't match
				++r;--b;
				if(r==ncols || b==0) right=r;
			}
			else{right=r;r=ncols;}
		}
		else{right=r;r=ncols;}//set the value when r move to an empty side
		}
	}

	return right -left-1;
}


void grid::print(){
	for(int i=nrows;i>0;--i){ //print different rows
		for(int j=0;j<ncols;++j){ //print column in the same row
			if(i<vec[j].size()){//output different character for player 1 and player 2
				if(vec[j][i]==1) cout<<"O ";
				else cout<<"X ";
			}
			else cout<<"  "; //output blank if no values in the cell yet
		}
		cout<<endl;
	}

	for(int j=0;j<ncols;++j){cout<<vec[j][0]<<" ";} //output the column number for player convenience
	cout<<endl;
}

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class grid{
private:
	int nrows=6;
	int ncols=7;
	vector<vector<int>> vec=vector<vector<int>>(ncols);
public:
	//constructor
	grid();

	//destructor
	~grid();

	//get the nth column of the grid
	vector<int> get_col(int col)const;

	//get row number
	int row_nbr()const;

	//get column number
	int col_nbr()const;

	//add/delete in nth column
	vector<int> add_char(int player,int col);
	vector<int> del_char(int col);

	//count the token number in continuous order
	int horizon(int player,int col);
	int vertical(int player,int col);
	int diag_lb_rt(int player,int col);
	int diag_lt_rb(int player,int col);

	void print();
};

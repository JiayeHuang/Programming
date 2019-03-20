#include <iostream>

using namespace std;

class Matrix {

private:
	int nrows;
	int ncols;
	double **elem;

public:
	//constructor
	Matrix(int r,int c);

	//deep copy constructor
	Matrix(const Matrix& mat_in);

	//deep assignment operator
	Matrix& operator=(const Matrix& mat_in);

	//destructor
	~Matrix();

	void set(const int i_row,const int j_col,double x);

	double get(const int i_row,const int j_col);

	int row();
	int col();

	double& operator()(const int i_row,const int j_col);
	Matrix& operator+=(Matrix mat_a);
	Matrix& operator-=(Matrix mat_a);

	void print();
};

//arithmetic operators
Matrix operator+(Matrix mat_a,Matrix mat_b);
Matrix operator-(Matrix mat_a,Matrix mat_b);

int operator!=(Matrix mat_a,Matrix mat_b);
int operator==(Matrix mat_a,Matrix mat_b);

//function for matrix calculation
Matrix transpose(Matrix mat_a);
Matrix multiply(Matrix mat_a,Matrix mat_b);

//output
std::ostream& operator<<(std::ostream &os,Matrix& mat_in);

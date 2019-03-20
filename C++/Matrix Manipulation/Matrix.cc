#include "Matrix.h"

//constructor
Matrix::Matrix(int r,int c):nrows{r},ncols{c}{

    elem=new double*[nrows];

    for(int i=0;i<nrows;i++){
	elem[i]=new double[ncols];

	//Initialize the value
	for(int j=0;j<ncols;j++){elem[i][j]=i+j;}

    }
}

//deep copy constructor
Matrix::Matrix(const Matrix& mat_in):nrows(mat_in.nrows),ncols(mat_in.ncols){
    if(mat_in.elem!=0) {
	elem=new double*[nrows];

	for(int i=0;i<nrows;i++){
	    elem[i]=new double[ncols];
	    for(int j=0;j<ncols;j++){
		elem[i][j]=mat_in.elem[i][j];
	    }
	}
    }
    else{elem=0;}
}

//deep assignment operater
Matrix& Matrix::operator=(const Matrix& mat_in){
    if(this == &mat_in){return *this;}

    double **p=new double*[mat_in.nrows];
    for(int i=0;i<mat_in.nrows;i++){
	p[i]=new double[mat_in.ncols];//allocate the memory
	std::copy(mat_in.elem[i],mat_in.elem[i]+mat_in.ncols,p[i]); //do the copy
    }
    
    for(int i=0;i<(this->nrows);i++){delete[] this->elem[i];}
    delete[] this->elem;

    elem=p;
    for(int i=0;i<mat_in.nrows;i++){elem[i]=p[i];}
    nrows=mat_in.nrows;
    ncols=mat_in.ncols;

    return *this;
}

//destructor
Matrix::~Matrix(){
    for(int i=0;i<nrows;i++){delete[] elem[i];}
    delete[] elem;
}



//change the element in the ith row,jth column
void Matrix::set(const int i_row,const int j_col,double x){
    if(i_row>=(this->nrows)||j_col>=(this->ncols)){
	cerr<<"error!"<<endl;exit(1);
    }
    elem[i_row][j_col]=x;
}

//get the element in the ith row,jth column
double Matrix::get(const int i_row,const int j_col){
    if(i_row>=(this->nrows)||j_col>=(this->ncols)){
	cerr<<"error!"<<endl;exit(1);
    }
    return elem[i_row][j_col];
}

double& Matrix::operator()(const int i_row,const int j_col){
    if(i_row>=(this->nrows)||j_col>=(this->ncols)){
	cerr<<"error!"<<endl;exit(1);
    }
    return elem[i_row][j_col];
}

//get the row and column number of the matrix
int Matrix::row(){return nrows;}
int Matrix::col(){return ncols;}




//do some calculation
Matrix operator+(Matrix mat_a,Matrix mat_b){//judge if caculable
    if((mat_a.row()!=mat_b.row())||(mat_a.col()!=mat_b.col())){cerr<<"matrix mismatch"<<endl;exit(1);}

    Matrix mat_c(mat_a.row(),mat_a.col());//create matrix to load the result of the caculation

    for(int i=0;i<mat_a.row();i++){
	for(int j=0;j<mat_a.col();j++){
	    mat_c.set(i,j,mat_a(i,j)+mat_b(i,j));
	}
    }
    return mat_c;
}

Matrix operator-(Matrix mat_a,Matrix mat_b){//judge if caculable
    if((mat_a.row()!=mat_b.row())||(mat_a.col()!=mat_b.col())){cerr<<"matrix mismatch"<<endl;exit(1);}

    Matrix mat_c(mat_a.row(),mat_a.col());//create matrix to load the result of the caculation

    for(int i=0;i<mat_a.row();i++){
	for(int j=0;j<mat_a.col();j++){
	    mat_c.set(i,j,mat_a(i,j)-mat_b(i,j));
	}
    }
    return mat_c;
}

int operator==(Matrix mat_a,Matrix mat_b){

    int equals=1;

    if((mat_a.row()!=mat_b.row())||(mat_a.col()!=mat_b.col())){equals=0;}

    for(int i=0;i<mat_a.row();i++){
	for(int j=0;j<mat_a.col();j++){
	    if(mat_a.get(i,j)!=mat_b.get(i,j)){equals=0;break;}
	}
    }
    return equals;
}

int operator!=(Matrix mat_a,Matrix mat_b){
 
    int non_equals=0;

    if((mat_a.row()!=mat_b.row())||(mat_a.col()!=mat_b.col())){non_equals=1;}

    for(int i=0;i<mat_a.row();i++){
	for(int j=0;j<mat_a.col();j++){
	    if(mat_a.get(i,j)!=mat_b.get(i,j)){non_equals=1;break;}
	}
    }
    return non_equals;
}

Matrix& Matrix::operator+=(Matrix mat_a){//judge if it is calculable
    if(((this->nrows)!=mat_a.row())||((this->ncols)!=mat_a.col())){cerr<<"matrix dismatch"<<endl;exit(1);}

    for(int i=0;i<mat_a.row();i++){
	for(int j=0;j<mat_a.col();j++){
	    this->elem[i][j]=this->elem[i][j]+mat_a.get(i,j);
	}
    }

    return *this;
}

Matrix& Matrix::operator-=(Matrix mat_a){//judge if it is calculable
    if(((this->nrows)!=mat_a.row())||((this->ncols)!=mat_a.col())){cerr<<"matrix dismatch"<<endl;exit(1);}

    for(int i=0;i<mat_a.row();i++){
	for(int j=0;j<mat_a.col();j++){
	    this->elem[i][j]=this->elem[i][j]-mat_a.get(i,j);
	}
    }

    return *this;
}

Matrix transpose(Matrix mat_a){
    Matrix mat_b(mat_a.col(),mat_a.row());

    for(int i=0;i<mat_a.row();i++){
	for(int j=0;j<mat_a.col();j++){
	    mat_b.set(j,i,mat_a(i,j));
	}
    }

    return mat_b;
}

Matrix multiply(Matrix mat_a,Matrix mat_b){
    if(mat_a.col()!=mat_b.row()){cerr<<"matrix mismatch"<<endl;exit(1);}

    Matrix mat_c(mat_a.row(),mat_b.col());

    for(int i=0;i<mat_c.row();i++){
	for(int j=0;j<mat_c.col();j++){
	    mat_c(i,j)=0;
	    for(int m=0;m<mat_a.col();m++){
		mat_c(i,j)+=mat_a(i,m)*mat_b(m,j);
	    }
	}
    }

    return mat_c;
}

//output
void Matrix::print(){
    for(int i=0;i<nrows;i++){
	for(int j=0;j<ncols;j++){
	    std::cout<<elem[i][j]<<" ";
	}
	std::cout<<endl;
    }
}

//output to string
std::ostream& operator<<(std::ostream &os,Matrix& mat_in){
    for(int i=0;i<mat_in.row();i++){
	for(int j=0;j<mat_in.col();j++){
	    os<<mat_in(i,j)<<" ";
	}
	os<<std::endl;
    }
    return os;
}

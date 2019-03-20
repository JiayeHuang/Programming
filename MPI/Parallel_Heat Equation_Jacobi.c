#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mpi.h"

#define maxn 500
#define maxit 10000

int getxy(int nx,int ny,int xind,int yind,double *x,double *y);
int gethxy(int nx,int ny,double *hx,double *hy);
double fzero(int xind,int yind,int nx,int ny);
double fone(int xind,int yind,int nx,int ny);
double fisherles1(int xind,int yind,int nx,int ny);
double fisherles2(int xind,int yind,int nx,int ny);
double fisherles3(int xind,int yind,int nx,int ny);
double fisherlessoln(int xind,int yind,int nx,int ny);

void sweep(double a[][maxn],double f[][maxn],int ny,int xs,int xe,int ys,int ye,double b[][maxn]);
double griddiff(double a[][maxn],double b[][maxn],int xs,int xe,int ys,int ye);

int main(int argc,char *argv[])
{
	double a[maxn][maxn],b[maxn][maxn],f[maxn][maxn];
	int nx,ny;
	int myid,nprocs;
	int nbrleft,nbrright,nbrup,nbrdown;
	int xs,xe,ys,ye;
	double ldiff,gdiff;
	double tol=1.0E-07;
	int i,j,k,it;
	MPI_Datatype stridedcol,stridedrow;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Comm_size(MPI_COMM_WORLD,&nprocs);

	if(nprocs%2!=0){
		if(myid==0){
		printf("Please input even number of processes.\n");
		fflush(stdout);
		}
		MPI_Abort(MPI_COMM_WORLD,1);
	}

	nx=7;
	ny=nx;
  
      /*Initialize the full grid*/
  
	for(i=0;i<maxn;i++){
		for(j=0;j<maxn;j++){
		    a[i][j]=-1;
		    b[i][j]=-1;
		    f[i][j]=-1;
		}
	}

    /*Seperate the grid for each processor*/  
	int len,elen;
	int ns,nl;

	len=(int)nx/(nprocs/2);elen=len+1;
	nl=nx-len*(nprocs/2);ns=(nprocs/2)-nl;
	if((int)myid/2<nl){xs=(int)myid/2*elen+1;xe=(int)myid/2*elen+elen;}
	else{xs=nl*elen+((int)myid/2-nl)*len+1;xe=nl*elen+((int)myid/2-nl)*len+len;}
                                                                         
	if(myid%2==0){ys=1;ye=(int)(ny/2);}
	else{ys=(int)(ny/2)+1;ye=ny;}

	printf("(Rank: %d),x range:(%d,%d),y range:(%d,%d)\n",myid,xs,xe,ys,ye);	

    /*Use Cartesian topology to distribute the processes*/
	int ndims;
	int dims[2];
	int periods[2];
	int coord[2];
	int recorder;
	MPI_Comm cartcomm;

	ndims=2;
	dims[0]=nprocs/2;dims[1]=2;
	periods[0]=0;periods[1]=0;
	recorder=0;

	MPI_Cart_create(MPI_COMM_WORLD,ndims,dims,periods,recorder,&cartcomm);
	MPI_Cart_coords(cartcomm,myid,2,coord);
	MPI_Cart_shift(cartcomm,1,-1,&nbrup,&nbrdown);
	MPI_Cart_shift(cartcomm,0,1,&nbrleft,&nbrright);
	printf("(Rank %d),coords=%d %d,neighbours(u,d,l,r)=%d %d %d %d\n",myid,coord[0],coord[1],nbrup,nbrdown,nbrleft,nbrright);
	MPI_Barrier(MPI_COMM_WORLD);

    /*Initialize the value in each process*/
	for(i=xs-1;i<=xe+1;i++){
		for(j=ys-1;j<=ye+1;j++){
			a[i][j]=0;
			b[i][j]=0;
			f[i][j]=0;
		}
	}
    //The left bound
	if(xs==1){
		for(j=ys;j<ye+1;j++){
			a[0][j]=fone(0,j,nx,ny);
			b[0][j]=fone(0,j,nx,ny);
		}
	}
    //The right bound
	if(xe==nx){
		for(j=ys;j<ye+1;j++){
			a[nx+1][j]=fone(0,j,nx,ny);
			b[nx+1][j]=fone(0,j,nx,ny);
		}
	}
    //The lower bound
	if(ys==1){
		for(i=xs;i<xe+1;i++){
			a[i][0]=fone(i,0,nx,ny);
			b[i][0]=fone(i,0,nx,ny);
		}
	}
    //The upper bound
	if(ye==ny){
		for(i=xs;i<xe+1;i++){
			a[i][ny+1]=fone(i,0,nx,ny);
			b[i][ny+1]=fone(i,0,nx,ny);
		}
	}

    /*Start the iteration for heat equation*/
                                         
	MPI_Type_vector(xe-xs+1,1,maxn,MPI_DOUBLE,&stridedcol);
	MPI_Type_vector(ye-ys+1,1,1,MPI_DOUBLE,&stridedrow);
	MPI_Type_commit(&stridedcol);
	MPI_Type_commit(&stridedrow);

	for(it=0;it<maxit;it++){
		MPI_Sendrecv(&a[xe][ys],1,stridedrow,nbrright,0,&a[xs-1][ys],1,stridedrow,nbrleft,0,cartcomm,MPI_STATUS_IGNORE);
		MPI_Sendrecv(&a[xs][ys],1,stridedrow,nbrleft,1,&a[xe+1][ys],1,stridedrow,nbrright,1,cartcomm,MPI_STATUS_IGNORE);
		MPI_Sendrecv(&a[xs][ye],1,stridedcol,nbrup,0,&a[xs][ys-1],1,stridedcol,nbrdown,0,cartcomm,MPI_STATUS_IGNORE);
		MPI_Sendrecv(&a[xs][ys],1,stridedcol,nbrdown,1,&a[xs][ye+1],1,stridedcol,nbrup,1,cartcomm,MPI_STATUS_IGNORE);
		sweep(a,f,ny,xs,xe,ys,ye,b);

		MPI_Sendrecv(&b[xe][ys],1,stridedrow,nbrright,0,&b[xs-1][ys],1,stridedrow,nbrleft,0,cartcomm,MPI_STATUS_IGNORE);
		MPI_Sendrecv(&b[xs][ys],1,stridedrow,nbrleft,1,&b[xe+1][ys],1,stridedrow,nbrright,1,cartcomm,MPI_STATUS_IGNORE);
		MPI_Sendrecv(&b[xs][ye],1,stridedcol,nbrup,0,&b[xs][ys-1],1,stridedcol,nbrdown,0,cartcomm,MPI_STATUS_IGNORE);
		MPI_Sendrecv(&b[xs][ys],1,stridedcol,nbrdown,1,&b[xs][ye+1],1,stridedcol,nbrup,1,cartcomm,MPI_STATUS_IGNORE);
		sweep(b,f,ny,xs,xe,ys,ye,a);
                                           
		ldiff=griddiff(a,b,xs,xe,ys,ye);
		MPI_Allreduce(&ldiff,&gdiff,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);

		if(gdiff<tol){
			if(myid==0){
			printf("The heat equation converges in %d iterations.\n",it);
			}
			break;
		}
	}

	MPI_Type_free(&stridedcol);
	MPI_Type_free(&stridedrow);
	MPI_Barrier(MPI_COMM_WORLD);

    /*Print out the result*/
	for(k=0;k<nprocs;k++){
		if(myid==k){
			printf("Rank: %d\n",myid);
			for(j=ye+1;j>=ys-1;j--){
				for(i=xs-1;i<=xe+1;i++){
					printf("%lf ",a[i][j]);
				}
				printf("\n");
			}
		}
	}

	MPI_Finalize();
	return 0;
}

void sweep(double a[][maxn],double f[][maxn],int ny,int xs,int xe,int ys,int ye,double b[][maxn])
{
	double h;
	int m,n;

	h=1.0/(double)(ny+1);

	for(m=xs;m<=xe;m++){
		for(n=ys;n<ye+1;n++){
			b[m][n]=0.25*(a[m-1][n]+a[m+1][n]+a[m][n-1]+a[m][n+1]-h*h*f[m][n]);
		}
	}
}

double griddiff(double a[][maxn],double b[][maxn],int xs,int xe,int ys,int ye)
{
	double sum;
	double tmp;
	int m,n;

	sum=0;

	for(m=xs;m<=xe;m++){
		for(n=ys;n<ye+1;n++){
			tmp=a[m][n]-b[m][n];
			sum=sum+tmp*tmp;
		}
	}
	return sum;
}

double fzero(int xind,int yind,int nx,int ny)
{
	return 0;
}

double fone(int xind,int yind,int nx,int ny)
{
	return 1;
}

double fisherles1(int xind,int yind,int nx,int ny)
{
	double x,y;
	double tmpv;
	
	getxy(nx,ny,xind,yind,&x,&y);

	tmpv=(1+x)*(1+x)+1;
	return 1/tmpv;
}

double fisherles2(int xind,int yind,int nx,int ny)
{
	double x,y;
	double tmpv;

	getxy(nx,ny,xind,yind,&x,&y);

	tmpv=1+y*y;
	return y/tmpv;
}

double fisherles3(int xind,int yind,int nx,int ny)
{
	double x,y;
	double tmpv;

	getxy(nx,ny,xind,yind,&x,&y);

	tmpv=4+y*y;
	return y/tmpv;
}

double fisherlessoln(int xind,int yind,int nx,int ny)
{
	double x,y;
	double tmpv;

	getxy(nx,ny,xind,yind,&x,&y);

	tmpv=(1+x)*(1+x)+y*y;
	return y/tmpv;
}

int getxy(int nx,int ny,int xind,int yind,double *x,double *y)
{
	double hx,hy;
	double lx,ly;

	gethxy(nx,ny,&hx,&hy);

	lx=xind*hx;
	ly=yind*hy;

	*x=lx;
	*y=ly;

	return 0;
}

int gethxy(int nx,int ny,double *hx,double *hy)
{
	*hx=1/((double)(nx+1));
	*hy=1/((double)(ny+1));

	return 0;
}

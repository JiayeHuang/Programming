#include <iostream>

using namespace std;

double pow(double x,int n)
{
	double p=1;
	int i=0;

	for(i=0;i<n;++i){p=p*x;} //calculate x^n

	return p;
}

long long fac(int n)
{
	long long f=1;

	if(n>1){f=n*fac(n-1);}  //recursive function, calculate n!

	return f;
}

double exp(double x)
{
	double e=1.0;
	int n=1;

//when 0<=x<=0.5
	if((x>=0)&&(x<=0.5)){
		while(pow(x,n)/fac(n)>=1.0e-5){
			e=e+pow(x,n)/fac(n);
			++n;
		}
	}

//when 0.5<x<<50
	else if((x>0.5)&&(x<=50)){
		e=exp(x/2)*exp(x/2); //recursive function, as e^x=e^(x/2)*e^(x/2)
	}

//when -50<=x<0
	else if((x>=-50)&&(x<0)){
		e=1/exp(-x); //e^(-x)=1/(e^x)
	}

//Send warning message when x is too large or too small
	else{cout<<"Please input x between -50 and 50."<<endl;exit(1);}

	return e;
}

int main()
{
	cout<<"exp(0)="<<exp(0)<<endl;
	cout<<"exp(0.4)="<<exp(0.4)<<endl;
	cout<<"exp(29)="<<exp(29)<<endl;
	cout<<"exp(-0.4)="<<exp(-0.4)<<endl;
	cout<<"exp(-17)="<<exp(-17)<<endl;
	cout<<"exp(102)="<<exp(102)<<endl;

	return 0;
}

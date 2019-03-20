#include "Matrix.h"

using namespace std;

int main()
{
    cout<<"Matrix m1"<<endl;
    Matrix m1(2,3);
    m1.set(0,2,6.9);
    m1.set(1,2,4.8);
    m1.print();
    
    cout<<"Matrix m2: Transpose of m1"<<endl;
    Matrix m2(3,2);
    m2=transpose(m1);
    cout<<m2;

    cout<<"Matrix m3: m1*m2"<<endl;
    Matrix m3(6,2);
    m3=multiply(m1,m2);
    cout<<m3;

    cout<<"Matrix m4: m4+=m3"<<endl;
    Matrix m4(2,2);
    m4+=m3;
    cout<<m4;

    cout<<"Matrix m5:m3+m4"<<endl;
    Matrix m5(3,4);
    m5=m3+m4;
    cout<<m5;

    if(m3==m4){cout<<"Matrix m3 equals m4"<<endl;}
    else{cout<<"Matrix m3 doesn't equal to m4"<<endl;}
}

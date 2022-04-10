// 3053.cpp
#include<iostream>
#include<cmath>
using namespace std;
/* pi * pow(r,2), (1,1) (0,0) */
int main(){
    int i;
    double pi = M_PI,k;
    cin >> i;

    k = pow(i,2)+pow(i,2);

    printf("%.6f \n%.6f",pi*pow(i,2), k);
    cout <<"\n";

}
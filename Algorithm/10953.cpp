#include <iostream>
#include <cstdio>
using namespace std;

int main(){
    int Testcase, a,b;
    scanf("%d",&Testcase);
    while(Testcase--){
        scanf("%d,%d",&a,&b);
        printf("%d\n",a+b);
    }
}
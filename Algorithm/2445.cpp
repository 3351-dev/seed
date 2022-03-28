// 2445.cpp
#include <iostream>
using namespace std;
int main(){
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            printf("*");
        }
        for(int j=2*n;j>2*i+2;j--){
            printf(" ");
        }
        for(int j=0;j<=i;j++){
            printf("*");
        }
        printf("\n");
    }
    for(int i=0;i<n-1;i++){
        for(int j=n;j>i+1;j--){
            printf("*");
        }
        for(int j=0;j<2*i+2;j++){
            printf(" ");
        }
        for(int j=n;j>i+1;j--){
            printf("*");
        }
        printf("\n");
    }
}
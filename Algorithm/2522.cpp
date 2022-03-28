// 2522.cpp
#include <iostream>
using namespace std;
int main(){
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=n;j>i+1;j--){
            printf(" ");
        }
        for(int j=0;j<i+1;j++){
            printf("*");
        }
        printf("\n");
    }
    for(int i=1;i<n;i++){
        for(int j=0;j<i;j++){
            printf(" ");
        }
        for(int j=n;j>i;j--){
            printf("*");
        }
        printf("\n");
    }
}
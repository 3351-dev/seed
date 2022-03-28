// 2442.cpp
#include <iostream>
using namespace std;
//  별이 찍힌 후에는 공백이 만들어지지 않도록.
int main(){
    int N;
    cin >> N;
    for(int i=0;i<N;i++){
        // for(int j=N;j>0;j--){
        //     if(i<j-1) printf(" ");
        //     else printf("*");
        // }
        // for(int j=0;j<N;j++){
        //     if(i<j+1) printf(" ");
        //     else printf("*");
        // }
        for(int j=0;j<N-i-1;j++){
            printf(" ");
        }
        for(int j=0;j<2*i+1; j++){
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
// 2447.cpp
#include<iostream>
using namespace std;
/* 
    N은 3 9 27 ... pow(3,n)
    N * N 정사각형 모형
 */

void star(int i, int j,int n){
    // 대충 if문잡는곳
    // 프린트 하는곳 >> 2개로 나눔 '*', ' ' (별, 공백)
    if((i/n)%3 ==1 && (j/n)%3==1) cout << " ";
    else{
        if(n/3 ==0) cout <<"*";
        else star(i,j,n/3);
    }

}

int main(){
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            star(i,j,n);
        }
        cout <<"\n";
    }
}
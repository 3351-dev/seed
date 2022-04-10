// 10872.cpp

#include<iostream>
using namespace std;

// 조건을 어떻게 주느냐에 따라 시간초과가 나올수도있다;; 
int factorial(int n){
    if(n>1) return n * factorial(n-1);
    else return 1;
}

int main(){
    int n;
    cin >> n;
    cout << factorial(n) <<"\n";
}
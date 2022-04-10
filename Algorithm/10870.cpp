// 10870.cpp

#include<iostream>
using namespace std;

int fibonacci(int n){
    if(n>1) return fibonacci(n-1) + fibonacci(n-2);
    else if(n == 1) return 1;
    else return 0;
}

int main(){
    int n;
    cin >> n;
    cout << fibonacci(n) <<"\n";
}
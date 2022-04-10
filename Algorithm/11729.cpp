// 11729.cpp
#include<iostream>
using namespace std;
/* 
    1 3
    1 2
    3 2
    1 3
    2 1
    2 3
    1 3
 */

void hanoi(int n, int start, int end, int pass){
    if(n == 1){
        cout << start << " " << end <<"\n";
    }else{
        hanoi(n-1,start, pass, end);
        cout << start << " " << end <<"\n";
        hanoi(n-1, pass, end, start);
    }
}

int main(){
    int n;
    cin >> n;
    cout << (1<<n) -1 <<"\n";
    hanoi(n,1,3,2);
}
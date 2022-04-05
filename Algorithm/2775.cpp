// 2775.cpp
#include <iostream>
using namespace std;

int getNum(int k,int n){
    if(n==1) return 1;
    if(k==0) return n;
    return (getNum(k-1,n)+getNum(k,n-1));
}

int main(){
    int t,n, k;
    cin >> t;
    for(int x = 0; x<t; x++){
        cin >> k >> n;
        cout << getNum(k,n) << "\n";
    }
}
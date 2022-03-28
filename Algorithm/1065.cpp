// 1065.cpp
#include <iostream>
using namespace std;

int sol(int n){
    if(n<100)
        return true;
    int a,b,c;
    a = n%10;       // 1의 자리 수
    b = n%100/10;   // 10의 자리수
    c = n/100;      // 100의 자리 수
    if(c-b==b-a) return true;

    return false;

}

int main(){
    int n, cnt=0;
    cin >> n;
    for(int i=1;i<n+1;i++){
        if(sol(i)) cnt++;
    }
    cout << cnt<<"\n";
}
// 8393.cpp
#include <iostream>
using namespace std;
int main(){
    int N, sum=0;
    cin >> N;
    for(int i=1;i<N+1;i++){
        sum += i;
    }
    cout << sum << "\n";
}
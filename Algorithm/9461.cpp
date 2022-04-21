// 9461.cpp

#include<iostream>

using namespace std;

long long arr[101] = {1,1,1,};

long long solution(int n){
    if(n<3) return arr[n];
    else if(arr[n] == 0){
        arr[n] = solution(n-2) + solution(n-3);
    }
    return arr[n];
}

int main(){
    int n,k;
    cin >> n;

    for(int i=0;i<n;i++){
        cin >> k;
        cout << solution(k-1) <<"\n";
    }
}
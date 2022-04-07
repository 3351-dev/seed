// 1929.cpp

#include<iostream>
#include<cmath>
using namespace std;

void prime(int n, int m, int arr[]){
    for(int i=0; i<m+1; i++){
        arr[i] = i;
    }
    for(int i=2; i<sqrt(m+1); i++){
        if(arr[i]==0) continue;
        
        for(int j=i*i; j<m+1; j+=i){
            arr[j] = 0;
        }
    }
// n이상 m 이하니까 m+1이지 ㅡㅡ
    for(int i=n;i<m+1;i++){
        if(arr[i] == 1) continue;
        if(arr[i] != 0) cout << arr[i] <<"\n";
    }
}

int main(){
    int n,m;
    int cnt = 0;
    cin >> n >> m;
    int arr[m];

    prime(n,m,arr);
}
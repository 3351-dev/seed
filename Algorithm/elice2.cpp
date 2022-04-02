// elice2.cpp

#include<iostream>
using namespace std;
int gcd(int a,int b){
    int n;
    while(b!=0){
        n=a%b;
        if(n==0) return b;
        a=b;
        b=n;
    }
    return a;
}

int main(){
    int N, C, cnt=0, mixmatch;
    cin >> N >> C;
    int arr[N];
    
    for(int i=0;i<N;i++){
        cin >> arr[i];
    }

    mixmatch = gcd(arr[0],arr[1]);
    cout << mixmatch <<"\n";

    for(int i=0;i<N;i++){
        cnt += C/arr[i];
    }

    cout << cnt <<"\n";




}
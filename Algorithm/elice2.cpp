// elice2.cpp

#include<iostream>
using namespace std;
// 최대 공약수
int getGcd(int a,int b){
    int n;
    while(b!=0){
        n=a%b;
        a=b;
        b=n;
    }
    return a;
}
// 최소 공배수
int getLcm(int a,int b){
    return a*b/getGcd(a,b);
}

int main(){
    int N, C, cnt=0;
    int gcd,lcm;
    cin >> N >> C;
    int arr[N];
    
    for(int i=0;i<N;i++){
        cin >> arr[i];
    }
    gcd = lcm = 1;

    // 최대 공약수 최소 공배수
    for(int i=0;i<N;i++){
        gcd = getGcd(gcd,arr[i]);
        lcm = getLcm(lcm, arr[i]);
    }

    for(int i=0;i<N;i++){
        cnt += C/arr[i];
    }
    cnt -= C/lcm;

    cout << cnt <<"\n";
}
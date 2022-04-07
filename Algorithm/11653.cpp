// 11653.cpp

#include<iostream>
using namespace std;
int main(){
    int n;
    cin >> n;

    if(n==1) return 0;
    for(int i=2;i<n+1;i++){
        while(n%i==0){
            cout << i <<"\n";
            n /= i;
            // cout <<" " << n <<"\n";
        }
    }

}

// 1978.cpp
#include<iostream>
using namespace std;

int main(){
    int n,a, cnt, sum=0;
    cin >> n;
    for(int i=0;i<n;i++){
        cnt = 0;
        cin >> a;
        if(a==1) continue;
        for(int j=1;j<a+1;j++){
            if(a % j == 0) cnt++;
        }
        if(cnt == 2) sum++;
    }
    cout << sum << "\n";
}
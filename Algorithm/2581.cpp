// 2581.cpp
#include <iostream>
using namespace std;

int main(){
    int m,n,cnt,sum=0,min=10000;
    cin >> m >> n;

    for(int i=m;i<n+1;i++){
        cnt = 0;
        if(i==1) continue;
        for(int j=1;j<i+1;j++){
            if(i%j==0) cnt++;
        }
        if(cnt==2) {
            sum+=i;
            if(min>i) min = i;
        }
    }
    if(sum==0) cout << "-1" <<"\n";
    else cout << sum << "\n" << min <<"\n";
}

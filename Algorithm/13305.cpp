// 13305.cpp

#include <iostream>

using namespace std;

long long dist[100001];
long long city[100001];

int main(){
    int n,ans =0;
    cin >> n;

    for(int i=0;i<n-1;i++){
        cin >> dist[i];
    }
    for(int i=0;i<n;i++){
        cin >> city[i];
    }
    
    int max = 1000000000;

    // for(int i=0;i<n;i++){
    //     if(i<n-1) cout << "dist : " << dist[i]<<"\n";
    //     cout << "city : " << city[i]<<"\n";
    // }

    for(int i=0;i<n-1;i++){
        if(city[i]<max) max=city[i];
        ans += max * dist[i];
        // cout << i << " : " << ans <<"\n";
    }

    cout << ans <<"\n";


}
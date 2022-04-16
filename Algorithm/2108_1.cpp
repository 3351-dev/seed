// 2108.cpp

#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<time.h>

using namespace std;

int main(){
    long n,temp;
    vector<long> arr,ans;
    int num[8001] ={0,};
    
    cin >> n;

    for(int i=0;i<n;i++){
        cin >> temp;
        arr.push_back(temp);
        ans.push_back(0);
        num 
    }
    temp = 0;

    sort(arr.begin(), arr.end());

    for(int i=0;i<n;i++){
        temp += arr[i];
    }
    ans[0] = round((float)temp/n);
    ans[1] = arr[n/2];
    int freq=0, checker =0;
    ans[3] = arr[n-1] - arr[0];

    // calc freq
    for(int i=0;i<8001;i++){
        if()
    }

    for(int i=0;i<4;i++){
        cout << ans[i] << "\n";
    }
}
// 2565.cpp

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int dp[102];
int main(){
    int n, ans=0;
    vector<pair<int, int> > arr;
    pair<int, int> temp;
    
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> temp.first >> temp.second;
        arr.push_back(temp);
    }
    sort(arr.begin(), arr.end());
    // cout << "----\n";
    // for(int i=0;i<n;i++){
    //     cout << arr[i].first << " " << arr[i].second <<"\n";
    // }

    for(int i=0;i<n;i++){
        dp[i] = 1;
        for(int j=0;j<i;j++){
            if(arr[i].second > arr[j].second){
                // dp[i] = max(dp[i], dp[j]+1);
                if(dp[i] < dp[j]+1) dp[i] = dp[j] + 1;
            }
        }
        ans = max(ans, dp[i]);
        // cout << "ans : " << ans <<"\n";
    }

    cout << n-ans <<"\n";
}
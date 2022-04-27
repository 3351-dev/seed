// 1912.cpp

#include<iostream>
#include<vector>
#include<algorithm>

#define MAX 100001

using namespace std;

int arr[MAX] ={0,};
int dp[MAX] = {0,};
// vector<int> temp;


int main(){
    int n, ans;
    cin >> n;

    for(int i=0;i<n;i++){
        cin >> arr[i];
        dp[i] = arr[i];
    }
    ans = dp[0];

    for(int i=1;i<n;i++){
        dp[i] = max(dp[i], dp[i-1]+arr[i]);
        if(dp[i] > ans) ans = dp[i];
    }

    cout << ans << "\n";

}
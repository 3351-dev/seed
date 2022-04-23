// 11053.cpp

#include<iostream>
#include<algorithm>
#include<vector>
#define MAX 1001

using namespace std;

vector<int> arr;
int dp[MAX];

int main(){
    int n, temp, ans=0, dp_height;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> temp;
        arr.push_back(temp);
        dp_height = 0;
        for(int j=0;j<arr.size();j++){
            if(arr[i] > arr[j]){
                if(dp_height < dp[j]){
                    dp_height = dp[j];
                }
            }
        }
        dp[i] = dp_height + 1;
        ans = max(ans, dp[i]);
    }

    cout << ans << "\n";
}
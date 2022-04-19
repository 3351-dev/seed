// 11054.cpp

#include<iostream>
#define MAX 1001
using namespace std;

int main(){
    int n;
    int arr[MAX];
    int dp[MAX];
    int reverse_dp[MAX];
    int ans = 0;

    cin >> n;
    
    for(int i=1;i<n+1;i++){
        cin >> arr[i];
    }

    for(int i=1;i<n+1;i++){
        dp[i] = 1;
        for(int j=0;j<i+1;j++){
            if(arr[j] < arr[i] && dp[i] < dp[j] + 1){
                dp[i] = dp[j] +1;
            }
        }
    }

    for(int i=n;i>0;i--){
        reverse_dp[i] = 1;
        for(int j=n;j+1>i;j--){
            if(arr[i] > arr[j] && reverse_dp[j] + 1 > reverse_dp[i]){
                reverse_dp[i] = reverse_dp[j] + 1;
            }
        }
    }

    for(int i=0;i<n+1;i++){
        if(ans < dp[i] + reverse_dp[i] - 1 ){
            ans = dp[i] + reverse_dp[i] -1;
        }
    }

    cout << ans <<"\n";


}
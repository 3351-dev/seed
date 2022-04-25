// 9251.cpp

#include<iostream>
#include<string>
#include<algorithm>

#define MAX 1001

using namespace std;

int dp[MAX][MAX];

int main(){
    string a,b;
    cin >> a >> b;
    int a_size = a.length(), b_size=b.length();
    for(int i=1;i<a_size+1;i++){
        for(int j=1;j<b_size+1;j++){
            if(a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] +1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    cout << dp[a_size][b_size] << "\n";
}
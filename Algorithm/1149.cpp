// 1149.cpp

#include<iostream>
#include<algorithm>
/* 
    빨강 초록 파랑 비용
    1. 1번집은 2번집과 다른색
    2. N번집은 N-1과 다른색
    i(2<= i <= N-1)집은 i-1, i+1 색
    2 <= N <= 1000
 */
using namespace std;

int arr[1001][3];

int main(){
    int n;
    int cost[3];

    cin >> n;
    arr[0][0] = 0;
    arr[0][1] = 0;
    arr[0][2] = 0;

    for(int i=1;i<n+1;i++){
        cin >> cost[0] >> cost[1] >> cost[2];
        arr[i][0] = min(arr[i-1][1], arr[i-1][2]) + cost[0];
        arr[i][1] = min(arr[i-1][0], arr[i-1][2]) + cost[1];
        arr[i][2] = min(arr[i-1][1], arr[i-1][0]) + cost[2];
    }

    cout << min(arr[n][2], min(arr[n][0], arr[n][1])) << "\n";

}
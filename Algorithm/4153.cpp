// 4153.cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#define MAX 30000
using namespace std;

/* 세 변이 주어지고, 직각 삼각형인지 확인하시오 */

int main(){
    int arr[MAX][3], arrCnt=0, ans=0;
// 입력 
    for(int i=0;i<MAX;i++){
        cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
        arrCnt++;
        if(arr[i][0]==0) break;
    }
    // string ans[MAX];
// 정렬 
    for(int i=0;i<arrCnt-1;i++){
        sort(arr[i], arr[i]+3);
    }

    for(int i=0;i<arrCnt-1;i++){
        if(pow(arr[i][0],2)+pow(arr[i][1],2) == pow(arr[i][2],2)){
            cout << "right" << "\n";
        }else{
            cout << "wrong" << "\n";
        }
    }

}
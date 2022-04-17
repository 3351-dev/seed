// 2108.cpp
/* 
    수정중!!
 */

#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<time.h>

using namespace std;

int main(){
    long n,temp;
    int most_val = 0, most = -9999;
    bool not_first=false;
    vector<long> arr,ans;
    int num[8001] ={0,};
    
    cin >> n;

    for(int i=0;i<n;i++){
        cin >> temp;
        arr.push_back(temp);
        ans.push_back(0);
    }
    temp = 0;

    sort(arr.begin(), arr.end());

    for(int i=0;i<n;i++){
        temp += arr[i];
        num[temp+4000] ++;
    }
    ans[0] = round((float)temp/n);
    ans[1] = arr[n/2];
    int freq=0, checker =0;
    ans[3] = arr[n-1] - arr[0];

    // calc freq
    for(int i=0;i<8001;i++){
        if(num[i] == 0) continue;
        if(num[i] == most){
            if(not_first){
                most_val = i - 4000;
                not_first = false;
            }
        }
        if(num[i] > most){
            most = num[i];
            most_val = i -4000;
            not_first = true;
        }
    }
    ans[2] = most_val;

    for(int i=0;i<4;i++){
        cout << ans[i] << "\n";
    }
}
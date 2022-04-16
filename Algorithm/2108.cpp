// 2108.cpp

#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int main(){
    long n,temp;
    vector<long> arr,ans;
    
    cin >> n;
    int value[n];

    for(int i=0;i<n;i++){
        cin >> temp;
        arr.push_back(temp);
        ans.push_back(0);
        value[i] = 0;
        ans[0] += temp;
    }

    sort(arr.begin(), arr.end());

    ans[0] = round((float)ans[0]/n);
    ans[1] = arr[n/2];
    int freq=0, checker =0;
    ans[3] = arr[n-1] - arr[0];
    // cout << " ans[3] : " << arr[n] << " " << arr[0] << "\n";

    // calc freq
    for(int i=0;i<n;i++){
        if(arr[i] == arr[i+1]){
            value[i]+=1;
        }
    }
    for(int i=0;i<n;i++){
        if(value[i]>freq){
            freq = value[i];
            checker = 0;
            ans[2] = arr[i];
        }
        else if(value[i] == freq && checker == 0){
            if(n==1){
                ans[2] = arr[i];
            }else{
                ans[2] = arr[i+1];
            }
            checker = 1;
            if(arr[i] == arr[i+1]) checker = 0;
        }        
    }

    // for(int i=0;i<n;i++){
    //     cout << "value : " <<value[i] <<"\n";
    // }

    for(int i=0;i<4;i++){
        cout << ans[i] << "\n";
    }
    

}
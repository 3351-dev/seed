// 11399.cpp

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    int n, temp ,ans=0;
    vector<int> arr;
    cin >> n;

    for(int i=0;i<n;i++){
        cin >> temp;
        arr.push_back(temp);
    }

    sort(arr.begin(), arr.end());

    for(int i=0;i<n;i++){
        for(int j=0;j<i+1;j++){
            ans += arr[j];
        }
    }

    cout << ans <<"\n";

}
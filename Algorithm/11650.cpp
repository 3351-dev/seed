// 11650.cpp
#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<pair<int, int> > arr;
    pair<int, int> temp;

    for(int i=0;i<n;i++){
        cin >> temp.first >> temp.second;
        arr.push_back(temp);
    }

    sort(arr.begin(), arr.end());

    for(int i=0;i<n;i++){
        cout << arr[i].first << " " << arr[i].second <<"\n";
    }

}
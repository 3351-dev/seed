// 18870.cpp

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    vector<int> arr, back;
    int n, input;

    cin >> n;

    for(int i=0;i<n;i++){
        cin >> input;
        arr.push_back(input);
        back.push_back(input);
    }

    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());

    for(int i=0;i<n;i++){
        printf("%ld ", lower_bound(arr.begin(), arr.end(), back[i]) - arr.begin());
    }
    cout << "\n";

}
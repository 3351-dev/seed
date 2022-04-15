// 10814.cpp

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool compare(pair<int, string> a, pair<int, string> b){
    return a.first < b.first;
}

int main(){
    int n;
    cin >> n;

    vector<pair<int, string> > arr;
    pair<int, string> temp;

    for(int i=0;i<n;i++){
        cin >> temp.first >> temp.second;
        arr.push_back(temp);
    }

    stable_sort(arr.begin(), arr.end(), compare);

    for(int i=0;i<n;i++){
        cout << arr[i].first << " " << arr[i].second << "\n";
    }

    return 0;

}
// 11651.cpp

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool compare(pair<int, int>a, pair<int,int>b){
    if(a.first == b.first){
        return a.first < b.first;
    }else{
        return a.second < b.second;
    }
}

int main(){
    int n;
    cin >> n;
    vector<pair<long, long> > arr;
    pair<long, long> temp;
    

    for(int i=0;i<n;i++){
        cin >> temp.first >> temp.second;
        arr.push_back(temp);
    }

    sort(arr.begin(), arr.end(), compare);

    for(int i=0;i<n;i++){
        cout << arr[i].first << " " << arr[i].second << "\n";
    }
}
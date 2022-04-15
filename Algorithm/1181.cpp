// 1181.cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool compare(string a, string b){
    int i=0;
    if(a.size() == b.size()){
        for(int i=0;i<a.size();i++){
            if(a[i] != b[i]) return a[i] < b[i];
        }
    }
    return a.size() < b.size();

}

int main(){
    int n;
    cin >> n;
    vector<string> arr;
    string temp;

    for(int i=0;i<n;i++){
        cin >> temp;
        arr.push_back(temp);
    }
    
    sort(arr.begin(), arr.end(), compare);

    for(int i=0;i<n;i++){
        if(arr[i] == arr[i+1]) continue;
        cout << arr[i] <<"\n";
    }
}
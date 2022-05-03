// 1931.cpp

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    int n, start, end;
    vector<pair<int, int> > table;
    pair<int, int> temp;

    cin >> n;

    for(int i=0;i<n;i++){
        cin >> temp.second >> temp.first;
        table.push_back(temp);
    }

    sort(table.begin(), table.end());

    // for(int i=0;i<n;i++){
    //     cout << table[i].first << " " << table[i].second <<"\n";
    // }

    int time = 0, ans =0;

    for(int i=0;i<n;i++){
        if(time <= table[i].second){
            // cout << "time : " << time << ", table[i].second : " << table[i].second << "\n";
            time = table[i].first;
            ans++;
        }
    }
    cout << ans << "\n";
}
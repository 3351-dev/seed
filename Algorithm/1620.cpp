// 1620.cpp
#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;

int n, m;
string name[100001];
map<string, int> maps;

int main(){
    cin >> n >> m;
    for(int i=1;i<n+1;i++){
        string s;
        cin >> s;
        name[i] = s;
        maps.insert(make_pair(s,i));
    }

    for(int i=1;i<m+1;i++){
        string s;
        int n;
        cin >> s;
        if(isdigit(s[0]) == true){
            n = stoi(s);
            cout << name[n] <<"\n";
        }else{
            auto it = maps.find(s);
            cout << it->second << "\n";
        }
    }

}
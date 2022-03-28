// 2480.cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    vector<int> v(3);
    cin >> v[0] >> v[1] >> v[2];

    sort(v.begin(), v.end());
    if(v[0] == v[1] && v[1] == v[2]) cout << 10000+(v[0]*1000)<< "\n";
    else if(v[0]==v[1]) cout << 1000+(v[0]*100)<< "\n";
    else if(v[0]==v[2]) cout << 1000+(v[0]*100)<< "\n";
    else if(v[1]==v[2]) cout << 1000+(v[1]*100)<< "\n";
    else cout << v[2]*100 << "\n";
}
// vector를 이용하여 sort후 문제풀이
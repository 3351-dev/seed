// 4153.cpp
#include<iostream>
#include<vector>
#include<algorithm>
#define MAX 30000
using namespace std;

/* 세 변이 주어지고, 직각 삼각형인지 확인하시오 */

int main(){
    vector<int> dot[3];
    for(int i=0;i<MAX;i++){
        for(int j=0;j<3;j++){
            cin >> dot[i][j];
            if(dot[i][j] == 0) break;
        }
        sort(dot.begin(), dot.end());
        cout << dot.front() << "\n";
    }

}
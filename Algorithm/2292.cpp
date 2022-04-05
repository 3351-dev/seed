// 2292.cpp
/* 
    벌집(육각형)
    1은 1
    그 다음은 6개 (2~7)
    그 다음은 12개(8~19)
    그 다음은 6*n개
    k번째 방을 가려면 그 숫자가 몇번째 라인인지 확인하면되겠네
 */

#include<iostream>
using namespace std;

int main(){
    int n;
    cin >> n;

    int i=1;
    int cnt = 1;
    while(n>i){
        i += 6*cnt;
        cnt ++;
    }

    cout << cnt <<"\n";
}
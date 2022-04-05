// 1712.cpp
#include<iostream>
using namespace std;
/* 
    A 고정비용
    B 한 대당 가변비용 
    C 가격
 */

int main(){
    int a,b,c;
    int profit,ans;
    cin >> a >> b >> c;
    profit = c-b;
    if(profit==0){
        cout << "-1\n";
        return 0;
    }
    ans = a/profit+1;
    if(ans<0){
        cout << "-1\n";
    }else cout << ans <<"\n";

}

// if(b==c) wow
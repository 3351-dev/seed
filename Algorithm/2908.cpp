// 2908.cpp
#include<iostream>
#include<string>
using namespace std;
 /* 
    734 893
    437 398
    입력을 받고, 숫자를 뒤집고 비교해보자
  */
int main(){
    string a,b;
    string a_reverse, b_reverse;
    cin >> a >> b;
    int j=0;
    // cout << "a.size : " << a.size() << "\n";
    for(int i=a.size()-1;i>-1;i--){
        a_reverse += a[i];
        b_reverse += b[i];
    }
    // cout << a_reverse << " " << b_reverse << "\n";
    cout << max(a_reverse,b_reverse) <<"\n";
}
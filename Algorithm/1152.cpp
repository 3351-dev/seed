// 1152.cpp
#include<iostream>
using namespace std;
/* 
    기본베이스를 띄어쓰기로 잡고
    시작의 공백만 빼면되지않을까?
    문제에서 공백이 연속해서 나오는 경우는 없다고 했으므로 처음만 검색한다!
 */
int main(){
    int cnt=0;
    string str;
    
    getline(cin, str); //한줄 받는 방법
    // preprocessing

    // main
    for(int i=0;i<str.size();i++){
        // cout << i << " ";
        if(str[i]==' ') cnt++;
    }
    // cout <<"\n";
    if(str[0]==' ') cnt --;
    if(str[str.size()-1]==' ') {
        cnt--;
    }
    cout << cnt+1 << "\n";
}
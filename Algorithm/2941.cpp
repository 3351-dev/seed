// 2941.cpp
#include<iostream>
#include<string>
using namespace std;
/* 
    크로아티아 알파벳
    c= c- dz= d- lj nj s= z=
    = - 있으면 -1
    lj nj 있으면 -1
    dz= 있으면 -2
 */
int main(){
    int cnt=0;
    string input;

    cin >> input;

    for(int i=0;i<input.size();i++){
        cnt++;
        if(input[i]=='-'||input[i]=='=') cnt--;
        if(input[i]=='l'&&input[i+1]=='j') cnt--;
        if(input[i]=='n'&&input[i+1]=='j') cnt--;
        if(input[i]=='d'&&input[i+1]=='z'&&input[i+2]=='=') cnt--;
    }
    cout << cnt <<"\n";
    // ㄹㅇ 개멍청하게 풀었누...
}
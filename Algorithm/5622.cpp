// 5622.cpp
#include<iostream>
#include<string>
using namespace std;
/* 
    1을 걸려면 2초 필요 -> (n+1)
    2부터 abc
    주어진 단어는 2보다 크거나 같고 15보다 작거나 같다.
    최소 시간을 출력
    Z는 9에 포함되어있으니 조건문으로 처리
    S 또한 7에 들어가있으니 조건문 처리
 */
int main(){
    int cnt=0;
    string word;
    string alphabet="ABCEDFGHIJKLMNOPQRSTUVWXYZ";
    
    cin >> word;
    for(int i=0;i<word.size();i++){
        for(int j=0;j<alphabet.size();j++){
            if(word[i]==alphabet[j] && word[i]=='S'){
                cnt += 7;
            }else if(word[i]==alphabet[j] && (word[i]=='T' || word[i]=='U'|| word[i]=='V')){
                cnt += 8;
            }else if(word[i]==alphabet[j] && (word[i]=='W' || word[i]=='X' || word[i] =='Y' || word[i] =='Z')){
                cnt += 9;
            }else if(word[i]==alphabet[j]){
                cnt += j/3+2;
            }
            
        }
        cnt +=1 ;
        // cout << i << "'s cnt : " << cnt <<"\n";
    }
    cout << cnt <<"\n";
    // 너무 멍청하게 푼거같은데..

    
}
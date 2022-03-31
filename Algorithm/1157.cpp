// 1157.cpp
#include<iostream>
#include<string>
using namespace std;
int main(){
    string word;
    string alpha_big ="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string alpha_small="abcdefghijklmnopqrstuvwxyz";
    int cnt[26]={0,},max=0,max_alpha, max2=0;

    cin >> word;

    for(int i=0;i<word.size();i++){
        for(int j=0;j<alpha_big.size();j++){
            if(word[i]==alpha_big[j] || word[i]==alpha_small[j]){
                cnt[j]+=1;
            }
        }
    }
    // for(int i=0;i<alpha_big.size();i++){
    //     cout << cnt[i] << " ";
    // }
    // cout << "\n";
    for(int i=0;i<alpha_big.size();i++){
        if(cnt[i]>max){
            max=cnt[i];
            max_alpha = i;
            // cout << alpha_big[max] << " ";
        }else if(cnt[i]==max){
            max2=cnt[i];
        }
    }

    // cout << max << " " << max2 <<"\n";

    if(max2<max){
        cout << alpha_big[max_alpha] << "\n";
    }else{
        printf("?\n");
    }
}
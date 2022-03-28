// 10809.cpp
#include<iostream>
#include<string>
using namespace std;

int main(){
    string S;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    cin >> S;

    for(int i=0;i<alphabet.size();i++){
        cout << (int) S.find(alphabet[i]) << " ";
    }
    cout <<"\n";

    return 0;

}
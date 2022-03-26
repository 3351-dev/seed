// 2439.cpp
#include<iostream>
using namespace std;
int main(){
    int N;
    cin >> N;
    for(int i=N;i>0;i--){
        for(int j=0;j<N;j++){
            if(j<i-1) cout << " ";
            else cout << "*";
        }
        cout <<"\n";
    }

    return 0;
}
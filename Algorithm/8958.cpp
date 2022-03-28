// 8958.cpp
#include <iostream>
#include <string>
using namespace std;
int main(){
    int n;
    string str;
    cin >> n;

    for(int i=0;i<n;i++){
        cin >> str;
        int sum=0, cnt=0;
        for(int j=0;j<str.length();j++){
            if(str[j]=='O') cnt++;
            else cnt=0;
            sum+=cnt;
        }
        cout << sum << "\n";
    }

}
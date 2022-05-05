// 1541.cpp

#include<iostream>
#include<string>

using namespace std;

int main(){

    string n;
    string num;
    int ans=0;
    bool minus = false;

    cin >> n;

    for(int i=0;i<n.size()+1;i++){

        if(n[i] == '+' || n[i] == '-' || i == n.size()){
            if(minus){
                ans -= stoi(num);
            }else{
                ans += stoi(num);
            }
            num = "";
            if(n[i] == '-'){
               minus = true;
            }
        }else{
            num += n[i];
        }
        // cout << ans <<"\n";
 
    }

    cout << ans <<"\n";


}
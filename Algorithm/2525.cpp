// 2525.cpp
#include <iostream>
using namespace std;
int main(){
    int a,b,c;
    cin >> a >> b;
    cin >> c;
    b += c;

    if(b>59){
        a+=b/60;
        b%=60;
        // a+=1;
        // b-=60;
    }
    a%=24;
    cout << a << " "<< b <<"\n";
}
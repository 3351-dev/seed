// 9020_1.cpp
#include <iostream>
#include <cmath>
using namespace std;
/* 
    (N/2 - i) + (N/2 + i) = N
    그렇다면, N/2-i와 N/2+i가 소수인것을 찾으면 될까
 */

bool isPrime(int n){
    int val;
    val = sqrt(n);
    // 2 혹은 3
    if(val == 1 && n!= 1){
        return true;
    }
    if(n%2){
        for(int i=2;i<val+1;i++){
            if(!(n%i)) return false;
            if(i == val) return true;
        }
    }
    return 0;
}
int main(){
    // cout << sqrt(8) << ", " << sqrt(3) <<"\n";
    // return 0;
    int T;
    cin >> T;
    for(int i=0;i<T;i++){
        int input;
        cin >> input;
        for(int j=input/2;j>1;j--){
            if(isPrime(j)&&isPrime(input-j)){
                cout << j << " " << input-j <<"\n";
                break;
            }
        }
    }

}
// 1904.cpp

#include<iostream>

using namespace std;

/* 
    1 -> (1) 1
    2 -> (2) 00, 11
    3 -> (3) 001, 100, 111
    4 -> (5) 0011, 1001, 1100, 0000, 1111
    5 -> (8) 00111, 10011, 11001, 11100,
            00001, 00100, 10000
            11111
 */

long long arr[1000001] ={ 1,2,};

long long solution(int n){
    if(n<2) return arr[n];
    else if(arr[n] == 0)
        arr[n] = solution(n-1) + solution(n-2);
    return arr[n]%15746;

}

int main(){
    int n;
    cin >> n;
    cout << solution(n-1) << "\n";

}

// 1193.cpp
/* 
    1 = 1/1
    2 = 1/2
    3 = 2/1
    4 = 3/1
    5 = 2/2
    6 = 1/3
    7 = 1/4
    8 = 2/3
    9 = 3/2
    ...
    14 = 2/4
    분모 1 2 1 , 1 2 3 4 3 2 1 , 1 2 3 4 5 6 7 8 7 6 5 4 3 2 1, ...
    분자 1 ,1 2 3 2 1, 1 2 3 4 5 4 3 2 1 , ...
    
    분모의 경우 싸이클 당 2n 까지 증가하함 (3, 7, 15 ...) (4n-1)*(n-1)
    분자의 경우 싸이클 2n-1 까지 증가함 (1, 5, 9 ...)
 */

/* 
    1 | 2 3 | 4 5 6 | 7 8 9 10 | ... 
 */
#include<iostream>
using namespace std;

int main(){
    int x,rule=0;
    cin >> x;

    while(x>0){
        rule++;
        x -= rule;
    }
    if(rule%2 == 1) cout << 1-x << "/" << rule+x << "\n";
    else cout << rule+x << "/" << 1-x <<"\n";
}


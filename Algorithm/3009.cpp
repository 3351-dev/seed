// 3009.cpp
#include<iostream>
using namespace std;
/* 
    세 점이 주어졌을때, 축에 평행한 직사각형을 만들기 위해 필요한 네번째 점 
    값이 짝수가 아닌 값을 넣어주면 되지않을까?   
 */

void check(int arr[]){
    for(int i=0;i<3;i++){
        for(int j=i+1;j<3;j++){
            if(arr[i] == arr[j]){
                arr[i] = 1001;
                arr[j] = 1001;
            }
        }
    }
}

void check2(int arr[]){
    for(int i=0;i<3;i++){
        if(arr[i] != 1001){
            cout << arr[i] <<" ";
        }
    }
}
int main(){
    int x[3],y[3],ansX, ansY;
    for(int i=0;i<3;i++){
        cin >> x[i] >> y[i];
    }
    check(x);
    check(y);

    check2(x);
    check2(y);
}
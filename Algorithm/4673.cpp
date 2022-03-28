// 4673.cpp
#include<iostream>
using namespace std;
bool arr[10001];

int d(int n){
    int sum = n;
    while(1){
        if(n==0) break;
        sum += n%10;
        n /= 10;
    }
    return sum;
}

int main(){

    for(int i=1;i<10001;i++){
        int x = d(i);
        if(x<=10001){
            arr[x] = true;
        }
    }
    for(int i=1;i<10001;i++){
        if(!arr[i]) printf("%d\n",i);
    }
    return 0;
}
//11047.cpp
#include <iostream>
using namespace std;

int main(){
    int N, K, cnt=0;
    cin >> N >> K;
    int arr[N];
    // 0 ~ N-1
    for(int i=0;i<N;i++){
        cin >> arr[i];
    }

    // N-1 ~ 0
    for(int i=N-1;i>=0;i--){
        if(K/arr[i]>0){
            cnt += K/arr[i];
            K %= arr[i];
        }
    }

    printf("%d",cnt);

    return 0;
}

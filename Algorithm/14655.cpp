//14655.cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int N, coin,sum=0;
    scanf("%d",&N);

    // 1Round
    for(int i=0;i<N;i++){
        // int coin;
        scanf("%d",&coin);
        sum += abs(coin);
    }
    // 2Round
    for(int i=0;i<N;i++){
        // int coin;6
        scanf("%d",&coin);
        sum += abs(coin);
    }

    printf("%d",sum);
    


    
}
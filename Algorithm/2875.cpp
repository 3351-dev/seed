//2875.cpp
#include <iostream>
using namespace std;

int main(){
    int N,M,K;  // #1 2N:M, #2 must -K
    cin >> N >> M >> K;

    int team = min(N/2, M);
    int intern = N + M - 3*team; //team이 3명으로 이루어져있으므로

    K -= intern;    // K에서 최대 인턴나가는 친구들을 빼는데 이게 양수면 team그대로 표현

    if(K<0){
        cout << team;
    }else{          // 아닐경우 모자란만큼 사람을 빼줘야하므로
        cout << team-(K+2)/3;
    }
    
}
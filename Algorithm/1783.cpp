//1783.cpp
#include <iostream>
using namespace std;

int main(){
    /* 
    세로 N, 가로 M
    1. 2 U 1 R
    2. 1 U 2 R
    3. 1 D 2 R
    4. 2 D 1 R
    N 1 -> 1
    N 2 -> 2,3 -> M에 따라 답이 달라짐, 최대 4칸 방문.(이동횟수 3칸+시작칸) 2*3=6
    N 3 -> M>7이상이면 모든 규칙을 쓸 수 있으며 
    가로로 보았을때 2칸이 비어있으므로 -2가 최대 방문 칸
     */
    int N,M;
    cin >> N >> M;

    if(N==1) cout << 1;
    else if(N==2){
        if(M < 7) cout << (M+1)/2;
        else cout << 4;
    }else{
        if(M<=4) cout << M;
        else if(M>=7) cout << M-2;
        else cout << 4;
    }
    // sol
}

// 2741.cpp
#include<iostream>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    for(int i=0;i<N;i++){
        cout << i+1 << "\n";
        // std::endl은 단순히 개행만 하는것이아닌 버퍼를 비우는 작업도 같이하기때문에 "\n"사용
    }
    return 0;
}
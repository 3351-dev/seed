// 11000.cpp
#include <iostream>
using namespace std;
/* 
    S start 
    T end
    N class

    3
    1 3
    2 4
    3 5
    ans 2

    sol.
    스택을 만들어 ST를 넣고
    다음 S를 보고 모든 스택의 T값을 찾아내어 같으면 넣고 다르면 새로 만든다?
 */
int main(){
    int N, cnt=1;
    cin >> N;
    int S[N], T[N];
    for(int i=0;i<N;i++){
        cin >> S[i] >> T[i];
    }

    for(int i=0;i<N-1;i++){
        if(T[i]==S[i+1]) cnt--;
        else cnt++;
    }
    if(cnt<0) cnt=1;
    cout << cnt << endl;
    return 0;
    // no sol
}
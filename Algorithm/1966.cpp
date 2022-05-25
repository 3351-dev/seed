// 1966.cpp

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int T, N, M;

int main() {
    cin >> T;
    
    while(T--) {
        vector<int> v;
        queue<pair<int,int> > q;
        int cnt=0;

        cin >> N >> M;

        for(int i=0;i<N;i++) {
            int x;
            cin >> x;
            v.push_back(x);
            if(i == M) {
                q.push({x,1}); //표시
            } else q.push({x,0});
        }

        sort(v.begin(),v.end()); //우선 순위 비교 vector

        for(;;) {
            if(v.back()==q.front().first) { //본인 순서고
                if(q.front().second==1) { //찾는 값이면 멈춤
                    cnt++;
                    break;
                }
                else { //본인 순서인데 찾는 값이 아니면 넘김
                    v.pop_back();
                    q.pop();
                    cnt++;
                }
            } else { //본인 순서 아니면 뒤로 그냥 보냄
                q.push({q.front().first,q.front().second});
                q.pop();
            }
        }

        cout << cnt << "\n";
    }
}
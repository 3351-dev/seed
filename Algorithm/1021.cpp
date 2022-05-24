// 1021.cpp

#include<iostream>
#include<deque>
using namespace std;

int x, p, tmp, N, M;
int ans = 0;
int find_num[51]; // M의 입력값
deque<int> dq;

void print_dq(){
	for (int i = 0; i < dq.size(); i++){
		cout << dq.at(i) << " ";
	}
	cout << "\n";
}

int main(){
	cin >> N >> M;
	for (int i = 1; i <= N; i++) dq.push_back(i);

	for (int i = 0; i < M; i++){
		cin >> x;
		find_num[i] = x;
	}

	for (int i = 0; i < M; i++){
		if (dq.size() == 1) continue;// 마지막 한개 남았을 때

		// 덱에서 해당 원소 인덱스 찾기
		for (int j = 0; j < N; j++){
			if (find_num[i] == dq.at(j)) {
				p = j; // 인덱스 저장
				break;
			}
		}

        // 찾으려는 원소가 중간보다 앞쪽에 있을 경우
		if (p <= dq.size() / 2){    
			for (int j = 0; j < p; j++) // 2번연산
			{
				dq.push_back(dq.front());
				dq.pop_front();
				ans++;
			}	
			dq.pop_front();
		}
        // (p > dq.size()/2) 찾으려는 원소가 중간보다 앞쪽에 있을 경우
		else {
            // 3번연산
			for (int j = 0; j < dq.size()- p; j++){
				dq.push_front(dq.back());
				dq.pop_back();
				ans++;
			}
			
			dq.pop_front(); // 1번연산
		}
	}
    cout << ans << "\n";
}
#include <iostream>

using namespace std;

int main()
{
	int N, K;
	int count = 0;

	cin >> N >> K;
	int coin[N];

	for(int i=0;i<N;i++){
		cin >> coin[i];
	}

	for(int i=N-1;K>0;i--){
		if(K/coin[i]){
			count += K/coin[i];
			K %= coin[i];
		}
	}

	cout << count;
}
// TODO Error Check

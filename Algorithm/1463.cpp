// 1463.cpp 
#include <iostream>
#define MIN(x, y) (x < y ? x : y)

using namespace std;

int dp[1000001];

int main(void) {
	
	int N;
    cin >> N;
	
	int i;
	for(i = 2; i<= N; i++){
		dp[i] = dp[i-1] + 1;
		if(i%2 == 0) dp[i] = MIN(dp[i], dp[i/2] + 1);
		if(i%3 == 0) dp[i] = MIN(dp[i], dp[i/3] + 1);
	}
    cout << dp[N] << "\n";

	return 0;
}
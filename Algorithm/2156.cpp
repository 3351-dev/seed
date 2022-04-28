// 2156.cpp

#include<iostream>
#include<cstring>
 
#define endl "\n"
#define MAX 10000 + 1
using namespace std;
 
int N;
int Arr[MAX];
int DP[MAX];
 
int Bigger(int A, int B) { if (A > B) return A; return B; }
 
void Initialize()
{
    memset(Arr, 0, sizeof(Arr));
    memset(DP, 0, sizeof(DP));
}
 
void Input()
{
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> Arr[i];
    }
}
 
void Solution()
{
    DP[0] = Arr[0] = 0;
    DP[1] = Arr[1];
    DP[2] = Arr[1] + Arr[2];
    // 3잔 연속 마실 수 없다.
    // 1. 마지막 잔을 기준으로 3번째 앞에 잔을 마시고, 2번째 앞에 잔을 건너뛰고 1번째 앞에 잔 + 마지막잔 
    // 2. 마지막 잔을 기준으로 2번째 앞에 잔을 마시고 + 마지막 잔
    // 3. 마지막 잔을 마시지 않고, 1번째 앞에 잔의 최댓값
    for (int i = 3; i <= N; i++)
    {
        DP[i] = Bigger(DP[i - 3] + Arr[i - 1] + Arr[i], Bigger(DP[i - 2] + Arr[i], DP[i - 1]));
    }
}
 
void Solve()
{
    Initialize();
    Input();
    Solution();
 
    cout << DP[N] << endl;
}
 
int main(void)
{

    Solve();
 
}
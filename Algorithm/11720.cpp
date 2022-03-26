// 11720.cpp

#include <iostream>
using namespace std;

int main(){
    int N=0, sum=0;
    cin >> N;
    // int arr[N];
    char arr[N]; // 문자를 하나하나씩 받기 위해서 char형 사용

    for(int i=0;i<N;i++){
        cin >> arr[i];
        sum += (arr[i]-48);
//      48대신 -'0'을 해줘도된다.
//      char 형으로 숫자를 받았기때문에 숫자로 나타내주기 위해 48을 빼줌
    }

    cout << sum << endl;

}
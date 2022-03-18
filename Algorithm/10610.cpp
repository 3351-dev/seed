// 10610.cpp
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main(){
    int sum=0,switchZ;
    string N;
    cin >> N;

    for(int i=0;i < N.size();i++){        
        sum += N[i]-'0';
        // sum += N[i]&15;
        if(N[i]-'0' == 0){
            // printf("%d\n",i);
            switchZ =1;
        }
    }
    if(sum % 3 != 0 || switchZ == 0){
        cout << -1 << endl;
        return 0;
    }

    sort(N.begin(), N.end(), greater<>());
    cout << N << endl;
    return 0;

}


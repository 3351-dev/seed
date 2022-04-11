// 2231.cpp
#include<iostream>
#include<cmath>
using namespace std;
/* 
    분해합은 N과 N을 이루는 각 자리수의 합 
    N이 주어졌을때 N의 가장 작은 생성자를 구하시오
    245는 256의 생성자
    ex)
    a + 10*b + 100*c + d = d
*/

int digit(int n){
    if(n/10){
        return n%10 + digit(n/10);
    }else{
        return n;
    }
}

int cntDecimal(int n,int cnt){
    if(n/10){
        cnt++;
        return cntDecimal(n/10,cnt);
    }else{
        return cnt;
    }
}

int main(){
    int n,m,sum;
    cin >> n;

    for(int i=1; i<n; i++){
        sum = i;
        m = i;
        
        while(m){
            sum += m%10;
            m /= 10;
        }

        if(n == sum){
            cout << i << "\n";
            return 0;
        }
    }

    cout << "0" <<"\n";
    return 0;
}
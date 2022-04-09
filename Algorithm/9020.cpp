// 9020.cpp

#include <iostream>
#include<cmath>
using namespace std;

int main(){
// init 
    int T;
    cin >> T;
    int cal[T];
    for(int i=0;i<T;i++){
        cin >> cal[i];
    }

// find Prime
    int arr[10001],prime[2000]={0};
    int n=1, m=10000, j=0;
    for(int i=0;i<m;i++){
        arr[i] = i;
    }

    for(int i=2;i<sqrt(m+1);i++){
        if(arr[i] == 0) continue;
        for(int j=i*i;j<m+1;j+=i){
            arr[j]=0;
        }
    }

    int PrimeCnt = 0;
    for(int i=n;i<m;i++){
        if(arr[i]!=0){
            PrimeCnt ++;
            // cout << "arr[i] is " << arr[i] <<"\n";
            prime[j] = arr[i];
            j+=1;
        }
    }

    // cout << PrimeCnt << "\n";
    // for(int i=0;i<T;i++){
    //     cout << cal[i] << ", ";
    // }

// calculate
    int saveJ,saveK,min=9999;
    for(int i=0;i<T;i++){
        for(int j=0;j<PrimeCnt;j++){
            for(int k=0;k<PrimeCnt;k++){
                if(prime[j]+prime[k]==cal[i] && prime[k]>prime[j]){
                    cout << prime[j] << " " << prime[k] << "\n";
                    // 이 값들을 계속 저장하다가 마지막 부분에서 차이가 가장 적은것을 출력하면 어떨까
                    if(prime[k]-prime[j]<min){
                        saveJ=prime[j];
                        saveK=prime[k];
                    }
                }
            }
        }
        // 
        cout << saveJ << " " << saveK <<"\n";
    }
    
    return 0;

}
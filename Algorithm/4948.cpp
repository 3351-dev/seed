// 4948.cpp
#include<iostream>
#include<cmath>
using namespace std;

void prime(int n, int m){
    int cnt=0;
    int arr[m];

    // cout << n << " " << m <<"\n";
    for(int i=0;i<m+1;i++){
        arr[i] = i;
    }
    for(int i=2;i<sqrt(m+1);i++){
        if(arr[i]==0) continue;
        for(int j=i*i; j<m+1; j+=i){
            arr[j] = 0;
        }
    }
    for(int i=n+1;i<m+1;i++){
        // if(arr[i]==1) cnt++;
        if(arr[i]!=0) {
            // cout << "arr["<< i << "] : " <<arr[i] <<"\n";
            cnt++;
        }
    }
    cout << cnt << "\n";
    
    
}

int main(){
    int arr[123456], end;
    for(int i=0;i<123456;i++){
        cin >> arr[i];
        if(arr[i] == 0){
            end = i;
            break;
        }
    }

    for(int i=0;i<end;i++){
        int a = arr[i];
        prime(a,2*a);
    }

    
    return 0;
}
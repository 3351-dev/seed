// 1067.cpp

#include<iostream>
#include<string>
#include<cstring>
/* 
    1 2 3 4 , 6 7 8 5 이 순서대로 순환이동을 했을때 가장 큰 값
    1 2 3 4 , 5 6 7 8 -> 5 12 21 32 = 70
    하나는 순환이동을 하지않고, 다른 행렬만 순환이동을해서 가장 큰 값끼리 곱해주도록 하면 되지않을까?
    23 4 95 20 17 94 63 44 13 96
    53 2 87 54 13 18 61 24 17 94

    1 2 3 4
    4 1 2 3
    3 4 1 2
    2 3 4 1
 */

using namespace std;

void cycle(int arr[], int n){
    int temp;
    for(int i=0;i<n-1;i++){
        temp = arr[i];
        arr[i] = arr[i+1];
        arr[i+1] = temp;
    }
}

int main(){
    int n;
    cin >> n;
    int arrA[n], arrB[n], sum[n];
    int max = 0;

    for(int i=0;i<n;i++){
        cin >> arrA[i] ;
    }
    for(int i=0;i<n;i++){
        cin >> arrB[i];
    }
    for(int i=0;i<n;i++){
        sum[i] = 0;
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            sum[i] += arrA[j]*arrB[j];
            cout << arrA[j] << " x " << arrB[j] <<", ";
        }
        cout << "sum : "<< sum[i] <<"\n";
        cycle(arrA,n);
    }

    for(int i=0;i<n;i++){
        if(max<sum[i]) max = sum[i];
    }
    cout << max <<"\n";
}
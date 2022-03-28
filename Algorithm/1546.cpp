// 1546.cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main(){
    int n,max=0;
    float sum=0;
    cin >> n;
    float arr[n];
    for(int i=0;i<n;i++){
        cin >> arr[i];
        if(arr[i]>max) max = arr[i];
    }
    // printf("max : %d\n",max);

    for(int i=0;i<n;i++){
        sum += arr[i]/max*100;
        // cout << arr[i]/max*100 << "\n";
    }
    printf("%.2f\n",sum/n);
    
}
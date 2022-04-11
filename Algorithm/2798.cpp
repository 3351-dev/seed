// 2798.cpp
#include <iostream>
using namespace std;

int main(){
    int n, m, min = 0;
    cin >> n >> m;
    int card[m];
    for(int i=0;i < n;i++){
        cin >> card[i];
    }

    for(int i=0;i<n-2;i++){
        for(int j=i+1;j<n-1;j++){
            for(int k=j+1;k<n;k++){
                int sum = card[i]+card[j]+card[k];
                // cout << card[i] << " " << card[j]<< " " << card[k] << " : " << sum <<"\n";
                if(sum == m){
                    cout << sum << "\n";
                    return 0;
                }else if(sum < m && sum > min) {
                    min = sum;
                }
            }
        }
    }

    cout << min << "\n";

}
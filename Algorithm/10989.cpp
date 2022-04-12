// 10989.cpp
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    int n, tmp;
    int count[10001] ={0,};
    // cin >> n;
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        // cin >> tmp;
        scanf("%d",&tmp);
        count[tmp]++;
    }

    for(int i=0;i<10001;i++){
        for(int j=0;j<count[i];j++){
            // cout << i <<"\n";
            printf("%d\n",i);
        }
    }
}
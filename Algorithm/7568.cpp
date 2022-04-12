// 7568.cpp

#include<iostream>
using namespace std;

int main(){
    int n,max = 0;
    cin >> n;
    int arr[n][2], rank=1;
    for(int i=0;i<n;i++){
        cin >> arr[i][0] >> arr[i][1];
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(arr[i][0] < arr[j][0] && arr[i][1] < arr[j][1]){
                rank++;
            }
        }
        cout << rank << " ";
        rank = 1;
    }

    // // int max=0;
    // for(int i=0;i<n;i++){
    //     // cout << rank[i] <<"\n";
    //     if(max<rank[i]){
    //         max = i;
    //     }
    // }

    // // cout << "max : " << max << "\n";
    // int rankingCnt = 1,endCnt, peopleCnt;
    // while(1){
    //     endCnt = 0;
    //     peopleCnt = 0;
    //     for(int i=0;i<n;i++){
    //         if(rank[i] == max && showRank[i] == -1){
    //             // cout << "i : " << i << " " << rank[i] <<"\n";
    //             showRank[i] = rankingCnt;
    //             peopleCnt ++;
    //         }
    //     }
    //     rankingCnt += peopleCnt;
    //     // cout << "rankingCnt : "<< rankingCnt << "\n";
    //     max -= 1;

    //     for(int i=0;i<n;i++){
    //         if(showRank[i] != -1){
    //             endCnt++;
    //         }
    //     }
    //     if(endCnt == 5) break;
    // }

    // for(int i=0;i<n;i++){
    //     cout << showRank[i] << " ";
    // }
    cout <<"\n";
}
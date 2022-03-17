#include<iostream>
#include<cstdio>
using namespace std;

int main(){
    int cnt=0;
    char board[8][8];

    for(int i=0;i<8;i++){
        scanf("%s",board[i]);
    }

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if((i+j)%2==0 && board[i][j]=='F'){
                cnt++;
            }
        }
    }
    printf("%d\n",cnt);
    return 0;
}

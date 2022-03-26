#include <iostream>
#include <cstdio>
using namespace std;

int main(){
    char board[8][8];
    int count = 0;
    for(int i=0;i<8;i++){
        scanf("%s",board[i]);
    }

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            // scanf("%s", &board[i][j]);
            if(i%2==1&&j%2==1){ // (0,0)은 흰색, i%2==0의 조건식은 (0,1)
                if(board[i][j]=='F'){
                    count++;
                }
            }else if(i%2==0&&j%2==0){
                if(board[i][j]=='F'){
                    count++;
                }
            }
        }
    }
    printf("%d\n",count);
}
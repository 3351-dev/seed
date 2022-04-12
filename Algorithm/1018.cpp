// 1018.cpp
#include<iostream>
#include<algorithm>
using namespace std;

string board[50];
string WB[8]={
    "WBWBWBWB",
    "BWBWBWBW",
    "WBWBWBWB",
    "BWBWBWBW",
    "WBWBWBWB",
    "BWBWBWBW",
    "WBWBWBWB",
    "BWBWBWBW"
};

string BW[8]={
    "BWBWBWBW",
    "WBWBWBWB",
    "BWBWBWBW",
    "WBWBWBWB",
    "BWBWBWBW",
    "WBWBWBWB",
    "BWBWBWBW",
    "WBWBWBWB"
};

int WB_cnt(int x, int y){
    int cnt = 0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(board[x+i][y+j] != WB[i][j]) cnt++;
        }
    }
    return cnt;
}

int BW_cnt(int x, int y){
    int cnt = 0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(board[x+i][y+j] != BW[i][j]) cnt++;
        }
    }
    return cnt;
}


int main(){
    int size[2];
    int cnt;
    int minimum=9999;
    pair<int, int> p1;

    cin >> p1.first >> p1.second;

    for(int i=0;i<p1.first;i++) cin >> board[i];

    for(int i=0; i+8<p1.first+1; i++){
        for(int j=0; j+8<p1.second+1; j++){
            int tmp;
            tmp = min(WB_cnt(i,j),BW_cnt(i,j));
            if(tmp<minimum) minimum = tmp;
        }
    }

    cout << minimum <<"\n";
}

// pair, min, 한방향아닌 두방향 생각하기.
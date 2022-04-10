// 1002.cpp

#include<iostream>
#include<cmath>
using namespace std;

int main(){
    int T;
    cin >> T;
    int arr[T][6]; // x1 y1 r1 x2 y2 r2
                   //  0  1  2  3  4  5
    double d;

    for(int i=0;i<T;i++){
        for(int j=0;j<6;j++){
            cin >> arr[i][j];
        }
    }
    for(int i=0;i<T;i++){
        d = sqrt(pow(arr[i][3]-arr[i][0],2)+pow(arr[i][4]-arr[i][1],2));
        int r1 = arr[i][2];
        int r2 = arr[i][5];
        // cout << "d : " << d <<"\n";

        // 동원일때
        if(d==0 && r1 == r2) cout << "-1\n";
        // 내접, 외접할때
        else if(abs(r1+r2) == d || abs(r1-r2) == d) cout <<"1\n";
        // 서로 다른 두점에서 만날때
        else if(abs(r1-r2) < d && d < abs(r1+r2)) cout <<"2\n";
        // 안만날때
        else cout << "0\n";
    }
}
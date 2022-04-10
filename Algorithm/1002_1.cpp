// 1002_1.cpp

#include<iostream>
#include<cmath>
using namespace std;
/* 
    d = sqrt(pow(x1-x2,2)+pow(y1-y2,2))
    d = 0 && r1 == r2              -1
    r1 + r2 = d || r1 - r2 = d      1
    r1 - r2 < d && d < r1 + r2      2
    r1 + r2 > d || r1 - r2 < d      0

 */

int main(){
    int T;
    int x1,y1,r1,x2,y2,r2;
    double d;
    
    cin >> T;
    for(int i=0;i<T;i++){
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
        d = sqrt(pow(x1-x2,2)+pow(y1-y2,2));

        // cout << "d : " << d <<"\n";
        // cout << abs(r1-r2) << "\n";

        if(d==0 && r1==r2) cout << "-1\n";
        else if (abs(r1+r2) == d || abs(r1-r2) == d) cout << "1\n";
        else if (abs(r1-r2) < d && d < abs(r1+r2)) cout << "2\n";
        else cout << "0\n";
    }
}
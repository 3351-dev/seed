// 10250.cpp

#include <iostream>
using namespace std;

int main(){
    int t,h,w,n;
    cin >> t;

    for(int i=0;i<t;i++){
        int floor, unit = 1;
        cin >> h >> w >> n;
        unit += n/h;
        floor = n%h;
        // 조건을 잘 확인하자
        if(floor == 0){
            floor = h;
            unit--;
        }

        if(unit<10){
            cout << floor << "0" << unit <<"\n";
        }else{
            cout << floor << unit <<"\n";
        }

    }
}
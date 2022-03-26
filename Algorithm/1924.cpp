// 1924.cpp

#include <iostream>
using namespace std;
int main(){
    // 01.01 = Mon
    // 요일은 7이니까 기준점이 되는 날로부터 몇일째인지 알아내서 7로 나누면 되지않을까
    // 그렇다면 모든달을 31일로 잡고, 2월은 -3, 4,6,9,11은 -1로 계산해보자
    int x, y;
    int month, day, ans;
    int specialMonth[5]={2,4,6,9,11};
    string week[7] = {
        "SUN","MON","TUE","WED","THU","FRI","SAT"
    };
    cin >> x >> y;

    month = x-1;
    day = month * 31 + y;
    for(int i=0;i<5;i++){
        if(x>specialMonth[i]){
            if(i==0)
                day -= 3;
            else
                day -= 1;
        }
    }

    // cout << day << "\n";

    ans = day%7;
    cout << week[ans] << "\n";

}
// 1085.cpp

#include<iostream>
using namespace std;
/* 
    현재 위치 (x,y)
    왼쪽 아래 꼭짓점 (0,0)
    오른쪽 위 꼭짓점 (w,h)
    input >> x, y, w, h
    경계선까지 가는 최소값 구하기
    solution
     현재 위치가 어디와 같은지 판단
     가까운쪽으로 수선의 발을 내리고 측정

 */

int main(){
    int x,y,w,h,shortX,shortY, ans;
    cin >> x >> y >> w >> h;

    shortX = (x-0)>(w-x)? w-x : x-0;
    shortY = (y-0)>(h-y)? h-y : y-0;
    ans = (shortX>shortY)?shortY:shortX;
    cout <<  ans <<"\n";

}
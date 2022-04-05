// 2869.cpp
/* 
    높이가 V
    낮에는 A 올라감
    밤에는 B 내려감
    최대에 도달하면 멈춤
 */
#include<iostream>
using namespace std;
int main(){
    int v,a,b,cnt =0;
    int oneDay=1;
    cin >> a >> b >> v;
    // 하루에 이동하는 정도 a-b;
    
    /* while(1){
        oneDay += a;
        if(oneDay>=v) break;
        oneDay -= b;
        cnt ++;
    }
    cout << cnt <<"\n"; */
    // 위의 코드는 출력 초과

    oneDay += (v-a)/(a-b);
    if((v-a)%(a-b) != 0) oneDay++;
    if(a>=v) cout << "1" <<"\n";
    else cout << oneDay << "\n";

}
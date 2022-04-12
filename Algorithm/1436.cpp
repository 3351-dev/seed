// 1436.cpp
#include<iostream>
#include<string>
using namespace std;
/* 
    종말의 숫자
    "666"이 세트로 들어가는 숫자
    666 1666 2666 ... 6666 7666 ... 6661 6662 6663
    666을 한 세트로 묶자
    N666 > 666N > N666N > N666NN
    666은 세트로 볼거니까 N_ > N_N > N N_ N > ...
 */
int findSeries(int n){
    int i = 666;
    int series = 0;
    string target;
    while(1){
        target = to_string(i);
        for(int j=0;j<target.length()-2;j++){
            if(target[j]=='6' && target[j+1]=='6' && target[j+2]=='6'){
                series++;
                if(series==n) return i;
                break;
            }
        }
        i++;
    }
}

int main(){
    int n;
    cin >> n;
    cout << findSeries(n) <<"\n";
}
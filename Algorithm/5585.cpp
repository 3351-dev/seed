//5585.cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int pay, cnt=0;
    vector<int> charge={500,100,50,10,5,1};

    scanf("%d",&pay);
    pay = 1000-pay;

    for(int i=0;i<charge.size();i++){
        cnt += pay/charge[i];
        pay %= charge[i];
    }

    printf("%d",cnt);

}
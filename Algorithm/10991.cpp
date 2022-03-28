// 10991.cpp
#include <iostream>
using namespace std;
int main(){
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=n;j>i+1;j--){
            printf(" ");
        }
        for(int j=0;j<2*i+1;j++){
            if(j%2==0) printf("*");
            else printf(" ");
        }
        

        printf("\n");
    }
}
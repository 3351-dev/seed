// 10992.cpp
#include <iostream>
using namespace std;
int main(){
    int n;
    cin >> n;

    for(int i=0;i<n;i++){
        for(int j=0;j<n+i;j++){
            if(i != n-1){
                if(j<n-i-1){
                    printf(" ");
                }
                else if(j==n-i-1){
                    printf("*");
                }
                else if(j>n-i-1 && j!=n+i-1){
                    printf(" ");
                }
                else if(j==n+i-1){
                    printf("*");
                }    
            }
            else printf("*");
        }
        printf("\n");
    }
}
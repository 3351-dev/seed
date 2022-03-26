#include <iostream>
using namespace std;

int main(){
    int t,a,b;
    cin >> t;
    for(int i=0;i<t;i++){
        cin >> a >> b;
        printf("Case #%d: %d + %d = %d\n",i+1,a,b,a+b);
    }
}
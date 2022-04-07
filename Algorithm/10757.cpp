// 10757.cpp

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// string reverse(string arr){
//     for(int i=0;i<arr.size()/2;i++){
//         char temp = arr[i];
//         arr[i] = arr[arr.size()-i-1];
//         arr[arr.size()-i-1]=temp;
//     }
//     // cout << "reverse : " << arr <<"\n";
//     return arr;
// }

void reverse(char arr[]){
    int len = strlen(arr);
    for(int i=0;i<len/2;i++){
        char temp = arr[i];
        arr[i] = arr[len -i -1];
        arr[len -i -1] = temp;
    }
}

int main(){
    char a[10002]={0},b[10002]={0};
    char ans[10003]={0};
    int ten=0;
    
    cin >> a >> b;
    reverse(a);
    reverse(b);

    int len;
    len = (strlen(a)>strlen(b))?strlen(a):strlen(b);
    // cout << len << "\n";
    for(int i=0;i<len;i++){
        int sum = a[i] - '0' + b[i] - '0' + ten;
        if(sum < 0){
            sum += '0';
        }
        if(sum > 9) ten = 1;
        else ten = 0;
        ans[i] = sum % 10 + '0';
        // ans를 string으로 선언하면 안나옴
        // cout << i << "'s a[i] : " << a[i] << ", b[i] : " << b[i] << ", sum : " << sum << ", ans[i] : " << ans << "\n";
    }
    if(ten == 1) ans[len] = '1';
    reverse(ans);
    cout << ans <<"\n";
}
// 9223372036854775807 9223372036854775808 
// 4344.cpp
#include <iostream>
using namespace std;
int main(){
    int testCase=0;
    cin >> testCase;

    for(int i=0;i<testCase;i++){
        int case_num;
        cin >> case_num;
        float point[case_num];
        float sum = 0;
        int cnt=0;
        for(int j=0;j<case_num;j++){
            cin >> point[j];
            sum += point[j];
        }
        sum /= case_num;
        for(int k=0;k<case_num;k++){
            if(point[k]>sum) cnt++;
        }
        printf("%.3f%%\n",(float)cnt/case_num*100);
    }
}
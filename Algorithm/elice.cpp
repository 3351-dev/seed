// elice.cpp
#include<iostream>
#include<stack>
#include<queue>
using namespace std;
int main(){
    int n;
    int input_num, separator;
    stack<int> left;
    queue<int> right;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> input_num >> separator;
        // cout << input_num <<" "<<separator<<"\n";
        if(separator==0){
            left.push(input_num);
        }else{
            right.push(input_num);
        }
    }

    while(left.empty()==0){
        cout << left.top() << " ";
        left.pop();

    }

    while(right.empty()==0){
        cout << right.front() <<" ";
        right.pop();
    }
}
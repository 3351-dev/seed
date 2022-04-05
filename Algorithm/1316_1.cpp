// 1316_1.cpp

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int n, cnt=0;
string word;
vector<char> temp;
bool flag =0;

void reset(){
    temp.clear();
    flag = 0;
}

int main(){
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> word;
        for(int j=0;j<word.size();j++){
            if(find(temp.begin(), temp.end(), word[j]) != temp.end()){
                if(temp.back()!=word[j]){
                    flag = 1;
                    break;
                }
            }else{
                char x = word[j];
                temp.push_back(x);
            }
        }
        if(!flag) cnt++;
        reset();
    }
    cout << cnt <<"\n";
}
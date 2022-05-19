// 1874.cpp

#include<iostream>
#include<stack>
#include<vector>

using namespace std;

int main(){
    stack<int> st;
    vector<char> res;
    int cnt = 1;
    int n;
    cin >> n;

    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        while(cnt<=x){
            st.push(cnt);
            cnt+=1;
            res.push_back('+');
        }

        if(st.top() == x){
            st.pop();
            res.push_back('-');
        }else{
            cout << "NO";
            return 0;
        }
    }

    for(int i=0;i<res.size();i++){
        cout << res[i] << "\n";
    }

}

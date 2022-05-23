#include <iostream>
#include <stack>
using namespace std;

int n;
int main(){
    cin >> n;
    stack<int> s;
    stack<int> ans;
    for(int i = 0, data ; i < n ; i++)
    {
        cin >> data;
        s.push(data);
    }

    stack<int> temp;
    while(!s.empty()){
        if(temp.empty()){
            ans.push(-1);
            temp.push(s.top());
        }
        else{
            if(s.top() < temp.top()){
                ans.push(temp.top());
                temp.push(s.top());
            }
            else{
                temp.pop();
                continue;
            }
        }
        s.pop();
    }

    while(!ans.empty()){
        cout << ans.top() << " ";
        ans.pop();
    }
    cout << '\n';
}

#include<iostream>
#include<stack>
#include<string>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	while (1) {
		string str;
		getline(cin, str); // 한 줄씩
		stack<char>s; // 괄호 저장
		bool ans = true; // yes 인지 no인지!!
		if (str.length() == 1 && str[0] == '.') break;
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == '(' || str[i] == '[') {
				s.push(str[i]);
			}
			if (str[i] == ')') {
				if (s.empty() || s.top() == '[') ans = false;
				else s.pop();
			}
			if (str[i] == ']') {
				if (s.empty() || s.top() == '(') ans = false;
				else s.pop();
			}
		}
		if (s.empty() && ans) cout << "yes" << '\n'; // 모든 과정이 끝났을때 stack 비어있고 ans가 true면 문자열이 균형
		else cout << "no" << '\n';
	}
	return 0;
}

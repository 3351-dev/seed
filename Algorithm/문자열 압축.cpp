// 문자열 압축.cpp

#include<iostream>

using namespace std;

int solution(string s){

	int answer = s.size();

	for(int i=1;i<=s.size()/2;i++){
		int cnt = 1;
		string temp = "", a = "";
		a = s.substr(0,i);	// 0부터 i번째까지 뽑아냄
		for(int j=i;j<s.size();j+=i){
			if(a==s.substr(j,i)) cnt++;	// 같은 뭉치가 있으면 카운터 ++
			else{
				if(cnt>1) temp += to_string(cnt);
				temp += a;
				a = s.substr(j,i);
				cnt = 1;
			}
		}
		if(cnt > 1) temp += to_string(cnt);
		temp+=a;
		if(answer > temp.size()) answer = temp.size();

	}
	cout << answer << "\n";
	return answer;
}

int main(){
	// string str = "aabbaccc";
	// cout << str.length() << "\n\n";
	// string str2 = "2a2ba3c";
	// cout << str2.length() << "\n\n";

	solution("aabbaccc");
	solution("ababcdcdababcdcd");
	solution("abcabcdede");
	solution("abcabcabcabcdededededede");
	solution("xababcdcdababcdcd");
}
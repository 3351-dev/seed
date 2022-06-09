// programers_신규아이디추천.cpp

#include<iostream>
#include<vector>

using namespace std;

/*
	Rules
	1. 소문자 치환
	2. 소문자, 숫자, -, _, . 제외한 문자제거
	3. .. -> .
	4. .이 처음 혹은 끝이면 제거
	5. 빈문자열이라면 a를 대입
	6. 16글자 이상이면 15개의 문자를 제외한 나머지 문자 제거, 이후 4번 적용
	7. 2글자 이하라면 마지막 글자를 3글자가 되도록 끝에 붙임

*/
string firstDotCheck(string str);

string solution(string new_id){
	string answer = "";


	// 1
	for(auto& ch : new_id){
		if('A' <= ch && 'Z' >=ch){
			ch |= 32;
		}

	}
	// cout << new_id <<"\n";

	// 2
	for(auto& ch : new_id){
		if((ch >= 'a' && ch<='z')||(ch>='0' && ch<='9' || ch == '-' || ch == '_' || ch == '.')){
			answer.push_back(ch);
		}
	}
	// cout << answer <<"\n";

	// 3
	int i = 0;
	while( i < answer.length()){
		if(answer[i-1] == '.' && answer[i] =='.'){
			answer.erase(answer.begin()+i);
			continue;
		}
		i++;
	}
	// cout << answer <<"\n";

	// 4
	// function firstDotCheck
	answer = firstDotCheck(answer);
	// if(answer[0] == '.'){
	// 	answer.erase(answer.begin());
	// }
	// cout << answer <<"\n";

	// 5
	if(answer.length() == 0){
		answer.push_back('a');
	}

	// 6
	if(answer.length()>=16){
		answer.erase(answer.begin()+15, answer.end());
		answer = firstDotCheck(answer);
	}
	// cout << answer<<"\n";

	// 7
	if(answer.length()<3){
		char ch = answer[answer.length()-1];
		while(answer.length()!=3){
			answer.push_back(ch);
		}
	}

	cout << answer <<"\n";
	return answer;

}

int main(){
	solution("...!@BaT#*..y.abcdefghijklm");
	solution("z-+.^.");
}

string firstDotCheck(string str){
	if(str[0] == '.'){
		str.erase(str.begin());
	}
	if(str[str.length()-1] =='.'){
		str.erase(str.end()-1);
	}

	return str;
}
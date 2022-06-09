// string.cpp

#include<bits/stdc++.h>

using namespace std;

int main(){
	string str = "123.+_213";

	cout << str << "\n";

	str.clear();
	cout << str <<"\n";

	if(str.empty()){
		printf("empty, %d, %d\n",str.empty(), str.back());
	}else{
		printf("not empty\n");
	}
}
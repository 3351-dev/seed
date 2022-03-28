// 1110.cpp
#include <iostream>
using namespace std;
int main(){
    int n,ori,count;
    cin >> ori;
    n = ori;
    while(1){
        n = (n%10)*10 + ((n/10)+(n%10))%10;
        count ++;
        if(n == ori) break;
    }
    cout << count << "\n";
}
/*
#include <iostream>
using namespace std;

int main() {
	int n;
	int cnt = 0;
	int num, temp;
	cin >> n;
	num = n;

	while (1) {
		temp = (n % 10) * 10 + (n / 10 + n % 10) % 10;
		cnt++;
		n = temp;
		if (temp == num)
			break;
	}
	cout << cnt << '\n';
}
*/
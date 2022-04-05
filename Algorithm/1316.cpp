// 1316.cpp
#include<iostream>
#include<string>
using namespace std;
/* 
    ccaazzzbb = c a z b
    kin = k i n
    aabbccb = a b c b
    자신의 문자가 한번 더 나오면 단어그룹(연속되면 제외)
 */
int main(){
    int cnt=0,n;
    bool pos;
    cin >> n;
    string word;

    for(int i=0;i<n;i++){
        pos = 1;
        cin >> word;
        // cout <<"\n";
        for(int j=0;j<word.size();j++){
            if(word.size()==1){
                // cout <<"size 1 "<<"\n";
                break;
            }
            int last = j;
            for(int k=j+1;k<word.size();k++){
                // cout << word[j] << " " << word[k] <<"\n";
                if(word[j] == word[k]){
                    if(k-last==1){
                        j = k;
                        last=k;
                    }
                    else {
                        // cout << " false" <<"\n";
                        pos = 0;
                        break;
                    }
                }
            }
            if(!pos) continue;
        }
        if(pos){
            cnt++;
            // cout << "cnt ++ " <<"\n";
        }
    }

    cout << cnt <<"\n";

}

/* 
    틀렸던 이유
    1. 하나일 경우 cnt++가 작동하지 않았던점
    2. 하나일 경우 cnt++가 두번 작동했던점
 */
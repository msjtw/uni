#include<iostream>
#include<set>

using namespace std;

int num[300] {};

bool test(char c){
    bool popsuted = false;
    for(int i = 'a'; i <= 'z'; i++){
        if(num[i] == 0)
            continue;
        if(i == c)
            continue;
        else if(num[i] == num[c])
            continue;
        else if((num[i] == num[c] + 1 or num[i] == 1)and !popsuted){
            popsuted = true;
            continue;
        }
        else
            return false;
    }
    return true;
}

int main(){
    string s;
    cin >> s;
    for(auto c : s){
        num[c] += 1;
    }
    set<int>res;
    bool rem = false;
    
    for(int i = 'a'; i <= 'z'; i++){
        //cout << num[i] << " ";
        if(test(i)){
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
    return 0;
}
#include<map>
#include<iostream>

using namespace std;

int hash_f(string s){
    long long int sum = 0;
    for(int i = 0 ; i < s.length(); i++){
        sum += s[i]*(i+1);
    }
    sum *= 19;
    return sum % 101;
}

int main(){
    cout << hash_f("Dabrowski") << endl;
    cout << hash_f("Polski") << endl;
    cout << hash_f("marsz") << endl;
    cout << hash_f("ziemii") << endl;
    cout << hash_f("z") << endl;
}
#include<iostream>

using namespace std;

int main(){
    int p;
    cin >> p;
    while(p --> 0){
        int a;
        cin >> a;
        int res = 0;
        for(int i = 5; i < a; i *= 5){
            res += a/i;
        }
        cout << res << endl; 
    }
}
#include<iostream>
#include<stack>

using namespace std;

void solve(string s){
    stack<char> brack;
    for(auto a : s){
        if(a == '(' or a == '[' or a == '{'){
            brack.push(a);
        }
        else{
            if(brack.empty()){
                cout << "NO" << endl;
                return;
            }
            if(brack.top() == '{' and a == '}')
                brack.pop();
            else if(brack.top() == '[' and a == ']')
                brack.pop();
            else if(brack.top() == '(' and a == ')')
                brack.pop();
            else{
                cout << "NO" << endl;
                return;
            }
        }
    }
    if(brack.empty()){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
    }
    return ;
}

int main(){
    int n;
    cin >> n;
    while(n --> 0){
        string s;
        cin >> s;
        solve(s);
    }
    return 0;
}
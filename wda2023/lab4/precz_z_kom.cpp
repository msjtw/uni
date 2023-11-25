#include<iostream>

using namespace std;

int main(){
    bool block = false;
    bool lane = false;
    bool inq = false;
    //bool skip = false;

    char a, b = 'a', c = 's';

    string res = "";

    while(cin.get(a)){
        if(lane){
            if(a == '\n'){
                lane = false;
                res += a;
            }
        }
        else if(block){
            if(a == '/' and b == '*'){
                block = false;
                a = 'd';
            }
        }
        else if(inq){
            res += a;
            if((a == '"' and b != '\\') or (a == '"' and b == '\\' and c == '\\')){
                inq = false;
            }
        }
        else{
            if(a == '"')
                inq = true;
            if(a == '*' and b == '/'){
                block = true;
                res.erase(res.end()-1);
            }
            else if(a == '/' and b == '/'){
                lane = true;
                res.erase(res.end()-1);
            }
            else{
                res += a;
            }
        }
        c = b;
        b = a;
    }
    //res += a;
    cout << res;
    return 0;
}
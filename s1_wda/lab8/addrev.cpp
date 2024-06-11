#include<iostream>
#include<algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    while(n --> 0){
        string a, b;
        cin >> a >> b;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        string c = to_string(stoi(a)+stoi(b));
        reverse(c.begin(), c.end());
        while(c[0] == '0')
            c.erase(c.begin());
        cout << c << endl;
    }
    return 0;
}
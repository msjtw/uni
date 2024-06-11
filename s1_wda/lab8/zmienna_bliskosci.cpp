#include<iostream>

using namespace std;

const int SIZE = 30007;
int len[2][SIZE];

int lcs(string a, string b){
    for(int i = 0; i <= a.length(); i++){
        for(int k = 0; k <= b.length(); k++){
            if(i == 0 || k == 0){
                len[i%2][k] = 0;
            }
            else if(a[i-1] == b[k-1]){
                len[i%2][k] = len[(i-1)%2][k-1] + 1;
            }
            else{
                len[i%2][k] = max(len[(i-1)%2][k], len[i%2][k-1]);
            }
        }
    }

    return len[a.length()%2][b.length()];
}

int main(){
    int n, m;
    cin >> n >> m;
    string a, b;
    cin >> a >> b;
    double l = a.length() + b.length();
    double llccss = lcs(a,b);
    if(l == 0)
        cout << 0;
    else
        cout << llccss*2/l;
    return 0;
}
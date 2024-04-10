#include <iostream>
#include <algorithm>

using namespace std;

typedef long long int ll;

const int MOD = 998244353;

void mul(ll m1[][2], ll m2[][2]){
    ll res[2][2];

    for (int i = 0; i < 2; i++) { 
        for (int j = 0; j < 2; j++) { 
            res[i][j] = 0; 
  
            for (int k = 0; k < 2; k++) { 
                res[i][j] += m1[i][k] * m2[k][j]; 
            } 
  
        } 
    }
    // cout << res[0][0] << " " << res[0][1] << endl;
    // cout << res[1][0] << " " << res[1][1] << endl << endl;
    m1[0][0] = res[0][0] % MOD;
    m1[0][1] = res[0][1] % MOD;
    m1[1][0] = res[1][0] % MOD;
    m1[1][1] = res[1][1] % MOD;
}

int main(){
    int n;
    cin >> n;
    while(n --> 0){
        ll m[2][2] ={{1,0},{0,1}}; 
        ll m_pow[2][2] ={{1,1},{1,0}}; 
        string s;
        cin >> s;
        reverse(s.begin(), s.end());
        for(int i =0 ; i < s.size(); i++){
            if(s[i] == '1'){
                // cout << i << endl;
                mul(m,m_pow);
            }
            mul(m_pow,m_pow);
            // cout << m[0][0] << " " << m[0][1] << endl;
            // cout << m[1][0] << " " << m[1][1] << endl << endl;
        }
        cout << m[1][0] << endl;
        //cout << (m[1][0] + m[1][1]) % MOD << endl;
    }
}
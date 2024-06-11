#include<iostream>

using namespace std;

const int MX = 1e7;

typedef long long int ll;

int small_fact[MX];

ll res[MX];

int main(){
    for(int i = 2; i < MX; i++){
        if(small_fact[i] == 0){
            for(int k = i; k < MX; k+= i){
                if(small_fact[k] == 0)
                    small_fact[k] = i;
            }
        }
    }
    for(int i = 2; i < MX; i++){
        res[i] = res[i-1]+small_fact[i];
    }

    int t;
    cin >> t;
    while(t --> 0){
        int a;
        cin >> a;
        cout << res[a] << endl;
    }
    return 0;
}
#include<iostream>

using namespace std;

int res[1007][1007] {};


int main(){
    int n, k, q;
    cin >> n >> k >> q;

    for(int i = 0; i <= k; i++){
        res[1][i] = 1;
    }

    for(int i = 2; i <= 1000; i++){
        for(int r = 0; r <= k; r++){
            if(r == 0){
                res[i][r] = res[i-1][r] + res[i-1][r+1];
            }
            else if(r == k){
                res[i][r] = res[i-1][r-1] + res[i-1][r];
            }
            else{
                res[i][r] = res[i-1][r-1] + res[i-1][r] + res[i-1][r+1];
            }
            res[i][r] = res[i][r]%q;
        }
    }

    while(n --> 0){
        int d;
        cin >> d;
        int sum = 0;
        for(int i = 0 ; i <= k; i++){
            sum = (sum + res[d][i])%q;
        }
        cout << sum << " ";
    }

    return 0;
}
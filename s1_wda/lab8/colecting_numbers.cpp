#include<iostream>

using namespace std;

const int SIZE = 107;

int val[SIZE][SIZE] {};
int res[SIZE][SIZE] {};
int n;

int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int k = 0; k < n; k++){
            cin >> val[i+1][k+1];
        }
    }

    for(int i = 1; i <= n; i++){
        for(int k = 1; k <= n; k++){
            res[i][k] = max(res[i-1][k], res[i][k-1])+val[i][k];
        }
    }

    cout << res[n][n];

    return 0;
}
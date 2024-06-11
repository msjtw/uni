#include <iostream>
#include <vector>

using namespace std;

int main(){
    int p;
    cin >> p;
    while(p-->0){
        int n, x;
        vector <int> arr;
        cin >> n >> x;
        arr.push_back(0);
        for(int i = 0 ; i < n ;i++){
            int a;
            cin >> a;
            arr.push_back(a);
        }
        int dp[2007][2007] {};
        for(int i = 1; i <= n; i++){
            for(int k = 1; k <= x; k++){
                dp[i][k] = dp[i-1][k];
                if(k - arr[i] >= 0){
                    dp[i][k] = max(dp[i][k], dp[i][k-arr[i]] + arr[i]);
                }
            }
        }
        cout << dp[n][x] << endl;
    }
    return 0;
}
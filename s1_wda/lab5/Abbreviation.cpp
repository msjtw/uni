#include<iostream>
#include<cctype>

using namespace std;

int main(){
    int p;
    cin >> p;
    while(p-->0){
        string a, b;
        bool dp[1007][1007] {};
        cin >> a >> b;
        if(a.length() < b.length()){
            cout << "NO" << endl;
            continue;
        }
        for(int i = 0; i < a.length() and islower(a[i]); i ++){
                dp[0][i+1] = true;
        }
        dp[0][0] = true;
        for(int ii = 0; ii < b.length(); ii++){
            bool nie = false;
            for(int kk = 0; kk < a.length(); kk++){
                int i = ii +1;
                int k = kk +1;
                if(isupper(a[kk])){
                    if(b[ii] != a[kk]){
                        dp[i][k] = false;
                        //nie = true;
                    }
                    else
                        dp[i][k] = dp[i-1][k-1];
                }
                else{
                    if(toupper(a[kk]) == b[ii]){
                        dp[i][k] = dp[i-1][k-1] | dp[i][k-1];
                    }
                    else{
                        dp[i][k] = dp[i][k-1];
                    }
                }
                if(!dp[i][k] and dp[i][k-1])
                    nie = true;
            }
            for(int iii = 0; iii <= b.length(); iii++){
                for(int kki = 0; kki <= a.length(); kki++){
                    cout << dp[iii][kki] << " ";
                }
                cout << endl;
            }
            cout <<  endl;
        }

        // for(int ii = 0; ii <= b.length(); ii++){
        //     for(int kk = 0; kk <= a.length(); kk++){
        //         cout << dp[ii][kk] << " ";
        //     }
        //     cout << endl;
        // }

        cout <<( dp[b.length()][a.length()] ? "YES" : "NO" )<< endl;
    }
}
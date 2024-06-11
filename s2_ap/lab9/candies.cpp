#include<iostream>

using namespace std;

const int MX = 1e5+7;

int can[MX];
int res[MX];

int main(){
    int n;
    cin >> n;
    for(int i = 0 ; i  < n; i++){
        cin >> can[i];
    }

    res[0] = 1;
    for(int i = 1 ; i < n; i++){
        if(can[i-1] < can[i]){
            res[i] = res[i-1] +1;
        }
        else{
            res[i] = 1;
        }
    }

    for(int i = n-2; i >= 0; i--){
        if(can[i] > can[i+1]){
            res[i] = max(res[i], res[i+1]+1);
        }
        else{
            res[i] = max(res[i], 1);
        }
    }

    long long int ret = 0;
    for(int i = 0 ; i < n; i++){
        ret += res[i];
    }

    cout << ret;

    return 0;
}
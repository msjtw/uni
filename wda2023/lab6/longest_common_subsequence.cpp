#include<iostream>
#include<stack>

using namespace std;

const int SIZE = 107;

int arr[SIZE][SIZE] {};

int seq1[SIZE] {};
int seq2[SIZE] {};

int main(){
    int n, m;
    cin >> n >> m;

    for(int i = 1; i <= n; i++){
        cin >> seq1[i];
    }
    for(int i = 1; i <= m; i++){
        cin >> seq2[i];
    }

    for(int i = 1; i <= n; i++){
        for(int k = 1; k <= m; k++){
            if(seq1[i] == seq2[k]){
                arr[i][k] = arr[i-1][k-1] + 1;
            }
            else{
                arr[i][k] = max(arr[i][k-1], arr[i-1][k]);
            }
        }
    }

    // for(int i = 0; i <= n; i++){
    //     for(int k = 0; k <= m; k++){
    //         cout << arr[i][k] << " ";
    //     }
    //     cout << endl;
    // }

    stack<int> res;

    int ii = n;
    int kk = m;
    while(arr[ii][kk] != 0){
        if(seq1[ii] == seq2[kk]){
            res.push(seq1[ii]);
            ii--;
            kk--;
        }
        else{
            if(arr[ii-1][kk] > arr[ii][kk-1]){
                ii--;
            }
            else{
                kk--;
            }
        }
    }

    while(!res.empty()){
        cout << res.top() << " ";
        res.pop();
    }

    return 0;
}
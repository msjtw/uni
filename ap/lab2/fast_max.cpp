#include <iostream>

using namespace std;

const int base = 2<<18;

int arr[2*base];

void insert(int arr[], int idx, int val){
    idx += base;
    arr[idx] = val;
    while(idx > 0){
        idx >>= 1;
        arr[idx] = max(arr[2*idx], arr[2*idx+1]);
    }
}

int querry(int arr[], int p, int q){
    int ret = 0;
    p += base -1;
    q += base +1;
    while(p/2 != q/2){
        if(p % 2 == 0){
            ret = max(ret, arr[p+1]);
        }
        if(q % 2 == 1){
            ret = max(ret, arr[q-1]);
        }
        p >>= 1;
        q >>= 1;
    }
    return ret;
}

int main(){
    int n, r;
    cin >> n >> r;
    while(r --> 0){
        int type, a, b;
        cin >> type >> a >> b;
        if(type == 1){
            insert(arr, a, b);
        }
        else{
            cout << querry(arr, a, b) << "\n";
        }
    }
    return 0;
}
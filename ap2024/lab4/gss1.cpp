#include <iostream>

using namespace std;

typedef long long int ll;

ll oo = __INT64_MAX__;

struct node{
    ll ssum = -oo;
    ll prfx = -oo;
    ll sufx = -oo;
    ll tsum = 0;
};

const int BASE = 1<<16;

node arr[2*BASE];

void insert(node arr[], int idx, int val){
    idx += BASE;
    arr[idx] = {val, val, val, val};
    while(idx > 0){
        idx >>= 1;
        int i = idx;
        int ii = 2*idx;
        arr[i].prfx = max(arr[ii].prfx, arr[ii].tsum+arr[ii+1].prfx);
        arr[i].sufx = max(arr[ii+1].sufx, arr[ii].sufx+arr[ii+1].tsum);
        arr[i].tsum = arr[ii].tsum + arr[ii+1].tsum;

        arr[i].ssum = max(max(max(arr[i].tsum, arr[ii].sufx+arr[ii+1].prfx), arr[ii].ssum), arr[ii+1].ssum);
        arr[i].ssum = max(arr[i].ssum, arr[i].sufx);
        arr[i].ssum = max(arr[i].ssum, arr[i].prfx);
    }
}

ll query(node arr[], int p, int q){
    node ret1;
    node ret2;
    p += BASE -1;
    q += BASE +1;
    while(p/2 != q/2){
        if(p % 2 == 0){
            node val;
            val.prfx = max(ret1.prfx, ret1.tsum + arr[p+1].prfx);
            val.sufx = max(arr[p+1].sufx, ret1.sufx + arr[p+1].tsum);
            val.tsum = ret1.tsum + arr[p+1].tsum;
            //val.ssum = max(ret1.sufx+arr[p+1].prfx, max(ret1.ssum, arr[p+1].ssum));

            val.ssum = max(max(max(val.ssum, val.sufx+arr[p+1].prfx), val.ssum), arr[p+1].ssum);
            val.ssum = max(val.ssum, val.sufx);
            val.ssum = max(val.ssum, val.prfx);
            ret1 = val;
        }
        if(q % 2 == 1){
            node val;
            val.prfx = max(arr[q-1].prfx, arr[q-1].tsum + ret2.prfx);
            val.sufx = max(ret2.sufx, arr[q-1].sufx+ret2.tsum);
            val.tsum = ret2.tsum + arr[q-1].tsum;
            //val.ssum = max(ret2.prfx+arr[q-1].sufx, max(ret2.ssum, arr[q-1].ssum));

            val.ssum = max(max(max(val.ssum, arr[q-1].sufx+val.prfx), val.ssum), arr[q-1].ssum);
            val.ssum = max(val.ssum, val.sufx);
            val.ssum = max(val.ssum, val.prfx);
            ret2 = val;
        }
        p >>= 1;
        q >>= 1;
    }
    ll ret = -__INT64_MAX__;
    ret = max(ret, ret1.ssum);
    ret = max(ret, ret2.ssum);
    ret = max(ret, ret1.ssum+ret2.prfx);
    return ret;
}

int main(){
    int n;
    cin >> n;
    for(int i = 0 ; i < n; i++){
        int a;
        cin >> a;
        insert(arr, i, a);
    }
    cin >> n;
    while(n --> 0){
        int a, b;
        cin >> a >> b;
        cout << query(arr, a-1, b-1) << endl;
    }
}
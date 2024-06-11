#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

typedef pair<int,int> pii;
typedef long long int ll;

vector<pii> arr;

const ll base = 2<<17;

ll vals[2*base];
ll res[50007];

void insert(ll arr[], ll idx, ll val){
    idx += base;
    arr[idx] = val;
    while(idx > 0){
        idx >>= 1;
        arr[idx] = arr[2*idx] + arr[2*idx+1];
    }
}

ll querry(ll arr[], ll p, ll q){
    ll ret = 0;
    p += base -1;
    q += base +1;
    while(p/2 != q/2){
        if(p % 2 == 0){
            ret += arr[p+1];
        }
        if(q % 2 == 1){
            ret += arr[q-1];
        }
        p >>= 1;
        q >>= 1;
    }
    return ret;
}

int main(){
    ll n;
    cin >> n;
    for(ll i = 1; i <= n; i++){
        ll a;
        cin >> a;
        arr.push_back({a, i});
    }

    sort(arr.begin(), arr.end());

    ll total = (arr[0].first-1)*n;
    ll last = 0;
    ll add = n;
    queue<ll> rem;

    for(ll i = 0; i < n; i++){
        pii curr = arr[i];
        if(i > 0 and arr[i].first > arr[i-1].first){
            while(!rem.empty()){
                insert(vals, rem.front(), 1);
                rem.pop();
            }
            total += add;
            last = arr[i-1].first;
            add = n - i;
            total += (curr.first-1-last)*add;
        }
        ll tmp = querry(vals, 0, curr.second);
        res[curr.second] = total + curr.second - tmp;
        rem.push(curr.second);
    }

    for(ll i = 1; i <= n; i++){
        cout << res[i] << "\n";
    }

    return 0;
}
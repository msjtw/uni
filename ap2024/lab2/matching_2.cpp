#include<iostream>
#include<vector>
#include<set>

using namespace std;

const int MX = 100007;

vector<int> adj[MX];
int vis[MX];
int maching[MX];

bool mat(int vis[], int x){
    if(vis[x])
        return 0;
    vis[x] = true;

    for(int u : adj[x]){
        if(maching[u] == -1 or mat(vis, maching[u])){
            maching[u] = x;
            return true;
        }
    }

    return false;
}

void zero(int arr[], int n, int val){
    for(int i = 0 ; i < n; i++){
        arr[i] = val;
    }
}

int main(){
    int cows, bulls, m;
    cin >> cows >> bulls >> m;

    for(int i = 0 ; i < m; i++){
        int a, b;
        cin >> a >> b;
        b += cows;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    zero(maching, MX, -1);

    if(cows < bulls){
        for(int i = 1 ; i <= cows; i++){
            zero(vis, MX, 0);
            mat(vis, i);
        }
    }
    else{
        for(int i = cows+1 ; i <= bulls+cows; i++){
            zero(vis, MX, 0);
            mat(vis, i);
        }
    }

    int res= 0;

    for(int i = 0 ; i <= cows+bulls; i++){
        //cout << maching[i] << endl;
        if(maching[i] > 0){
            res++;
        }
    }

    cout << res;

    return 0;
}
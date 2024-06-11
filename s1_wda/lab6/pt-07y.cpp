#include<iostream>
#include<vector>

using namespace std;

const int SIZE = 10007;

vector<int>adj[SIZE];
int vis[SIZE];

void dfs(int n){
    if(vis[n])
        return;
    vis[n] = 1;
    for(auto v : adj[n]){
         dfs(v);
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    int start;
    for(int i =0; i < m; i++){
        int a, b;
        cin >> a >> b;
        start = a;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }


    dfs(start);
    int all = 0;
    for(int i = 0; i < SIZE; i++){
        all += vis[i];
    }
    cout << all;
    cout << (n == m+1 and all == n ? "YES" : "NO");

    return 0;
}
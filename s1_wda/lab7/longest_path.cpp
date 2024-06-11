#include<iostream>
#include<vector>

using namespace std;

const int SIZE = 1e4+7;
vector <int> adj[SIZE];
vector <int> leafs;
int n;

bool vis[SIZE] {};

int dfs(int x, int r){
    int res = r;
    vis[x] = true;
    for(int v : adj[x]){
        if(!vis[v]){
            res = max(res, dfs(v, r)+1);
        }
    }
    return res;
}

int main(){
    cin >> n;
    for(int i = 0; i < n-1; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for(int i = 0; i < n ; i++){
        if(adj[i].size() == 1){
            leafs.push_back(i);
        }
    }

    int res = 0;

    for(int leaf : leafs){
        for(int i = 0; i < SIZE; i++){
            vis[i] = false;
        }
        res = max(res, dfs(leaf, 0));
    }

    cout << res;

    return 0;
}
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

const int MX = 207;

int flow[MX][MX];
int used[MX][MX];

vector<int> adj[MX];
vector<int> radj[MX];

bool bfs(int s, int lvl[], const int n){
    queue<int> q;
    q.push(1);
    lvl[1] = 1;
    while(!q.empty()){
        int p = q.front();
        q.pop();
        for(int v : adj[p]){
            if(lvl[v] == 0 and flow[p][v] - used[p][v] > 0){
                lvl[v] = lvl[p]+1;
                q.push(v);
            }
        }
        for(int v : radj[p]){
            if(lvl[v] == 0 and used[v][p] > 0){
                lvl[v] = lvl[p]+1;
                q.push(v);
            }
        }
    }
    return lvl[n] > 0;
}

int dfs(int x, int val, const int lvl[], const int n){
    if(x == n)
        return val;
    for(int v : adj[x]){
        if(lvl[v] == lvl[x]+1){
            int r = dfs(v, min(val, flow[x][v]-used[x][v]), lvl, n);
            if(r > 0){
                used[x][v] += r;
                return r;
            }
        }
    }
    for(int v : radj[x]){
        if(lvl[v] == lvl[x]+1){
            int r = dfs(v, min(val, used[v][x]), lvl, n);
            if(r > 0){
                used[v][x] -= r;
                return r;
            }
        }
    }
    return 0;
}

int main(){
    ios_base::sync_with_stdio(false);

    int p;
    cin >> p;
    while(p --> 0){
        for(int i = 0; i < MX; i++){
            for(int k = 0; k < MX; k++){
                flow[i][k] = 0;
                used[i][k] = 0;
            }
            adj[i].clear();
            radj[i].clear();
        }

        int n;
        cin >> n;
        for(int i = 1; i < n; i++){
            int k;
            cin >> k;
            while(k --> 0){
                int a;
                cin >> a;
                adj[i].push_back(a);
                radj[a].push_back(i);
                flow[i][a] = MX;
                if(i == 1 || a == n){
                    flow[i][a] = 1;
                }
            }
        }

        int lvl[MX];

        int res = 0;

        while(bfs(1, lvl, n)){
            res += dfs(1, __INT_MAX__, lvl, n);
            for(int i = 0 ; i < MX; i++)
                lvl[i] = 0;
        }
        cout << res << " ";

    }
    return 0;
}
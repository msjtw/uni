#include<iostream>
#include<vector>
#include<queue>

using namespace std;
 
typedef long long int ll;
 
const int MX = 207;

ll flow[MX][MX];
ll used[MX][MX];
 
bool vis[MX];
 
bool bfs(int s, const vector<int> adj[], const vector<int> radj[], int lvl[], const int n){
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
 
int dfs(int x, ll val, const vector<int> adj[], const vector<int> radj[], const int lvl[], const int n){
    //cout << x << " ";
    vis[x] = true;
    if(x == n){
        return val;
    }
    for(int v : adj[x]){
        if(lvl[v] == lvl[x]+1 and flow[x][v] - used[x][v] > 0 and !vis[v]){
            int r = dfs(v, min(val, flow[x][v]-used[x][v]), adj, radj, lvl, n);
            if(r > 0){
                used[x][v] += r;
                return r;
            }
        }
    }
    for(int v : radj[x]){
        if(lvl[v] == lvl[x]+1 and used[v][x] > 0 and !vis[v]){
            int r = dfs(v, min(val, used[v][x]), adj, radj, lvl, n);
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
    cin.tie(NULL);
    cout.tie(NULL);

    int p;
    cin >> p;
    while(p --> 0){
        for(int i = 0; i < MX; i++){
            vis[i] = false;
            for(int k = 0; k < MX; k++){
                flow[i][k] = 0;
                used[i][k] = 0;
            }
        }
        vector<int> adj[MX];
        vector<int> radj[MX];
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
    
        long long int res = 0;
    
        while(bfs(1, adj, radj, lvl, n)){
            res += dfs(1, __INT_MAX__, adj, radj, lvl, n);
            for(int i = 0 ; i < MX; i++){
                vis[i] = false;
                lvl[i] = 0;
            }
        }
        cout << res << "\n";

    }
    return 0;
}
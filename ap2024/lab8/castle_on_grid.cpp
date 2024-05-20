#include<iostream>
#include<map>
#include<queue>

using namespace std;

typedef pair<int,int> pii;

const int MX = 107;

string grid[MX];

map<pii, vector<pii>> adj;
map<pii, bool> proc;
map<pii, int> dist;

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> grid[i];
    }
    for(int i = 0 ; i < n; i++){
        for(int k = 0; k < n; k++){
            pii start = {i, k};
            proc[start] = false;
            dist[start] = __INT_MAX__;
            for(int j = i-1; j >= 0 and grid[j][k] != 'X'; j--){
                adj[start].push_back({j,k});
            }
            for(int j = i+1; j < n and grid[j][k] != 'X'; j++){
                adj[start].push_back({j,k});
            }
            for(int j = k-1; j >= 0 and grid[i][j] != 'X'; j--){
                adj[start].push_back({i,j});
            }
            for(int j = k+1; j < n and grid[i][j] != 'X'; j++){
                adj[start].push_back({i,j});
            }
        }
    }

    pii start, goal;
    cin >> start.first >> start.second >> goal.first >> goal.second;
    
    queue<pii> q;
    dist[start] = 0;
    q.push(start);
    while(!q.empty()){
        pii p = q.front();
        q.pop();
        if(proc[p])
            continue;
        proc[p] = true;
        for(auto u : adj[p]){
            if(dist[p]+1 < dist[u]){
                dist[u] = dist[p]+1;
                q.push(u);
            }
        }
    }

    cout << dist[goal];

    return 0;
}
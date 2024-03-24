#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

const int MX = 3007;

typedef pair<int, int> pii;

vector<pii> adj[MX];
bool vis[MX];

int main(){
    int n, m;
    int start;
    cin >> n >> m;
    for(int i = 0 ; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }
    start = 1;
    cin >> start;


    int res = 0;

    priority_queue<pii> q;
    q.push({0,start});
    while(!q.empty()){
        int a = q.top().second;
        int wz = q.top().first;
        q.pop();
        if(vis[a])
            continue;
        vis[a] = true;
        res -= wz;
        for(auto u : adj[a]){
            int b, w;
            tie(b, w) = u;
            q.push({-w, b});
        }
    }

    cout << res;

    return 0;
}
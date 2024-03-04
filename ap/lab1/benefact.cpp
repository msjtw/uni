#include<iostream>
#include<vector>
#include<tuple>

using namespace std;

const int MX = 2e5+7;

vector<pair<int, int>> adj[MX];

int dist[MX];

int furth = 1;
int maxd;

void dfs(int a, int e){
    for(auto v : adj[a]){
        int b, d;
        tie(b, d) = v;
        if(b != e){
            dist[b] = dist[a]+d;
            if(dist[b] > maxd){
                maxd = dist[b];
                furth = b;
            }
            dfs(b, a);
        }
    }
}

int main(){
    int p;
    cin >> p;
    while(p --> 0){
        for(int i = 0; i < MX; i++){
            adj[i].clear();
            dist[i] = 0;
            furth = 1;
            maxd = 0;
        }
        int n;
        cin >> n;
        for(int i = 1; i < n; i++){
            int a, b, w;
            cin >> a >> b >> w;
            adj[a].push_back({b, w});
            adj[b].push_back({a, w});
        }

        dfs(furth, 0);
        maxd = 0;
        for(int i = 0; i < MX; i++)
            dist[i] = 0;
        dfs(furth, 0);
        
        cout << maxd << '\n';
    }
    return 0;
}
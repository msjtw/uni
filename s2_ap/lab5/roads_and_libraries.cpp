#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long int ll;

const int MX = 1e5+7;

int main(){
    int p;
    cin >> p;
    while(p --> 0){
        ll n, m, c_road, c_lib;
        cin >> n >> m >> c_lib >> c_road;
        vector<int> adj[MX];
        for(int i = 0; i < m; i++){
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        ll libs = 0;
        ll roads = 0;
        bool vis[MX] = {};
        for(int i = 1; i <= n; i++){
            if(vis[i])
                continue;
            libs++ ;
            queue<int> q;
            q.push(i);
            vis[i] = true;
            while(!q.empty()){
                int a = q.front();
                q.pop();
                for(int b : adj[a]){
                    if(!vis[b]){
                        vis[b] = true;
                        roads++;
                        q.push(b);
                    }
                }
            }
        }
        //cout << roads << " " << libs << endl;
        cout << min(n*c_lib, (roads*c_road)+(libs*c_lib)) << endl;
    }
    return 0;
}
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

const int MX = 2007;

int main(){
    int p;
    cin >> p;
    for(int pp = 0; pp < p; pp++){
        vector<int> adj[MX];
        int n, m;
        cin >> n >> m;
        for(int i = 0; i < m; i++){
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        bool popsuted = false;
        int color[MX] {};
        int proc[MX] {};
        for(int i = 1; i < n; i++){
            if(proc[i])
                continue;
            queue<int>q; 
            q.push(i);
            color[i] = 1;
            while(!q.empty() and !popsuted){
                int p = q.front();
                q.pop();
                if(proc[p])
                    continue;
                proc[p] = true;

                int c = -1*color[p];
                for(int u : adj[p]){
                    if(color[u] == color[p]){
                        popsuted = true;
                    }
                    color[u] = c;
                    q.push(u);
                }
            }
        }
        cout << "Scenario #" << pp+1 << ":" << endl;
        if(popsuted){
            cout << "Suspicious bugs found!" << endl;
        }
        else{
            cout << "No suspicious bugs found!" << endl;
        }
    }
    return 0;
}

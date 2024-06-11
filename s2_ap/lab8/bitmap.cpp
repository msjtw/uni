#include <iostream>
#include <queue>

using namespace std;

typedef long long int ll;
typedef pair<int ,int> pii;

const int MX = 200;

int main(){
    int t;
    cin >> t;
    while(t --> 0){
        queue<pii> q;
        int n, m;
        cin >> n >> m;
        int dist[MX][MX];
        for(int i = 0 ; i < MX; i++){
            for(int k = 0; k < MX; k++){
                dist[i][k] = -1;
            }
        }
        for(int i = 0; i < n; i++){
            string s;
            cin >> s;
            for(int k =0; k < m; k++){
                if(s[k] == '1'){
                    dist[i][k] = 0;
                    q.push({i,k});
                }
            }
        }

        vector<pii> dir = {{-1,0},{1,0},{0,-1},{0,1}};

        while(!q.empty()){
            pii a = q.front();
            q.pop();
            for(pii next : dir){
                int x = a.first + next.first;
                int y = a.second + next.second;
                if(x < 0 or y < 0 or x >= n or y >= m)
                    continue;;
                if(dist[x][y] == -1){
                    dist[x][y] = dist[a.first][a.second] +1;
                    q.push({x,y});
                }
            }
        }

        for(int i = 0 ; i < n; i++){
            for(int k = 0 ; k < m; k++){
                cout << dist[i][k] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
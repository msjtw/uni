#include<iostream>
#include<queue>
#include<cassert>

using namespace std;

struct poz{
    int x;
    int y;
};

const int SIZE = 1e3+7;
int c, r;
string map[SIZE];

poz fur;

int bfs(poz start){
    int res = 0;
    bool vis[SIZE][SIZE] {};
    int dist[SIZE][SIZE] {};
    queue<poz> q;
    q.push(start);
    vis[start.x][start.y] = true;
    while(!q.empty()){
        poz p = q.front();
        q.pop();
        if(p.x > 0 and map[p.x-1][p.y] == '.'){
            if(!vis[p.x-1][p.y]){
                poz n_poz = {p.x-1,p.y};
                vis[n_poz.x][n_poz.y] = true;
                dist[n_poz.x][n_poz.y] = dist[p.x][p.y] +1;
                if(dist[n_poz.x][n_poz.y] > res){
                    res = dist[n_poz.x][n_poz.y];
                    fur = n_poz;
                }
                q.push(n_poz);
            }
        }
        if(p.x < r-1 and map[p.x+1][p.y] == '.'){
            if(!vis[p.x+1][p.y]){
                poz n_poz = {p.x+1,p.y};
                vis[n_poz.x][n_poz.y] = true;
                dist[n_poz.x][n_poz.y] = dist[p.x][p.y] +1;
                if(dist[n_poz.x][n_poz.y] > res){
                    res = dist[n_poz.x][n_poz.y];
                    fur = n_poz;
                }
                q.push(n_poz);
            }
        }
        if(p.y > 0 and map[p.x][p.y-1] == '.'){
            if(!vis[p.x][p.y-1]){
                poz n_poz = {p.x,p.y-1};
                vis[n_poz.x][n_poz.y] = true;
                dist[n_poz.x][n_poz.y] = dist[p.x][p.y] +1;
                if(dist[n_poz.x][n_poz.y] > res){
                    res = dist[n_poz.x][n_poz.y];
                    fur = n_poz;
                }
                q.push(n_poz);
            }
        }
        if(p.y < c-1 and map[p.x][p.y+1] == '.'){
            if(!vis[p.x][p.y+1]){
                poz n_poz = {p.x,p.y+1};
                vis[n_poz.x][n_poz.y] = true;
                dist[n_poz.x][n_poz.y] = dist[p.x][p.y] +1;
                if(dist[n_poz.x][n_poz.y] > res){
                    res = dist[n_poz.x][n_poz.y];
                    fur = n_poz;
                }
                q.push(n_poz);
            }
        }
    }
    return res;
}

int main(){
    int t;
    cin >> t;
    while(t-->0){
        cin >> c >> r;
        for(int i = 0; i < r; i++){
            cin >> map[i];
        }
        poz start;
        for(int i = 1; i < r-1; i++){
            for(int k = 1; k < c-1; k++){
                if(map[i][k] == '.'){
                    start = {i, k};
                    goto rome;
                }
            }
        }
        rome:
        // priority_queue<int> q;
        // if(map[start.x-1][start.y] == '.'){
        //     q.push(bfs({start.x-1,start.y}));
        // }
        // if(map[start.x+1][start.y] == '.'){
        //     q.push(bfs({start.x+1,start.y}));
        // }
        // if(map[start.x][start.y-1] == '.'){
        //     q.push(bfs({start.x,start.y-1}));
        // }
        // if(map[start.x][start.y+1] == '.'){
        //     q.push(bfs({start.x,start.y+1}));
        // }
        // int add = min(int(q.size()),2);
        // q.push(0);
        // q.push(0);

        // res += q.top();
        // q.pop();
        // res += q.top();
        int res = 0;
        int trash = bfs(start);
        // cout << fur.x << " " << fur.y << endl;
        res = bfs(fur);
        // cout << trash << endl;
        //cout << fur.x << " " << fur.y << endl;
        cout << "Maximum rope length is " << res <<  "." << endl;
    }    
    return 0;
}
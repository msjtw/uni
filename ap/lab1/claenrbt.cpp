#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
#include <map>

using namespace std;

typedef pair<int,int> pii;

const int MX = 22;

int n, m;

// int bfs(const char map[][27], const vector<pair<int,int>> &dirt, const pair<int,int> &robot){
//     int ret = 0;

//     for(int i = 0 ; i < dirt.size(); i++){
//         pair<int, int> start;
//         if(i == 0)
//             start = robot;
//         else
//             start = dirt[i-1];
//         pair<int, int> end = dirt[i];
//         bool vis[27][27];
//         for(int i = 0; i < 27; i++){
//             for(int k = 0; k < 27; k++){
//                 vis[i][k] = false;
//             }
//         }
//         int dist = 0;
//         bool found = false;
//         queue<tuple<int,int, int>> q;
//         q.push({start.first, start.second, 0});
//         while(!q.empty()){
//             auto p = q.front();
//             q.pop();
//             int x, y, d;
//             tie(x, y ,d) = p;
//             if(make_pair(x, y) == end){
//                 dist += d;
//                 found = true;
//                 break;
//             }
//             int a, b;
//             tie(a, b) = make_tuple(x-1, y);
//             if(a > 0 and map[a][b] == '.' and !vis[a][b]){
//                 vis[a][b] = true;
//                 q.push({a, b, d+1});
//             }
//             tie(a, b) = make_tuple(x+1, y);
//             if(a <= n and map[a][b] == '.' and !vis[a][b]){
//                 vis[a][b] = true;
//                 q.push({a, b, d+1});
//             }
//             tie(a, b) = make_tuple(x, y-1);
//             if(b > 0 and map[a][b] == '.' and !vis[a][b]){
//                 vis[a][b] = true;
//                 q.push({a, b, d+1});
//             }
//             tie(a, b) = make_tuple(x, y+1);
//             if(b <= m and map[a][b] == '.' and !vis[a][b]){
//                 vis[a][b] = true;
//                 q.push({a, b, d+1});
//             }
//         }
//         if(!found){
//                 ret = -(__INT_MAX__-10);
//             }
//         else{
//             ret += dist;
//         }
//     }
//     return ret;
// }



int bfs(int adj[][MX], vector<int> &points){
    int ret = 0;
    for(int i = 0 ; i < points.size()-1; i++){
        ret += adj[points[i]][points[i+1]];
        if(ret < 0)
            return -1;
    }
    return ret;
}

void bfs2(int adj[][MX], char room[][MX], map<pii, int> &dirt, pii dirt2[], const int size){
    for(int i = 0 ; i < size; i++){
        bool vis[MX][MX];
        for(int i = 0 ; i < MX; i++){
            for(int k = 0 ; k < MX; k++){
                vis[i][k] = false;
            }
        }
        queue<tuple<int, int, int>> q;
        q.push({dirt2[i].first, dirt2[i].second, 0});
        vis[dirt2[i].first][dirt2[i].second] = true;
        while(!q.empty()){
            auto p = q.front();
            q.pop();
            int x, y, d;
            tie(x, y, d) = p;
            if(dirt.count({x, y}) > 0){
                adj[dirt[dirt2[i]]][dirt[{x, y}]] = d;
            }
            int a, b;
            tie(a, b) = make_tuple(x-1, y);
            if(a > 0 and room[a][b] == '.' and !vis[a][b]){
                vis[a][b] = true;
                q.push({a, b, d+1});
            }
            tie(a, b) = make_tuple(x+1, y);
            if(a <= n and room[a][b] == '.' and !vis[a][b]){
                vis[a][b] = true;
                q.push({a, b, d+1});
            }
            tie(a, b) = make_tuple(x, y-1);
            if(b > 0 and room[a][b] == '.' and !vis[a][b]){
                vis[a][b] = true;
                q.push({a, b, d+1});
            }
            tie(a, b) = make_tuple(x, y+1);
            if(b <= m and room[a][b] == '.' and !vis[a][b]){
                vis[a][b] = true;
                q.push({a, b, d+1});
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(true){
        cin >> m >> n;
        if(n == 0 and m == 0)
            break;
        char room[MX][MX];
        int adj[MX][MX];
        for(int i = 0; i < MX; i++){
            for(int k = 0; k < MX; k++){
                adj[i][k] = -__INT_MAX__;
            }
        }
        map<pii, int> dirt;
        pii dirt2[MX];
        int d_num = 1;
        for(int i = 1 ; i <= n; i++){
            for(int k = 1 ; k <= m; k++){
                cin >> room[i][k];
                if(room[i][k] == '*'){
                    dirt[{i,k}] = d_num;
                    dirt2[d_num] = {i,k};
                    d_num++;
                    room[i][k] = '.';
                }
                if(room[i][k] == 'o'){
                    dirt[{i,k}] = 0;
                    dirt2[0] = {i,k};
                    room[i][k] = '.';
                }
            }
        }

        bfs2(adj, room, dirt, dirt2, d_num);

        // for(int i = 0; i <= 10; i++){
        //     for(int k = 0; k <= 10; k++){
        //         cout << adj[i][k] << " ";
        //     }
        //     cout << endl;
        // }

        int res = __INT_MAX__;
        vector<int> points;
        for(int i = 0; i < d_num-1; i++){
            points.push_back(i+1);
        }
        do{
            vector<int> nodes = points;
            reverse(nodes.begin(), nodes.end());
            nodes.push_back(0);
            reverse(nodes.begin(), nodes.end());
            res = min(res, bfs(adj, nodes));
            if(res < 0)
                break;
        }while(next_permutation(points.begin(), points.end()));
        cout << max(res, -1) << '\n';
    }
    return 0;
}
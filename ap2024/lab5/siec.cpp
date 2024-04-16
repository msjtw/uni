#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<queue>

using namespace std;

typedef long long int ll;
typedef pair<string, ll> psi;
typedef pair<ll, string> pis;


const ll INF = __INT64_MAX__/2;

int main(){
    ll n, c, r;
    ll num = 1;
    while(true){
        cin >> n >> c >> r;
        if(n+c+r == 0)
            break;
        string start;
        cin >> start;
        vector<string> cars;
        map<string, map<string, ll>> dist;
        for(ll i = 0 ; i < c; i++){
            string s;
            cin >> s;
            cars.push_back(s);
        }
        set<string> cities;
        vector<tuple<string, string, int>>roads;
        for(ll i = 0; i < r; i++){
            string a, b, dst;
            cin >> a >> dst >> b;

            cities.insert(a);
            cities.insert(b);

            ll d = stoi(dst.substr(2, dst.length()-2));
            if(dst[0] == '<'){
                roads.push_back({b, a, d});
            }
            if(dst[dst.length()-1] == '>'){
                roads.push_back({a, b, d});
            }
        }

        for(string c : cities){
            for(string d : cities){
                dist[c][d] = INF;
                if(c == d)
                    dist[c][d] = 0;
            }
        }

        for(auto road : roads){
            string a, b;
            ll w;
            tie(a, b ,w) = road;
            dist[a][b] = min(dist[a][b], w);
        }

        for(auto k : cities){
            for(auto a : cities){
                for(auto b : cities){
                    dist[a][b] = min(dist[a][b], dist[a][k]+dist[k][b]);
                }
            }
        }
        
        ll res = 0;
        for(auto a : cars){
            res += dist[start][a];
            res += dist[a][start];
        }
        cout << num++ << ". " << res << endl;
    }
    return 0;
}
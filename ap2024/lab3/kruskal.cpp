#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

vector<tuple<int, int, int>> edg;

const int MX = 1e5+7;

int s_size[MX];
int link[MX];

int max_size = 0;
int num;

bool cmp(tuple<int, int, int> l, tuple<int, int, int> r){
    return get<2>(l) < get<2>(r);
}

int find(int x){
    while(x != link[x])
        x = link[x];
    return x;
}

bool same(int a, int b){
    return find(a) == find(b);
}

void unite(int a, int b){
    a = find(a);
    b = find(b);
    if(s_size[a] < s_size[b])
        swap(a, b);
    s_size[a] += s_size[b];
    max_size = max(max_size, s_size[a]);
    link[b] = a;
    num--;
}

int main(){
    for(int i = 0; i < MX; i++){
        s_size[i] = 1;
        link[i] = i;
    }

    int n, m, res;
    cin >> n >> m;
    num = n;
    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        edg.push_back({a, b, w});
    }

    sort(edg.begin(), edg.end(), cmp);

    for(auto e : edg){
        int a, b ,w;
        tie(a, b, w) = e;
        if(!same(a, b)){
            unite(a, b);
            res += w;
        }
    }
    cout << res;
    return 0;
}
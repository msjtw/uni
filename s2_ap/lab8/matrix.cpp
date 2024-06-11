#include<iostream>
#include<vector>
#include<algorithm>
#include<tuple>

using namespace std;

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

const int MX = 1e5+7;

vector<tiii> roads;
bool mash[MX] {};

int link[MX];
int ssize[MX];

bool cmp(tiii l, tiii r){
    return get<2>(l) > get<2>(r);
}

int find(int x){
    while(x != link[x])
        x = link[x];
    return x;
}

void unite(int a, int b){
    a = find(a);
    b = find(b);
    if(ssize[a] < ssize[b])
        swap(a, b);
    if(mash[a] or mash[b])
        mash[a] = true;
    ssize[a] += ssize[b];
    link[b] = a;
}

int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 0 ; i < n-1; i++){
        int a, b, w;
        cin >> a >> b >> w;
        roads.push_back({a, b, w});
    }
    for(int i = 0 ; i < m; i++){
        int a;
        cin >> a;
        mash[a] = true;
    }

    sort(roads.begin(), roads.end(), cmp);
    for(int i = 0 ; i < MX; i++){
        link[i] = i;
        ssize[i] = 1;
    }

    int res = 0;

    for(auto r : roads){
        int a, b ,w;
        tie(a, b ,w) = r;

        if(!(mash[find(a)] and mash[find(b)])){
            unite(a, b);
        }
        else{
            res += w;
        }
    }

    cout << res;

    return 0;
}
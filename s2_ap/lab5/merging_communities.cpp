#include<iostream>

using namespace std;

const int MX = 1e5+7;

int s_size[MX];
int link[MX];

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
    link[b] = a;
}

int main(){
    for(int i = 0 ; i < MX; i++){
        link[i] = i;
        s_size[i] = 1;
    }
    int n, q;
    cin >> n >> q;
    while(q --> 0){
        char op;
        int a, b;
        cin >> op;
        if(op == 'M'){
            cin >> a >> b;
            if(!same(a, b))
                unite(a, b);
        }
        if(op == 'Q'){
            cin >> a;
            cout << s_size[find(a)] << endl;
        }
    }
    return 0;
}
#include<iostream>
#include<vector>

using namespace std;

void solve(){
    int n, z;
    cin >> z >> n;
    vector<int> prices;
    for(int i = 0 ; i < n; i++){
        int a;
        cin >> a;
        prices.push_back(a);
    }
    for(int i = 0; i < prices.size(); i++){
        for(int k = i+1; k < prices.size(); k++){
            if(prices[i] + prices[k] == z){
                cout << i+1 << " " << k+1 << endl;
                return;
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t --> 0){
       solve();
    }

}
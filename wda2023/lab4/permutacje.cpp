#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_map>

using namespace std;

int main(){
    int p;
    cin >> p;
    while(p-->0){
        int n;
        cin >> n;
        unordered_map<string, int> all;
        for(int i = 0; i < n; i++){
            string s;
            cin >> s;
            sort(s.begin(), s.end());
            all[s]++;
        }   
        int res = 0;
        for(auto a : all){
            res = max(res, a.second);
        } 
        cout << res << endl;
    }
    return 0;
}
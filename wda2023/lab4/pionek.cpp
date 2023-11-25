#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector <int> num;
    for(int i = 0 ; i < n ; i ++){
        int a;
        cin >> a;
        num.push_back(a);
    }


    int cost[1000007] {};
    for(int i = 0; i < n ;i++){
        cost[i] = (i > 0 ? cost[i-1]+num[i]: num[i]);
        for(int k = i-1 ; k >= 0 and i-k <= 6; k--){
            cost[i] = max(cost[i], cost[k]+num[i]);
        }
        //cout << cost[i] << " ";
    }

    cout <<  cost[n-1];

    return 0;
}
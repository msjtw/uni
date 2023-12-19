#include<iostream>
#include<set>

using namespace std;

long long int res = 0;

int main(){
    multiset<int> reciepts;
    int days;
    cin >> days;
    while(days --> 0){
        int n;
        cin >> n;
        while(n --> 0){
            int a;
            cin >> a;
            reciepts.insert(a);
        }
        auto smallest = reciepts.begin();
        auto largest = reciepts.end();
        largest--;
        res += *largest - *smallest;
        reciepts.erase(smallest);
        reciepts.erase(largest);
    }

    cout << res;

    return 0;
}
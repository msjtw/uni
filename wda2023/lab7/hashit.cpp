#include <iostream>
#include <map>

using namespace std;

int hash_f(string s){
    long long int sum = 0;
    for(int i = 0 ; i < s.length(); i++){
        sum += s[i]*(i+1);
    }
    sum *= 19;
    return sum % 101;
}

int main(){
    int t;
    cin >> t;
    while(t --> 0){
        map<string,int> indexes;
        string table[101] {};
        for(int i = 0; i < 101; i++){
            table[i] = "";
        }
        int n;
        cin >> n;
        for(int i = 0; i < n; i++){
            string l;
            cin >> l;
            string op = l.substr(0,3);
            string key = l.substr(4, l.length()-4);
            int index = hash_f(key);
            if(op == "ADD"){
                if(indexes.count(key))
                    continue;
                int n_op = 1;
                while(table[index] != "" and n_op < 20){
                    index = hash_f(key) + n_op*n_op + 23*n_op;
                    index %= 101;
                    n_op++;
                }
                if(table[index] == ""){
                    indexes[key] = index;
                    table[index] = key;
                }
            }
            if(op == "DEL"){
                // if(indexes.count(key) > 0){
                //     table[indexes[key]] = "";
                //     indexes.erase(key);
                // }
                indexes.erase(table[hash_f(key)]);
                table[hash_f(key)] = "";
                //indexes
            }
        }
        //cout << indexes.size() << endl;
        int size = 0;
        for(int i = 0; i < 101; i++){
            if(table[i] != ""){
                size++;
            }
        }
        cout << size  << endl;
        for(int i = 0; i < 101; i++){
            if(table[i] != ""){
                cout << i << ":" <<  table[i] << endl;
            }
        }
    }
    return 0;
}
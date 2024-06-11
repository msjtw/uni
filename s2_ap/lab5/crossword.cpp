#include <iostream>
#include <vector>

using namespace std;

struct arr{
    char t[12][12];
};

vector<string> words;
bool done = false;

void fit(arr crt, int t){
    if(done)
        return;

    if(t == words.size()){
        for(int i = 1; i < 11; i++){
            for(int k = 1; k < 11; k++){
                cout << crt.t[i][k];
            }
            cout << endl;
        }
        done = true;
        return;
    }

    auto cross = crt.t;
    string word = words[t];
    for(int i = 1; i < 11; i++){
        for(int k = 1; k < 11; k++){
            int horz = 0;
            for(int j = i; cross[j][k] == '-' || cross[j][k] == word[j-i]; j++){
                horz++;
            }
            if(horz == word.length()){
                auto tmp = crt;
                for(int j = 0; j < horz; j++){
                    tmp.t[i+j][k] = word[j];
                }
                fit(tmp, t+1);
                if(done)
                    return;
            }
            horz = 0;
            for(int j = k; cross[i][j] == '-' || cross[i][j] == word[j-k]; j++){
                horz++;
            }
            if(horz == word.length()){
                auto tmp = crt;
                for(int j = 0; j < horz; j++){
                    tmp.t[i][k+j] = word[j];
                }
                fit(tmp, t+1);
                if(done)
                    return;
            }
        }
    }
}

int main(){
    arr cross;

    for(int i = 0; i < 12; i++){
        cross.t[i][0] = '+';
        cross.t[i][11] = '+';
        cross.t[0][i] = '+';
        cross.t[11][i] = '+';
    }

    for(int i = 1; i < 11; i++){
        for(int k = 1; k < 11; k++){
            cross.t[i][k] = getchar();
        }
        getchar();
    }

    string sword;
    cin >> sword;
    while(sword.length() > 0){
        int it = sword.find(';');
        if(it == -1){
            words.push_back(sword);
            sword = "";
        }
        else{
            words.push_back(sword.substr(0,it));
            sword = sword.substr(it+1, string::npos);
        }
    }

    fit(cross, 0);

    return 0;
}
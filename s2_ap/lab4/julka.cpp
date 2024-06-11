#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void add(vector<int> &a, vector<int> &b){
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    a.resize(max(a.size(), b.size())+2,0);
    for(int i = 0 ; i < b.size(); i++){
        a[i] += b[i];
    }
    for(int i = 0; i < a.size()-1; i++){
        if(a[i] < 0){
            a[i] += 10;
            a[i+1] -= 1;
        }
        if(a[i] > 9){
            a[i] -= 10;
            a[i+1] += 1;
        }
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
}

void sub(vector<int> &a, vector<int> &b){
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    a.resize(max(a.size(), b.size()),0);
    for(int i = 0 ; i < b.size(); i++){
        a[i] -= b[i];
    }
    for(int i = 0; i < a.size()-1; i++){
        if(a[i] < 0){
            a[i] += 10;
            a[i+1] -= 1;
        }
        if(a[i] > 9){
            a[i] -= 10;
            a[i+1] += 1;
        }
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
}

vector<int> div(vector<int> &a, int b){
    vector<int> res;
    int tmp = 0;
    for(int i = 0; i < a.size(); i++){
        tmp *= 10;
        tmp += (a[i]);
        if(tmp >= b){
            int d = tmp/b;
            res.push_back(d);
            tmp -= b*d;
        }
        else{
            res.push_back(0);
        }
    }
    return res;
}

void print(vector<int> a){
    int i = 0;
    while(a[i] == 0)
        i++;
    for(; i < a.size(); i++){
        cout << char(a[i]+'0');
    }
    cout << endl;
}

int main(){
    string sn, sx;
    while(cin >> sn >> sx){
        vector<int> n, x;
        for(int i = 0; i < sn.size(); i++){
            n.push_back(sn[i]-'0');
        }
        for(int i = 0; i < sx.size(); i++){
            x.push_back(sx[i]-'0');
        }

        sub(n, x);
        vector<int> a = div(n,2);
        vector<int> b = a;
        add(b, x);

        print(b);
        print(a);
    }
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void add(vector<int> &a, vector<int> b){
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

void sub(vector<int> &a, vector<int> b){
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
    string sx;
    while(cin >> sx){
        if(sx == "1"){
            cout << 1 << endl;
            continue;
        }
        vector<int> x;
        for(int i = 0; i < sx.size(); i++){
            x.push_back(sx[i]-'0');
        }
        vector<int> two = {2};
        add(x, x);
        sub(x, two);

        print(x);
    }
    return 0;
}
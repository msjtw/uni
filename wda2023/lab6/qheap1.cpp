#include<iostream>

using namespace std;

const int SIZE = 100007;

int heap1[SIZE];
int s1 = 1;

int heap2[SIZE];
int s2 = 1;

void add(int heap[], int* s, int x){
    int poz = *s;
    *s += 1;
    heap[poz] = x;
    while(poz/2 >= 1){
        if(heap[poz/2] > heap[poz]){
            swap(heap[poz/2], heap[poz]);
            poz /= 2;
        }
        else{
            break;
        }
    }
}

void pop(int heap[], int* s){
    int poz = 1;
    *s -= 1;
    heap[1] = heap[*s];
    int father = poz;
    int son = 2*father;
    while(son < *s){
        if(son+1 < *s && heap[son+1] < heap[son]){
            son++;
        }
        if(heap[son] < heap[father]){
            swap(heap[son], heap[father]);
            father = son;
            son = father*2;
        }
        else{
            break;
        }
    }
}


int main(){
    int q;
    cin >> q;
    while(q --> 0){
        int a, b;
        cin >> a;
        if(a == 1){
            cin >> b;
            add(heap1, &s1, b);
        }
        if(a == 2){
            cin >> b;
            add(heap2, &s2, b);
        }
        if(a == 3){
            while(heap1[1] == heap2[1]){
                pop(heap1, &s1);
                pop(heap2, &s2);
            }
            cout << heap1[1] << " ";
        }
    }
    // for(int i = 0;i < s1; i++){
    //         cout << heap1[i] << " ";
    // }
}
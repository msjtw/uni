#ifndef NWT_RAPH_H_
#define NWT_RAPH_H_

#include <iostream>
#include <cmath>

template<typename T>
int newton_raphson(T &x, T (*f)(T), T (*df)(T), T (*d2f)(T),const int mit, const T eps, T &fatx, int &it){
    int st;
    T dfatx, d2fatx, p, v, w, xh, x1, x2;
    if(mit < 1){
        st = 1;
    }
    else{
        st = 3;
        it = 0;
        do{
            it++;
            fatx = f(x);
            dfatx = df(x);
            d2fatx = d2f(x);
            p = fatx*dfatx - 2*fatx*d2fatx;
            if(p < 0){
                st = 4;
            }
            else{
                xh = x;
                w = abs(xh);
                p = sqrt(p);
                x1 = x-(dfatx-p)/d2fatx;
                x2 = x-(dfatx+p)/d2fatx;
                if( abs(x2-xh) > abs(x1 - xh) )
                    x = x1;
                else 
                    x = x2;
                v = abs(x);
                if(v < w){
                    v = w;
                }
                if(v == 0){
                    st = 0;
                }
                else if( abs(x-xh)/v <= eps ){
                    st = 0;
                }
            }
        }while(it != mit and st == 3);
    }
    if(st == 0 or st == 3){
        fatx = f(x);
    }
    return st;
} 

#endif //  NWT_RAPH_H_

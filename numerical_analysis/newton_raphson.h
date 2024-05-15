#ifndef NWT_RAPH_H_
#define NWT_RAPH_H_

#include <iostream>
#include <cmath>

// x - initial aproximation of zero of the function
// f - pointer to function that evaluates to f(x)
// df - pointer to function that evaluates to first derivative of f(x)
// d2f - pointer to function that evaluates to second derivative of f(x)
// mit - maximum number of iterations
// eps - minimal error

// calculated values
// x - found zero of the function
// fatx - value of f(x)
// it - numer of iterations

// return value st
// 1: mit < 1
// 3: coudn't achive desired accuracy in mit iterations
// 4: when for some x [f'(x)]² -2f(x)f"(x) < 0
// in other cases 0


template<typename T>
int newton_raphson(T &x, T (*f)(T), T (*df)(T), T (*d2f)(T),const int mit, const T eps, T &fatx, int &it){
    int st;
    T dfatx, d2fatx, p, v, w, xh, x1, x2;
    if(mit < 1){
        return 1;
    }
    st = 3;
    it = 0;
    do{
        it++;
        fatx = f(x);
        dfatx = df(x);
        d2fatx = d2f(x);
        p = dfatx*dfatx - 2*fatx*d2fatx;
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
            else if( abs(x-xh)/v < eps ){
                st = 0;
            }
        }
    }while(it != mit and st == 3);
    if(st == 0 or st == 3){
        fatx = f(x);
    }
    return st;
} 

#endif //  NWT_RAPH_H_

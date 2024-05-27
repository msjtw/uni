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
// 2: for some x: f"(x) = 0
// 3: coudn't achive desired accuracy in mit iterations
// 4: when for some x [f'(x)]² -2f(x)f"(x) < 0
// in other cases 0

using namespace std;

int newton_raphson_f(_Float128 &x, _Float128 (*f)(_Float128), _Float128 (*df)(_Float128), _Float128 (*d2f)(_Float128),const int mit, const _Float128 eps, _Float128 &fatx, int &it){
    int st;
    _Float128 dfatx, d2fatx, p, v, w, xh, x1, x2;
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
        if(d2fatx == 0){
            st = 2;
        }
        else if(p < 0){
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
    } while(it < mit and st == 3);
    if(st == 0 or st == 3){
        fatx = f(x);
    }
    return st;
} 

int newton_raphson_i(Interval &x, Interval (*f)(Interval), Interval (*df)(Interval), Interval (*d2f)(Interval),const int mit, const _Float128 eps, Interval &fatx, int &it){
    int st;
    Interval dfatx, d2fatx, p, v, w, xh, x1, x2, ret;

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
        if(con_zero(d2fatx)){
            st = 2;
        }
        else if(neg(p)){
            st = 4;
        }
        else{
            xh = x;
            w = abs(xh);
            p = sqrt(p);
            x1 = x-(dfatx-p)/d2fatx;
            x2 = x-(dfatx+p)/d2fatx;
            if( make_intr(x2, xh).width() > make_intr(x1, xh).width() )
                x = x1;
            else 
                x = x2;
            ret = make_intr(x, xh);
            if( ret.width() < eps ){
                st = 0;
            }
        }
    } while(it < mit and st == 3);
    if(st == 0 or st == 3){
        x = ret;
        fatx = f(x);
    }
    return st;
} 

#endif //  NWT_RAPH_H_

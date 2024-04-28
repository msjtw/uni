#include <iostream>
#include <cmath>

using namespace std;

double newton_raphson(double x, double (*f)(double), double (*df)(double), double (*d2f)(double), int mit, double eps, double fatx, int it, int st){
    double dfatx, d2fatx, p, v, w, xh, x1, x2;
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
        }while(it == mit or st != 3);
    }
    if(st == 0 or st == 3){
        return x;
        fatx = f(x);
    }
    return 0;
} 

int main(){

}
// msjtw 2024
// https://github.com/msjtw

#ifndef INTERVAL_H_
#define INTERVAL_H_

#include<string>
#include <iostream>

//namespace intrvl{
    class Interval{
        public:
            Interval();
            Interval(std::string);
            Interval(_Float128, _Float128);
            bool read_float(std::string);
            bool read_interval(std::string, std::string);

            friend Interval sqrt(const Interval &);
            friend Interval pow(const Interval &, int);
            friend Interval abs(const Interval &);
            friend Interval sin(Interval);
            friend Interval cos(Interval);

            friend std::string to_string(const _Float128, int, char);
            friend std::string to_string(const Interval, int, char);
            friend std::ostream& operator<<(std::ostream&, const Interval&);


            Interval operator+(const Interval &) const;
            Interval operator-(const Interval &) const;
            Interval operator*(const Interval &) const;
            Interval operator/(const Interval &) const;
            bool operator<(const Interval &) const;
            inline bool operator>(const Interval &intrvl) const{
                return !this->operator<(intrvl);
            }
            bool operator==(const Interval &) const;
            bool operator<=(const Interval &) const;
            inline bool operator>=(const Interval &intrvl) const{
                return !this->operator<=(intrvl);
            }

            bool operator<(const _Float128 &) const;
            inline bool operator>(const _Float128 &val) const{
                return !this->operator<(val);
            }

            inline Interval operator+(int a) const{
                return this->operator+(Interval(std::to_string(a)));
            }
            inline Interval operator-(int a) const{
                return this->operator-(Interval(std::to_string(a)));
            }
            inline Interval operator*(int a) const{
                return this->operator*(Interval(std::to_string(a)));
            }
            inline Interval operator/(int a) const{
                return this->operator/(Interval(std::to_string(a)));
            }
            inline bool operator==(int a) const{
                return this->operator==(Interval(std::to_string(a)));
            }


            friend Interval operator+(int a, const Interval &intrvl){
                return intrvl + a;
            }
            friend Interval operator-(int a, const Interval &intrvl){
                return intrvl - a;
            }
            friend Interval operator*(int a, const Interval &intrvl){
                return intrvl * a;
            }
            friend Interval operator/(int a, const Interval &intrvl){
                return intrvl / a;
            }
            friend bool operator<(_Float128 a, const Interval &intrvl){
                return intrvl < a;
            }
            friend bool operator>(int a, const Interval &intrvl){
                return !(intrvl < a);
            }
            friend bool operator==(int a, const Interval &intrvl){
                return intrvl == a;
            }

        private:
            _Float128 left;
            _Float128 right;
            int cmp(std::string, std::string);

    };

    std::string to_string(const _Float128, const int n = 50, const char type = 'e');
    std::string to_string(const Interval, const int n = 50, const char type = 'e');
    std::string sci_to_full(std::string);

    inline Interval pi(){
        Interval r;
        r.read_float("3.141592653589793238462643383279502884197169399375");
        return r;
    }

    _Float128 sqrtf128(const _Float128, bool);
    _Float128 pow(const _Float128 , int);
    inline _Float128 sqrt(const _Float128 x){
        return sqrtf128(x, false);
    }
    inline _Float128 absf128(const _Float128 f){
        return (f < 0 ? f * -1 : f);
    }
    inline _Float128 abs(const _Float128 f){
        return (f < 0 ? f * -1 : f);
    }
//}
#endif /* INTERVAL_H_ */
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
            friend Interval pow(const Interval &);
            friend Interval abs(const Interval &);
            friend Interval sin(Interval);
            friend Interval cos(Interval);

            friend std::string to_string(const _Float128, int, char);
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
            inline bool operator<(int a) const{
                return this->operator<(Interval(std::to_string(a)));
            }
            inline bool operator>(int a) const{
                return !this->operator<(Interval(std::to_string(a)));
            }
            inline bool operator==(int a) const{
                return this->operator==(Interval(std::to_string(a)));
            }
            inline bool operator<=(int a) const{
                return this->operator<=(Interval(std::to_string(a)));
            }
            inline bool operator>=(int a) const{
                return this->operator>=(Interval(std::to_string(a)));
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
            friend bool operator<(int a, const Interval &intrvl){
                return intrvl < a;
            }
            friend bool operator>(int a, const Interval &intrvl){
                return !(intrvl < a);
            }
            friend bool operator==(int a, const Interval &intrvl){
                return intrvl == a;
            }
            friend bool operator<=(int a, const Interval &intrvl){
                return intrvl <= a;
            }
            friend bool operator>=(int a, const Interval &intrvl){
                return intrvl >= a;
            }

        private:
            _Float128 left;
            _Float128 right;
            int cmp(std::string, std::string);

    };

    std::string to_string(const _Float128, const int n = 5000, const char type = 'f');
    std::string scientificToFull(const std::string&);

    inline Interval pi(){
        Interval r;
        r.read_float("3.141592653589793238462643383279502884197169399375");
        return r;
    }

    _Float128 sqrtf128(const _Float128, bool);
    inline _Float128 absf128(const _Float128 f){
        return (f < 0 ? f * -1 : f);
    }
//}
#endif /* INTERVAL_H_ */
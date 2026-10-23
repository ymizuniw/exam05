#include "bigint.hpp"
#include <string>

bigint::bigint(){
        d_.push_back(0);
}
bigint::bigint(const bigint &other){
        d_ = other.d_;
}
bigint::bigint(unsigned int n){
        // 1 0 0
        if (n==0){
                d_.push_back(0);
                return ;
        }
        while (n>0){
                d_.push_front(n%10);
                n/=10;
        }
}
// bigint::bigint(std::deque<unsigned int> &d){

// }
bigint &bigint::operator=(const bigint &other){
        if (this==&other)
                return *this;
        d_=other.d_;
        return *this;
}
bigint::~bigint(){

}

bigint bigint::operator+=(const bigint &other){
        //   1 0 
        // 9 9 1
        std::deque<unsigned int> d;
        int idx_a = this->d_.size() - 1;
        int idx_b = other.d_.size() - 1;
        int carry = 0;
        int add = 0;
        while (idx_a>=0 || idx_b>=0 || carry>0){
                add = 0;
                // std::cout << "add a:" << idx_a << std::endl;
                if (idx_a>=0){
                        add += this->d_[idx_a];
                        idx_a--;
                }
                // std::cout << "add b:" << idx_b << std::endl;
                if (idx_b>=0){
                        add += other.d_[idx_b];
                        idx_b--;
                }
                add += carry;
                carry = add/10;
                add %= 10;
                d.push_front(add);
        }
        this->d_ = d;
        return *this;
}
bigint bigint::operator+=(unsigned int n){
        const bigint b(n);
        *this+=b;
        return *this;
}

bigint bigint::operator++(){
        const bigint one(1);
        *this+=one;
        return *this;
}
bigint bigint::operator++(int){
        const bigint one(1);
        bigint cp(*this);
        *this+=one;
        return cp;
}
bool    bigint::trySubtract(std::deque<unsigned int>::reverse_iterator &rit, std::deque<unsigned int>::reverse_iterator &rend){
        if (rit==rend)
                return false;
        if (*rit==0){
                bool ret = trySubtract(++rit,rend);
                --rit;
                if (ret){
                        *rit = 9;
                        return true;
                }
                else{
                        return false;
                }
        }
        else {
                *rit -= 1;
                return true;
        }
}
bigint bigint::operator--(){
        // 1 0 0
        std::deque<unsigned int>::reverse_iterator rit = d_.rbegin();
        std::deque<unsigned int>::reverse_iterator rend = d_.rend();

        trySubtract(rit,rend);
        while (d_.front()==0){
                d_.pop_front();
        }
        return *this;
}
bigint bigint::operator<<(unsigned int shift){
        bigint cp(*this);
        cp<<=(shift);
        return cp;
}
bigint bigint::operator<<=(unsigned int shift){
        while (shift>0){
                if (d_.size()==1 && d_.front()==0)
                {
                        return *this;
                }
                d_.push_back(0);
                shift--;
        }
        return *this;
}
bigint bigint::operator>>(unsigned int shift){
        while (shift>0) {
                if (d_.empty()){
                        d_.push_back(0);
                        return *this;
                }
                d_.pop_back();
                shift--;
        }
        return *this;
}
bigint bigint::operator>>=(const bigint &shift){
        bigint cp(shift);
        while (cp>0){
                if (d_.empty()){
                        d_.push_back(0);
                        return *this;
                }
                d_.pop_back();
                --cp;
        }
        return *this;
}

std::string bigint::getNumStr() const{
        std::string s;
        for (int i=0;i<d_.size();++i){
                s += std::to_string(d_[i]);
        }
        return s;
}

size_t bigint::getSize() const{
        return d_.size();
}

bigint operator+(const bigint &a, const bigint &b){
        bigint ret(a);
        ret+=b;
        return ret;
}

unsigned int bigint::operator[](unsigned int i) const{
        if (d_.size()<=i)
                return 0;
        return d_[i];
}
bool    operator<(const bigint &a, const bigint &b){
        if (a.getSize()<b.getSize())
                return true;
        for (size_t i=0;i<a.getSize();++i){
                if (a[i]<b[i])
                        return true;
                else if (a[i]>b[i])
                        return false;
        }
        return false;
}
bool    operator>(const bigint &a, const bigint &b){
        if (a.getSize()>b.getSize())
                return true;
        for (size_t i=0;i<a.getSize();++i){
                if (a[i]>b[i])
                        return true;
                else if (a[i]<b[i])
                        return false;
        }
        return false;
}
bool    operator<=(const bigint &a, const bigint &b){
        if (a>b)
                return false;
        else
                return true;
}
bool    operator>=(const bigint &a, const bigint &b){
        if (a<b)
                return false;
        else
                return true;
}
bool    operator==(const bigint &a, const bigint &b){
        if (!(a>b) && !(a<b))
                return true;
        else
                return false;
}
bool    operator!=(const bigint &a, const bigint &b){
        if (a==b)
                return false;
        else
                return true;
}


std::ostream &operator<<(std::ostream &os, const bigint &obj)
{
        os << obj.getNumStr();
        return os;
}

int main(void)
{
        bigint a;
        bigint b(1);
        bigint c(99);
        bigint d(9999);
        bigint e(100);

        bigint a_copy(a);
        
        std::cout << "a: " << a << std::endl;
        std::cout << "b: " << b << std::endl;
        std::cout << "c: " << c << std::endl;
        std::cout << "d: " << d << std::endl;
        std::cout << "e: " << e << std::endl;

        std::cout << "\nadd\n\n" << std::endl;
        std::cout << "a: " << a+b << std::endl;
        std::cout << "b: " << b+c << std::endl;
        std::cout << "c: " << c+d << std::endl;
        std::cout << "d: " << d+e << std::endl;
        std::cout << "e: " << e << std::endl;

        std::cout << "\nshift\n\n" << std::endl;
        std::cout << "a: " << (bigint)(a<<5) << std::endl;
        std::cout << "b: " << (bigint)(b>>5) << std::endl;
        std::cout << "e: " << e << std::endl;
        std::cout << "e: " << (bigint)(e>>=(const bigint)1) << std::endl;
        return 0;
}

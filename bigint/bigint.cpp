#include "bigint.hpp"
#include <cstddef>
#include <deque>
#include <string>

bigint::bigint(){
    d_.push_back(0);
}
bigint::bigint(const bigint &other){
    // copy deq
    d_ = other.d_;
}
bigint::bigint(unsigned int n){
    // 1 0 0 
    if (n==0)
        d_.push_back(n);
    while (n>0){
        d_.push_front(n%10);
        n/=10;
    }
}

bigint::bigint(std::deque<unsigned int> &d){
    this->d_ = d;
}

bigint &bigint::operator=(const bigint &other){
    if (this==&other){
        return *this;
    }
    this->d_=other.d_;
    return *this;
}
bigint::~bigint(){

}

bigint bigint::operator+=(const bigint &other){
    // 0 1 1 
    // 9 9 9
    std::deque<unsigned int> d;
    size_t d1 = this->d_.size();
    size_t d2 = other.d_.size();
    size_t i = d1;
    size_t j = d2;
    unsigned int carry = 0;
    unsigned int add = 0;

    while (i!=0 || j!=0 || carry!=0){

        add = carry;

        if (i!=0){
            add += this->d_.at(i-1);
            i--;
        }
        if (j!=0){
            add += other.d_.at(j-1);
            j--;
        }
        carry = add/10;
        add %= 10;

        d.push_front(add);
    }
    this->d_ = d;
    return *this;
}

bigint bigint::operator+=(unsigned int n){
    bigint rh(n);
    *this+=rh;
    return *this;
}
bigint bigint::operator+(const bigint &other){
    bigint ret(*this);
    ret+=other;
    return ret;
}

bigint bigint::operator++(){
    // 1 9 9
    bigint one(1);
    *this+=one;
    return *this;
}
bigint bigint::operator++(int){
    bigint one(1);
    bigint ret(*this);
    *this+=one;
    return ret;
}

bool    bigint::trySubtract(std::deque<unsigned int>::reverse_iterator &rit, std::deque<unsigned int>::reverse_iterator &rend){
    if (rit==rend)
        return false;
    if (*rit==0){
        if (trySubtract(++rit, rend)==false)
            return false;
        --rit;
        *rit = 9;
    }
    else {
        --*rit;
    }
    return true;
}

bigint bigint::operator--(){
    // 1 0 0
    // subtract : d_.at(0)
        // subtract : d_.at(1)
            // subtract : d_.at(2)
    if (d_.size()==1 && d_.at(0)==0)
        return *this;
    std::deque<unsigned int>::reverse_iterator rit = d_.rbegin();
    std::deque<unsigned int>::reverse_iterator rend = d_.rend();
    trySubtract(rit,rend);

    std::deque<unsigned int>::iterator it = d_.begin();
    std::deque<unsigned int>::iterator end = d_.end();
    while (it!=end && *it==0){
        d_.erase(it);
        ++it;
    }
    return *this;
}
bigint bigint::operator<<(unsigned int shift){
    if (d_.size()==1 && d_.at(0)==0)
        return *this;
    bigint tmp(*this);
    while (shift>0){
        tmp.d_.push_back(0);
        shift--;
    }
    return tmp;
}
bigint bigint::operator<<=(unsigned int shift){
    while (shift>0){
        d_.push_back(0);
        shift--;
    }
    return *this;
}
bigint bigint::operator>>(unsigned int shift){
    bigint ret(*this);
    while (shift>0){
        if (ret.d_.empty()){
            break ;
        }
        ret.d_.pop_back();
        shift--;
    }
    if (ret.d_.empty()){
        ret.d_.push_back(0);
    }
    return ret;
}
bigint bigint::operator>>=(const bigint shift){
    bigint zero(0);
    bigint shift2(shift);
    while (shift2>zero){
        if (d_.empty()){
            break ;
        }
        d_.pop_back();
        --shift2;
    }
    if (d_.empty()){
        d_.push_back(0);
    }
    return *this;
}

bool    bigint::operator<(const bigint b){
    if (d_.size() > b.d_.size())
        return false;
    else if (d_.size() < b.d_.size())
        return true;
    for (size_t i=0;i<d_.size();++i){
        if (d_.at(i)<b.d_.at(i))
            return true;
    }
    return false;
}
bool    bigint::operator>(const bigint b){
    if (d_.size() < b.d_.size())
        return false;
    else if (d_.size() > b.d_.size())
        return true;
    for (size_t i=0;i<d_.size();++i){
        if (d_.at(i)>b.d_.at(i))
            return true;
    }
    return false;
}
bool    bigint::operator<=(const bigint b){
    if (*this<b || *this==b)
        return true;
    return false;
}
bool    bigint::operator>=(const bigint b){
    if (*this>b || *this==b)
        return true;
    return false;
}
bool    bigint::operator==(const bigint b){
    if (d_.size()!=b.d_.size())
        return false;
    for (size_t i=0;i<d_.size();++i){
        if (d_.at(i)!=b.d_.at(i))
            return false;
    }
    return true;
}
bool    bigint::operator!=(const bigint b){
    if (!(*this==b))
        return true;
    return false;
}
std::string bigint::getNumStr(){
    std::string s;
    for (size_t i=0;i<d_.size();++i){
        s.append(std::to_string(d_.at(i)));
    }
    return s;
}

std::ostream &operator<<(std::ostream &os, bigint obj){
    os << obj.getNumStr();
    return os;
}

int main(void){
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

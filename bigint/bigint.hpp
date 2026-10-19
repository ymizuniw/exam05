#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <ostream>
#include <string>
#include <sstream>
#include <deque>
#include <iostream>

class bigint {
    private:
        std::deque<unsigned int> d_;
    public:
        bigint();
        bigint(const bigint &other);
        bigint(unsigned int n);
        bigint(std::deque<unsigned int> &d);
        bigint &operator=(const bigint &other);
        ~bigint();

        bigint operator+=(const bigint &other);
	bigint operator+=(unsigned int n);
        bigint operator+(const bigint &other);


	bigint operator++();
        bigint operator++(int);
        bool    trySubtract(std::deque<unsigned int>::reverse_iterator &rit, std::deque<unsigned int>::reverse_iterator &rend);
        bigint operator--();
        bigint operator<<(unsigned int shift);
        bigint operator<<=(unsigned int shift);
        bigint operator>>(unsigned int shift);
        bigint operator>>=(const bigint shift);

        bool    operator<(const bigint b);
        bool    operator>(const bigint b);
        bool    operator<=(const bigint b);
        bool    operator>=(const bigint b);
        bool    operator==(const bigint b);
        bool    operator!=(const bigint b);
	std::string getNumStr();
};

std::ostream &operator<<(std::ostream &os, bigint obj);

#endif 

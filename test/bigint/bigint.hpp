#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>
#include <deque>

class bigint {
private:
        std::deque<unsigned int> d_;
public:
	bigint();
        bigint(const bigint &other);
        bigint(unsigned int n);
        bigint &operator=(const bigint &other);
        ~bigint();

        bigint operator+=(const bigint &other);
	bigint operator+=(unsigned int n);
        
	bigint operator++();
        bigint operator++(int);
        bool    trySubtract(std::deque<unsigned int>::reverse_iterator &rit, std::deque<unsigned int>::reverse_iterator &rend);
        bigint operator--();
        bigint operator<<(unsigned int shift);
        bigint operator<<=(unsigned int shift);
        bigint operator>>(unsigned int shift);
        bigint operator>>=(const bigint &shift);
        unsigned operator[](unsigned int) const;
        
	std::string getNumStr() const;
	size_t getSize() const;

};

bigint operator+(const bigint &a, const bigint &b);
bool    operator<(const bigint &a, const bigint &b);
bool    operator>(const bigint &a, const bigint &b);
bool    operator<=(const bigint &a, const bigint &b);
bool    operator>=(const bigint &a, const bigint &b);
bool    operator==(const bigint &a, const bigint &b);
bool    operator!=(const bigint &a, const bigint &b);

std::ostream &operator<<(std::ostream &os, const bigint &obj);

#endif

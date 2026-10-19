#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"

class set {
    private:
        searchable_bag &bag;
        set &operator=(const set &other); // reference member cannot be rebound: assignment disabled
    public:
        set(searchable_bag &bag);
        set(const set &other);            // shares the same underlying bag
        ~set();
        void insert(int);
        void insert(int *, int);
        void print();
        void clear();
        bool has(int) const;
        const searchable_bag &get_bag() const;
};

#endif

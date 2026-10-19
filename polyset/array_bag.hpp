#ifndef ARRAY_BAG_HPP
#define ARRAY_BAG_HPP

#include "bag.hpp"

class array_bag : public virtual bag{
    protected:
        int *data;
        int size;
    public:
        array_bag();
        array_bag(int *data, int size);
        array_bag(const array_bag &other);
        array_bag &operator=(const array_bag &other);
        ~array_bag();
        void insert(int);
        void insert(int *, int);
        void print();
        void clear();
};

#endif

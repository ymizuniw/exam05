#ifndef SEARCHABLE_BAG_HPP
#define SEARCHABLE_BAG_HPP

#include "bag.hpp"

class searchable_bag: public virtual bag{
    public:
        virtual bool has(int) const = 0;
};

#endif

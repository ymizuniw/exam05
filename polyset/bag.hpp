#ifndef BAG_HPP
#define BAG_HPP

class bag {
    public:
        virtual ~bag() {}
        virtual void insert(int) = 0;
        virtual void insert(int *, int) = 0;
        virtual void print() = 0;
        virtual void clear() = 0;
};

#endif

#ifndef TREE_BAG_HPP
#define TREE_BAG_HPP

#include "bag.hpp"

class tree_bag: public virtual bag {
private:
    struct node {
        node *l;
        node *r;
        int   value;
    } *tree;
public:
    tree_bag();
    tree_bag(const tree_bag &other);
    tree_bag &operator=(const tree_bag &other);
    ~tree_bag();
    static void copyTree(node *&dst, node *src);
    static void destroyTree(node *&dst);
    static void do_insert(node *&dst, int n);
    static void do_print(node *src);
    static bool do_contains(node *src, int);
    void insert(int);
    void insert(int *, int);
    void print();
    void clear();
    bool contains(int) const;
};

#endif

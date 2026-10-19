#ifndef TREE_BAG_HPP
#define TREE_BAG_HPP

#include "bag.hpp"

class tree_bag : public virtual bag{
    protected:
        struct node {
            node *l;
            node *r;
            int value;
        } * tree;

    private:
        static void copyTree(node **dst_tree, node *src_tree);
        static void destroyTree(node *);
        static void insertNode(node **, int);
        static void printTree(node *);
    public:
        tree_bag();
        tree_bag(const tree_bag &other);
        tree_bag &operator=(const tree_bag &other);
        ~tree_bag();
        void insert(int);
        void insert(int *, int);
        void print();
        void clear();
};

#endif

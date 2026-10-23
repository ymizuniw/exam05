#include "tree_bag.hpp"

#include <cstddef>
#include <iostream>

tree_bag::tree_bag(){
    tree = NULL;
}

void tree_bag::copyTree(node *&dst, node *src)
{
    /*
            a
        b       c
    d         e     f
    */
    // copy a

    // copy b
        // copy d
    // copy c
        // copy e
        // copy f

    if (src==NULL)
        return;
    // if (dst)
        // destroyTree(dst);
    // alloc node and copy members

    dst = new node;
    dst->l =NULL;
    dst->r = NULL;
    dst->value = src->value;

    if (src->l)
        copyTree(dst->l, src->l);
    if (src->r)
        copyTree(dst->r, src->r);
}

tree_bag::tree_bag(const tree_bag &other){
    // copy tree
    copyTree(this->tree,other.tree);
}
tree_bag &tree_bag::operator=(const tree_bag &other){
    // copy tree
    if (this==&other)
        return *this;
    copyTree(this->tree, other.tree);
    return *this;
}

void tree_bag::destroyTree(node *&dst)
{
    if (dst==NULL)
        return ;
    if (dst->l)
        delete dst->l;
    if (dst->r)
        delete dst->r;
    delete dst;
    // del l
    // del r
    // del itself
}
tree_bag::~tree_bag(){
    // destroy tree
    destroyTree(this->tree);
}

void tree_bag::do_insert(node *&dst, int n){

    // if cur is NULL, copy n
    if (dst==NULL)
    {
        // alloc node
        node *src = new node;
        src->l = NULL;
        src->r = NULL;
        src->value = n;
        dst = src;
    }
    else if (dst->value>n){
        do_insert(dst->l,n);
    }
    else if (dst->value<=n){
        do_insert(dst->r,n);
    }
    // elif cur->l is not NULL, and if (smaller than cur->value), insert(cur->l)
    // elif cur->r is not NULL, and if (larger than cur->value), insert(cur->r)
}

void tree_bag::insert(int n){
    do_insert(tree, n);
}
void tree_bag::insert(int *arr, int size){
    for (int i=0;i<size;++i){
        do_insert(tree, arr[i]);
    }
}

void tree_bag::do_print(node *src){
    if (src==NULL)
        return ;
    std::cout << src->value;
    if (src->l || src->r)
        std::cout << " ";
    if (!src->l && !src->r)
        std::cout << std::endl;
    if (src->l)
        do_print(src->l);
    if (src->r)
        do_print(src->r);
}

void tree_bag::print(){
    do_print(tree);
}
void tree_bag::clear(){
    destroyTree(tree);
}

bool tree_bag::do_contains(node *src, int n){
    // null src
    if (src==NULL)
        return false;
    // src
    if (src->value==n)
        return true;
    bool found = false;
    // src->l
    if (src->l)
    {
        found = do_contains(src->l, n);
        if (found)
            return true;
    }
    // dst->r
    if (src->r)
    {
        found = do_contains(src->r, n);
        if (found)
            return true;
    }
    return false;
}
bool tree_bag::contains(int n) const{
    return do_contains(tree, n);
}

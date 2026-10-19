#include "tree_bag.hpp"
#include <cstddef>
#include <iostream>

void tree_bag::copyTree(node **dst, node *src)
{
    if (src==NULL)
    {
        *dst = NULL;
        return ;
    }
    *dst = new node;
    (*dst)->l = NULL;
    (*dst)->r = NULL;
    (*dst)->value = src->value;
    copyTree(&(*dst)->l, src->l);
    copyTree(&(*dst)->r, src->r);
}

void tree_bag::destroyTree(node *tree)
{
    if (tree==NULL)
        return ;
    destroyTree(tree->l);
    destroyTree(tree->r);
    delete tree;
}

void tree_bag::insertNode(node **tree, int n)
{
    while (*tree)
        tree = (n < (*tree)->value) ? &(*tree)->l : &(*tree)->r;
    *tree = new node;
    (*tree)->l = NULL;
    (*tree)->r = NULL;
    (*tree)->value = n;
}

void tree_bag::printTree(node *tree)
{
    if (tree==NULL)
        return ;
    printTree(tree->l);
    std::cout << tree->value << " ";
    printTree(tree->r);
}

tree_bag::tree_bag(): tree(NULL){

}
tree_bag::tree_bag(const tree_bag &other): tree(NULL){
    copyTree(&tree, other.tree);
}
tree_bag &tree_bag::operator=(const tree_bag &other){
    if (this==&other)
        return *this;
    node *tmp = NULL;
    copyTree(&tmp, other.tree);
    destroyTree(tree);
    tree = tmp;
    return *this;
}
tree_bag::~tree_bag(){
    destroyTree(tree);
}

void tree_bag::insert(int n){
    insertNode(&tree, n);
}
void tree_bag::insert(int *arr, int n){
    if (!arr)
        return ;
    for (int i=0;i<n;++i)
        insertNode(&tree, arr[i]);
}
void tree_bag::print(){
    printTree(tree);
    std::cout << std::endl;
}
void tree_bag::clear(){
    destroyTree(tree);
    tree = NULL;
}

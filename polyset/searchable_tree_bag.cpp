#include <cstddef>
#include "searchable_tree_bag.hpp"
#include "searchable_bag.hpp"
#include "tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag(): searchable_bag(), tree_bag(){

}
searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &other): searchable_bag(), tree_bag(other){

}
searchable_tree_bag &searchable_tree_bag::operator=(const searchable_tree_bag &other){
    if (this==&other)
        return (*this);
    tree_bag::operator=(other);
    return (*this);
}
searchable_tree_bag::~searchable_tree_bag(){

}

bool searchable_tree_bag::search_val(node *tree, int n)
{
    if (tree==NULL)
        return (false);
    if (tree->value==n)
        return (true);
    return (search_val(tree->l, n) || search_val(tree->r, n));
}

bool searchable_tree_bag::has(int n) const{
    return (search_val(tree, n));
}

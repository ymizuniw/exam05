#include "searchable_tree_bag.hpp"
#include "tree_bag.hpp"
#include <iostream>

int main() {
    tree_bag a;
    int arr[] = {1,2,3,4,6,5,7,8,9};
    int size=sizeof(arr)/sizeof(int);

    a.insert(1);
    a.insert(2);
    a.print();

    tree_bag b;
    b.insert(arr, size);
    b.print();
    return 0;
}

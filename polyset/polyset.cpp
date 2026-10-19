#include "set.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"
#include <iostream>

/*
    virtual ~class();

    setting virtual destructor in parent class, then derived class's destructor will be called when parent class destctor is called.
*/

/*
    from base => concrete : downcast
*/

/*

    class Base {}
    class Derived1 : virtual Base {}
    class Derived2 : virtual Base {}
    class Derived3 : Derived1, Derived2 {}
    base class => 
*/

/*
    interface:
        insert(int);
        insert(int *, int)
        print();
        clear();
*/

/*
    interface class bag
    interface class array_bag
    interface class tree_bag
    
    abstract base class searchable_bag
    concrete class searchable_array_bag
    concrete class searchable_tree_class

    wrapper class set{}
*/

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    int arr[] = {5, 3, 8, 1};

    searchable_array_bag ab;
    searchable_tree_bag tb;
    set sets[2] = {set(ab), set(tb)};   // same code path, different bag
    for (int i = 0; i < 2; ++i)
    {
        sets[i].insert(arr, 4);
        sets[i].insert(3);
        sets[i].print();
        std::cout << sets[i].has(8) << sets[i].has(9) << std::endl;
        set copy(sets[i]);              // shares the bag
        copy.clear();
        std::cout << sets[i].has(8) << std::endl;
    }
    return (0);
}

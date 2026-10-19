#include "set.hpp"

set::set(searchable_bag &bag): bag(bag){
}
set::set(const set &other): bag(other.bag){
}
set::~set(){
}

void set::insert(int n){
    bag.insert(n);
}
void set::insert(int *arr, int n){
    bag.insert(arr, n);
}
void set::print(){
    bag.print();
}
void set::clear(){
    bag.clear();
}
bool set::has(int n) const{
    return (bag.has(n));
}
const searchable_bag &set::get_bag() const{
    return (bag);
}

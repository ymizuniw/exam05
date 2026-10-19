#include "searchable_array_bag.hpp"
#include "array_bag.hpp"
#include "searchable_bag.hpp"
#include <cstdlib>

searchable_array_bag::searchable_array_bag(): array_bag(), searchable_bag(){
    
}
searchable_array_bag::searchable_array_bag(const searchable_array_bag &other): array_bag(other), searchable_bag(){
    
}
searchable_array_bag &searchable_array_bag::operator=(const searchable_array_bag &other){
    if (this==&other)
        return *this;
    array_bag::operator=(other);
    return *this;
}

searchable_array_bag::~searchable_array_bag(){
    
}

bool searchable_array_bag::has(int n) const{
    for (int i=0;i<size;++i)
    {
        if (data[i]==n)
            return (true);
    }
    return(false);
}

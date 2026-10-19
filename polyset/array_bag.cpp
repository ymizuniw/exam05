#include "array_bag.hpp"
#include <cstddef>
#include <exception>
#include <iostream>

    // private:
    //     int *data;
    //     int size;
    // public:
    //     void insert(int);
    //     void insert(int *, int);
    //     void print();
    //     void clear();

array_bag::array_bag(): data(0), size(0){

}

array_bag::array_bag(int *data, int size): data(0), size(0){
    if (data && size > 0)
    {
        this->data = new int[size];
        for (int i=0;i<size;++i)
            this->data[i] = data[i];
        this->size = size;
    }
}

array_bag::array_bag(const array_bag &other): data(0), size(0){
    if (other.data && other.size > 0)
    {
        data = new int[other.size];
        for (int i=0;i<other.size;++i)
            data[i] = other.data[i];
        size = other.size;
    }
}
array_bag &array_bag::operator=(const array_bag &other){
    if (this==&other)
        return (*this);
    int *tmp = 0;
    if (other.data && other.size > 0)
    {
        tmp = new int[other.size];
        for (int i=0;i<other.size;++i)
            tmp[i] = other.data[i];
    }
    delete[] data;
    data = tmp;
    size = tmp ? other.size : 0;
    return (*this);
}

array_bag::~array_bag(){
    delete[] data;
}

void array_bag::insert(int n){
    int *tmp = new int[size+1];
    for (int i=0;i<size;++i)
    {
        tmp[i] = data[i];
    }
    tmp[size] = n;
    delete[] data;
    data = tmp;
    size++;
}

void array_bag::insert(int *arr, int n){
    if (!arr || n <= 0)
        return ;
    int *tmp = new int[size+n];
    for (int i=0;i<size;++i)
        tmp[i] = data[i];
    for (int i=0;i<n;++i)
        tmp[size+i] = arr[i];
    delete[] data;
    data = tmp;
    size += n;
}

void array_bag::print(){
    for (int i=0;i<size;++i)
    {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

void array_bag::clear(){
    delete[] data;
    data = 0;
    size = 0;
}

int main(void)
{
    array_bag arr;
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);
    // arr.print();

    array_bag arr2(arr);
    arr2.print();
    return (0);
}

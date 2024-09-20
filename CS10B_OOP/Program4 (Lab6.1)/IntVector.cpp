#include "IntVector.h"
#include <stdexcept>
#include <iostream>

using namespace std;

//Constructors
IntVector::IntVector(unsigned capacity, int value){
    if (capacity > 0){
        _data = new int[capacity];
        for (unsigned i = 0; i < capacity; i++){
            _data[i] = value;
        }

        //_data = instancedData;
        //cout << value << endl;
    }else{
        _data = nullptr;
    }
    
    _size = capacity;
    _capacity = capacity;
}


//Destructor
IntVector::~IntVector(){
    if (_data != nullptr){
        delete[] _data;
    }
}

//Private Helper Functions
void IntVector::expand(){
    _capacity *= 2;
    if (_capacity == 0){ _capacity = 1;}

    int *tempVar = new int[_capacity];

    for (unsigned i = 0; i < _size; i++){
        tempVar[i] = _data[i];
    }

    delete[] _data;

    _data = tempVar;
}

void IntVector::expand(unsigned amount){
    _capacity += amount;
    int *tempVar = new int[_capacity];

    for (unsigned i = 0; i < _size; i++){
        tempVar[i] = _data[i];
    }

    delete[] _data;

    _data = tempVar;
}

//Accessors
unsigned IntVector::size() const{
    return _size;
}

unsigned IntVector::capacity() const{
    return _capacity;
}

bool IntVector::empty() const{
    return _size == 0;
}

const int & IntVector::at(unsigned index) const{
    if (index >= _size || _data == nullptr){
        throw out_of_range("IntVector::at_range_check");
    }
    return _data[index];
}

const int & IntVector::front() const{
    return _data[_size-1];
}

const int & IntVector::back() const{
    return _data[0];
}

//Mutators
int & IntVector::at(unsigned index){
    if (index >= _size || _data == nullptr){
        throw out_of_range("IntVector::at_range_check");
    }
    return _data[index];
}

int & IntVector::front(){
    return _data[_size-1];
}

int & IntVector::back(){
    return _data[0];
}

void IntVector::insert(unsigned index, int value){
    if (index > _size){
        cout << index << endl;
        throw out_of_range("IntVector::insert_range_check");
    }
    
    if (_size + 1 > _capacity){
        expand();
    }

    for (unsigned i = index; i < _size; i++){
        _data[i+1] = _data[i];
    }

    _data[index] = value;

    _size += 1;
}

void IntVector::erase(unsigned index){
    if (index >= _size || _data == nullptr){ //Unsure we should allow insertion when size is 0 to element 0
        throw out_of_range("IntVector::erase_range_check");
    }

    for (unsigned i = index; i < _size; i++){
        _data[i] = _data[i+1];
    }

    _size -= 1;
}

void IntVector::push_back(int value){
    if (_size + 1 > _capacity){
        expand();
    }

    _data[_size] = value;

    _size += 1;
}

void IntVector::pop_back(){
    _size -= 1;
}

void IntVector::clear(){
    _size = 0;
}

//room for assign

void IntVector::resize(unsigned size, int value){
    if (size < _size){
        _size = size;
        return;
    }

    if (size < _capacity){
        
        for (unsigned i = _size; i < size; i++){
            _data[i] = value;
        }

        _size = size;
        return;
    }

    unsigned storageNeeded = size - _capacity;
    if (storageNeeded > _capacity){
        //cout << 1 << endl;
        expand(storageNeeded);
    }else{
        expand();
    }

    for (unsigned i = _size; i < size; i++){
        _data[i] = value;
    }

    _size = size;
}

void IntVector::reserve(unsigned n){
    if (_capacity < n){
        unsigned diff = n - _capacity;
        expand(diff);
    }
}

void IntVector::assign(unsigned n, int value){
    if (n > _capacity){
        unsigned storageNeeded = n - _capacity;
        if (storageNeeded > _capacity){
            expand(storageNeeded);
        }else{
            expand();
        }
    }
    
    for (unsigned i = 0; i < n; i++){
        _data[i] = value;
    }

    _size = n;
}
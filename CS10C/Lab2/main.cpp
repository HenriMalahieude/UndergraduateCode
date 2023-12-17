#include "IntList.h"
#include <iostream>

using namespace std;

int main(){
    IntList test;

    cout << "Is test empty? " << test.empty() << endl;

    test.push_back(2);
    test.push_front(1);
    test.push_back(3);
    test.push_front(0);

    cout << "Before: " << test << endl;

    test.pop_back();
    test.pop_front();
    cout << "After: " << test << endl;

    cout << "Reverse: ";
    test.printReverse();

    return 0;
}
#include <iostream>
#include <string>
#include "IntVector.h"

using namespace std;

void failCheck(string message){
    cout << "FAILED: " << message << endl;
}

void checkSizeCap(IntVector &iv, unsigned s, unsigned c, string check){
    if (iv.size() != s){
        cout << "Size of IntVec: " << iv.size() << endl;
        cout << "FAILED:  Size was improperly configured with " << check << endl;
    }
    if(iv.capacity() != c){
        cout << "Capacity of IntVec: " << iv.capacity() << endl;
        cout << "FAILED:  Capacity was improperly configured with " << check << endl;
    }
}

int main(){
    //Test Harness//
    cout << "Running Tests" << endl;

    /*
    //Default Constructor Test
    IntVector test1;

    checkSizeCap(test1, 0, 0, "default constructor");

    //User-Specified Capacity Constructor Test
    IntVector test2 = IntVector(5);
    checkSizeCap(test2, 5, 5, "specified constructor");

    for (int i = 0; i < 5; i++){
        if (test2.at(i) != 0){
            //cout << endl << "Issue at index " << i  << " val: " << test2.at(i) << endl;
            failCheck("Setting variable to default value");
            break;
        }
    }

    //User-Specified Capacity and Value Constructor Test
    IntVector test3 = IntVector(5, 5);

    for (int i = 0; i < 5; i++){
        if (test3.at(i) != 5){
            //cout << endl << "Issue at index " << i  << " val: " << test2.at(i) << endl;
            failCheck("Setting variable to specified value");
            break;
        }
    }

    test3.at(1) = 3;
    if (test3.at(1) != 3){
        failCheck("Could not set IntVector element with .at");
    }

    test3.front() = 3;
    if (test3.front() != 3){
        failCheck("Could not set IntVector element with .front");
    }

    test3.back() = 3;
    if (test3.back() != 3){
        failCheck("Could not set IntVector element with .back");
    }

    //Insertion/Erase Test
    IntVector test4 = IntVector(5, 5);

    test4.insert(1, 4);
    if (test4.at(1) != 4){
        failCheck("Could not set IntVector element with .insert");
    }

    checkSizeCap(test4, 6, 10, ".insert");

    for (unsigned i = 0; i < test4.size(); i++){
        if (test4.at(i) != 5 && i != 1){
            failCheck("Improperly set element with .insert");
            break;
        }
    }

    test4.erase(1);
    if (test4.at(1) != 5){
        failCheck("Did not erase IntVector element with .erase");
    }

    checkSizeCap(test4, 5, 10, ".erase");

    //Push Back Tets
    IntVector test5 = IntVector(5, 5);

    test5.push_back(4);
    if (test5.at(5) != 4){
        failCheck("Did not add IntVector element with .push_back");
    }
    checkSizeCap(test5, 6, 10, ".push_back");

    test5.pop_back();
    checkSizeCap(test5, 5, 10, ".pop_back");

    test5.resize(5);
    //checkSizeCap(test5, 5, 5, ".resize");

    test5.resize(100);
    checkSizeCap(test5, 100, 100, ".resize");
    for(unsigned i = 0; i < test5.size(); i++){
        if ((i > 4 && test5.at(i) != 5) || test5.at(i) != 0){
            cout << endl << "Issue at index " << i << " val: " << test5.at(i) << endl;
            failCheck("Did not properly set specified .resize value");
            break;
        }
    }*/

    IntVector *test = new IntVector(3);
    test->resize(100, 5);

    cout << test->size() << endl;
    cout << test->capacity() << endl;


    cout << "Tests Complete!" << endl;

    return 0;
}
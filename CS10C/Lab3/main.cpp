#include<iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index){
    T small = vals.at(index);
    unsigned smallI = index;
    
    for (unsigned i = index+1; i < vals.size(); i++){
        if (small > vals.at(i)){
            small = vals.at(i);
            smallI = i;
        }
    }

    return smallI;
}

template<typename T>
void selection_sort(vector<T> &vals){
    for (unsigned i = 0; i < vals.size(); i++){
        unsigned min = min_index(vals, i);
        
        T temp = vals.at(min);
        vals.at(min) = vals.at(i);
        vals.at(i) = temp;
    }
}

template<typename T>
T getElement(vector<T> vals, int index){
    return vals.at(index);
}

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

int main(){

    //Part B
     srand(time(0));
     vector<char> vals = createVector();
     char curChar;
     int index;
     int numOfRuns = 10;
     // i-- = i = i - 1 vs i++ = (i = i + 1)
     //++i vs i++
     //--numOfRuns >= 0
     //numOfRuns-- >= 0
     while(--numOfRuns >= 0){
         cout << "Enter a number: " << endl;
         cin >> index;
         try{
            curChar = getElement(vals,index);
            cout << "Element located at " << index << ": is " << curChar << endl;
         }
         catch(const std::out_of_range& excpt){
            cout <<"out of range exception occured" << endl;
         }
    }
    return 0;
}
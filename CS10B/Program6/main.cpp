#include "IntList.h"
#include "SortedSet.h"

#include <iostream>

using namespace std;

int main() {
   cout << "Enter a test number(1-5): ";
	int test;
	cin >> test;
	cout << endl;
   //tests constructor, destructor, push_front, pop_front, display
   if (test == 1) {
      cout << endl;
      cout << "set1 constructor called" << endl;
      
      SortedSet set1;

      cout << "adding 1! " << endl;
      set1.add(1);
      cout << "Set 1: " << set1 << endl;

      cout << "pushing back 2!" << endl;
      set1.push_back(2);
      cout << "Set1 : " << set1 << endl;

      cout << "Pushing front 3!" << endl;
      set1.push_front(3);
      cout << "Set1: " << set1 << endl;

      cout << "insert order 4" << endl;
      set1.insert_ordered(4);
      cout << "Set1: " << set1 << endl;

      cout << "1 in Set? " << set1.in(1) << endl;
      cout << "4 in Set? " << set1.in(4) << endl;
      cout << "5 in Set? " << set1.in(5) << endl; 
   }
   if (test == 1) {
      cout << "set1 destructor called" << endl;
   }

   if (test == 2){
      SortedSet set2;
      set2.add(1);
      set2.add(2);
      set2.add(4);

      SortedSet set3;
      set3.add(1);
      set3.add(3);
      set3.add(5);

      cout << "Union: " << (set2 | set3) << endl;
      cout << "Inter: " << (set2 & set3) << endl;

      SortedSet set4 = set3;

      set4 |= set2;
      set3 &= set2;
      
      cout << "Mutator Union: " << set4 << endl;
      cout << "Mutator Inter: " << set3 << endl;
   }

   return 0;
}
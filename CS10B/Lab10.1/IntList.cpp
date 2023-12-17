#include "IntList.h"

void IntList::distanceFrom(int key) {
   searchAndModify(head, key);
}


int IntList::searchAndModify(IntNode *curr, int key) {
   if (curr == nullptr || curr->data == key){
      return 1;
   }
   int d = searchAndModify(curr->next, key);
   curr->data = d;
   
   return d + 1;
}
#include "IntList.h"

#include <ostream>

using namespace std;

IntList::IntList() : head(nullptr) {}


void IntList::push_front(int val) {
   if (!head) {
      head = new IntNode(val);
   } else {
      IntNode *temp = new IntNode(val);
      temp->next = head;
      head = temp;
   }
}

ostream & operator<<(ostream &o, const IntList &iL){
   if (iL.head == nullptr){
      return o;
   }
   o << iL.head->value;
   o << iL.head->next;
   return o;
}

bool IntList::exists(int v) const{
   return exists(head, v);
}

bool IntList::exists(IntNode *iN, int v) const{
   if (iN == nullptr){
      return false;
   }else if (iN->value == v){
      return true;
   }else{
      return exists(iN->next, v);
   }
}

ostream & operator<<(ostream &o, IntNode *iN){
   if (iN != nullptr){
      o << " " << iN->value;
      o << iN->next;
   }
   return o;
}
#include "SortedSet.h"

//Generation
SortedSet::SortedSet() : IntList(){}

SortedSet::SortedSet(const SortedSet &set) : IntList(set){}

SortedSet::SortedSet(const IntList &list): IntList(list){
    remove_duplicates();
    selection_sort();
}

SortedSet::~SortedSet(){
    clear();
}

//Accessors
bool SortedSet::in(int value) const{
    IntNode *temp = head;
    while(temp != nullptr){
        if (temp->value == value){
            return true;
        }else if (temp->value > value){
            return false;
        }

        temp = temp->next;
    }

    return false;
}

SortedSet SortedSet::operator|(const SortedSet &rhs) const{
    SortedSet un = SortedSet(*this);
    
    IntNode *temp = rhs.head;
    while(temp != nullptr){
        un.add(temp->value);
        temp = temp->next;
    }

    return un;
}

SortedSet SortedSet::operator&(const SortedSet &rhs) const{
    SortedSet in = SortedSet();
    
    IntNode *tempL, *tempR;
    tempL = head;
    tempR = rhs.head;
    while(tempL != nullptr && tempR != nullptr){
        (tempL->value == tempR->value) ? in.add(tempL->value) : void();
        
        tempL = tempL->next;
        tempR = tempR->next;
    }

    return in;
}

//Mutators
void SortedSet::add(int value){
    if (in(value)) return;
    
    //cout << "bruh" << endl;
    IntList::insert_ordered(value);
    //cout << "bruh1" << endl;
}

void SortedSet::push_front(int value){
    add(value);
}

void SortedSet::push_back(int value){
    add(value);
}

void SortedSet::insert_ordered(int value){
    add(value);
}

SortedSet SortedSet::operator|=(const SortedSet &rhs){
    SortedSet bruh = *this | rhs;
    
    clear();
    
    *this = bruh;

    return bruh;
}

SortedSet SortedSet::operator&=(const SortedSet &rhs){
    SortedSet bruh = *this & rhs;

    clear();

    *this = bruh;

    return bruh;
}
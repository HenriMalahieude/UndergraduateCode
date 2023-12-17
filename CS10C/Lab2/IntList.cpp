//Programmed by Henri Malahieude
//Programmed by Pu Sun
#include "IntList.h"
#include <iostream>

IntList::IntList(){
    dummyHead = new IntNode(-1);
    dummyTail = new IntNode(-1);
    
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
}

IntList::~IntList(){
    IntNode *cur = dummyHead;
    while (cur != nullptr && cur != 0){
        IntNode* temp = cur->next;
        delete cur;
        cur = temp;
    }
}

void IntList::push_front(int value){
    IntNode *add = new IntNode(value);

    add->next = dummyHead->next;
    dummyHead->next = add;
    add->prev = dummyHead;
    add->next->prev = add;
}

void IntList::pop_front(){
    IntNode *temp = nullptr;

    if (dummyHead->next != dummyTail){
        temp = dummyHead->next;

        dummyHead->next = temp->next;
        dummyHead->next->prev = dummyHead;

        delete temp;
        temp = nullptr;
    }
}

void IntList::push_back(int value){
    IntNode *add = new IntNode(value);

    add->prev = dummyTail->prev;
    dummyTail->prev = add;
    add->next = dummyTail;
    add->prev->next = add;
}

void IntList::pop_back(){
    if(!empty()){
    IntNode *temp = dummyTail->prev;
    dummyTail->prev = temp->prev;
    temp->prev->next = dummyTail;

    delete temp;
    temp = nullptr;
    }
    return;
}

bool IntList::empty() const{
    if(dummyHead->next == dummyTail && dummyTail->prev == dummyHead){
        return true;
    }
    else{
        return false;
    }
}

ostream & operator<<(ostream &out, const IntList &rhs){
    if(!rhs.empty()){
        IntNode *c = rhs.dummyHead->next;
        out<< c->data;
        while(c->next != rhs.dummyTail){
            c = c->next;
            out << " " << c->data;
        }
    }
    return out;
}

void IntList::printReverse() const{
    if(!empty()){
        IntNode *c = dummyTail->prev;
        cout << c->data;
        while (c->prev != dummyHead)
        {
            c= c->prev;
            cout <<" "<< c->data;
        }
        
    }
}
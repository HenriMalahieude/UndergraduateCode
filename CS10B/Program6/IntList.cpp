#include <vector>

#include "IntList.h"

using namespace std;

//Constructors
IntList::IntList(){
    head = nullptr;
    tail = nullptr;
}

IntList::IntList(const IntList &cpy){
    head = nullptr;
    tail = nullptr;
    copy(cpy);
}

//Equal Constructor
IntList & IntList::operator=(const IntList &cpy){
    if (this != &cpy){
        clear();
        copy(cpy);
    }
    
    return *this;
}

//Destructor
IntList::~IntList(){
    clear();
}

//Private Methods
//void IntList::deepCopy(const IntList &cpy){}

IntNode* IntList::min(IntNode *node){
    return nullptr;
}

void IntList::copy(const IntList &list){ 
    IntNode *ptr = list.head;
    while (ptr != nullptr){
        push_back(ptr->value);

        ptr = ptr->next;
    }
}

//Accessors
bool IntList::empty() const{
    return head == nullptr;
}

const int & IntList::front() const{
    return head->value;
}

const int & IntList::back() const{
    return tail->value;
}

//Mutators
void IntList::push_front(int value){
    if (head == nullptr){
        head = new IntNode(value);
        tail = head;
    }else {
        IntNode *temp = new IntNode(value);
        temp->next = head;

        head = temp;
    }
}

void IntList::pop_front(){
    if (head == nullptr) {return;}

    IntNode *ptr = head;

    head = ptr->next;

    delete ptr;
    //No need to set ptr to nullptr, it will be deinitialized afterwards
}

void IntList::push_back(int value){
    if (head == nullptr){
        head = new IntNode(value);
        tail = head;
    } else {
        IntNode *temp = new IntNode(value);

        tail->next = temp;
        tail = temp;
    }
}

void IntList::clear(){
    IntNode *ptr;
    while(head != nullptr){
        ptr = head->next;

        delete head;

        head = ptr;
    }

    head = nullptr;
    tail = nullptr;
}

void IntList::insert_ordered(int value){
    //cout << "allal" << endl;
    if (head == nullptr){ IntList::push_front(value); return;}

    IntNode *last = head;
    IntNode *higher = head;
    while (higher != nullptr && higher->value < value){
        last = higher;
        higher = higher -> next;
    }

    if (higher == nullptr){
        IntList::push_back(value);
    }else{

        if (higher != head){
            IntNode *temp = new IntNode(value);
            last->next = temp;
            temp->next = higher;
        }else{
            IntNode *temp = new IntNode(value);
            head = temp;
            temp->next = higher;
        }
    }
}

//Methods
void IntList::selection_sort(){
    if (head == nullptr || head == tail){ return; }
    
    IntNode *i = head;
    IntNode *min = head->next;
    IntNode *j = i;

    //cout << endl;
    while(i != tail && i != nullptr){ //tail should happen first
        while(j != nullptr){
            if (j->value < min->value){
                min = j;
            }
            j = j->next;
        }
        
        //Debugging
        //cout << "i value: " << i->value << endl;
        //cout << "min value: " << min->value << endl;

        //swap
        int temp = i->value;
        i->value = min->value;
        min->value = temp;

        //reset
        i = i->next;
        min = i->next;
        j = i;
    }
    //cout << endl;
}

void IntList::remove_duplicates(){
    if (head == nullptr){ return; }
    vector<int> values(1, head->value);

    IntNode *last = head;
    IntNode *cur = head->next;
    while(cur != nullptr){
        bool del = false;
        for (unsigned i = 0; i < values.size(); i++){
            if (cur->value == values.at(i)){
                last->next = cur->next;
                delete cur;
                cur = last;
                del = true;
                break;
            }
        }

        if (!del){
            values.push_back(cur->value);
        }
        
        last = cur;
        cur = cur->next;
    }
    tail = last;
}

ostream & operator<<(ostream &out, const IntList &list){
    if (list.head == nullptr) { return out; }

    out << list.head->value;
    
    IntNode *ptr = list.head->next;
    while (ptr != nullptr){
        out << " " << ptr->value;
        ptr = ptr->next;
    }

    return out;
}
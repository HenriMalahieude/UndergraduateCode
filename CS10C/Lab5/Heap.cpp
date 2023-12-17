#include "Heap.h"
#include <iostream>

using namespace std;

Heap::Heap(){
    numItems = 0;
}

PrintJob* Heap::highest(){
    if(numItems>0){
        return arr[0];
    }else{
        return nullptr;
    }
}

void Heap::print(){
        cout << "Priority: " << arr[0]->getPriority();
        cout << ", Job Number: " << arr[0]->getJobNumber();
        cout << ", Number of Pages: " << arr[0]->getPages() << endl;
}


void Heap::swap(int i, int j){
    PrintJob* tmp = arr[i];
    arr[i]= arr[j];
    arr[j]= tmp;
}

void Heap::trickleDown(int i){
    for(int j = 0; j<numItems;j++){
        if(arr[i]->getPriority() < arr[j]->getPriority()){
            swap(i,j);
        }
    }
}

void Heap::dequeue(){
    if(numItems == 1){
        arr[0] = 0;
        numItems = 0;
        return;
    }
    if(numItems > 0){
        arr[0] = arr[numItems-1];
        arr[numItems -1] = 0;
        numItems--;
        trickleDown(0);
    }
}

int Heap::getparent(int i){
    return (i-1)/2;
}
void Heap::enqueue(PrintJob *cur){
    if(numItems < MAX_HEAP_SIZE){
        arr[numItems] = cur;
        int i = numItems;
        numItems++;
    
    while((i!= 0)&&(arr[getparent(i)]->getPriority()<arr[i]->getPriority()) ){
        swap(getparent(i),i);
        i = getparent(i);
    }
    }
}
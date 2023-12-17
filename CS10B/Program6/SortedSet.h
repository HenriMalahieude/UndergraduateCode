#include "IntList.h"

#ifndef SORTEDSET_H
#define SORTEDSET_H

class SortedSet : public IntList{
 public:
    //Generation
    SortedSet();
    SortedSet(const SortedSet &);
    SortedSet(const IntList &);

    ~SortedSet();

    //Accessors
    bool in(int) const;
    SortedSet operator|(const SortedSet &) const;
    SortedSet operator&(const SortedSet &) const;

    //Mutators
    void add(int);
    void push_front(int);
    void push_back(int);
    void insert_ordered(int);
    SortedSet operator|=(const SortedSet &);
    SortedSet operator&=(const SortedSet &);
};

#endif
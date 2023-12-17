#ifndef INTLIST_H
#define INTLIST_H

#include <iostream>
using namespace std;

struct IntNode {
	int value;
	IntNode *next;
	IntNode(int value) : value(value), next(nullptr) { }
};

class IntList {
 private:
	IntNode *head;
	IntNode *tail;

	void deepCopy(const IntList &);
 public:
	//Constructors
	IntList();
	IntList(const IntList &); //Copy Construct

	//Equal Constructor
	IntList & operator=(const IntList &);
	
	//Destructor
	~IntList();
	
	//Accessors
	bool empty() const;
	const int & front() const;
	const int & back() const;

	//Mutators
	void push_front(int);
	void pop_front();
	void push_back(int);
	void clear();
	void insert_ordered(int);

	//Methods
	void selection_sort();
	void remove_duplicates();
	friend ostream & operator<<(ostream &, const IntList &);
};

#endif

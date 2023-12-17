#include <vector>
#include <list>
#include <string>

using namespace std;

struct Element{
	string data;
	int count;
	//void operator<<(ostream out) const{ out << data << " " << count << endl; };
	bool operator==(Element rhs) const{ return data == rhs.data; };
	Element(string d): data(d), count(1){};
};

class Hashtable {
	list<Element> *table; //array of lists of Elements
	int items;
	int size;
	int hashFunction(string);
	void growAndRemap(int);

	public:
		Hashtable() : table(new list<Element>[20]()), size(20), items(0){};
		void addMember(string);
		void removeMember(string);
		void getHighestCount();
};

/*int Hashtable::hashFunction(string in){
	int hash = 5;
	for (int i=0; i < in.size(); i++){
		hash = (hash * 3) + in.at(i);
	}
 
	return hash % size;
}

void Hashtable::growAndRemap(int){
	double loadFactor = (double)items / (double)size;
	if (loadFactor < 0.6 && items >= size){
		list<Element> *nArray = new list<Element>[size*2]();

		for (int i = 0; i < size; i++){
			for (list<Element>::iterator its = table[i].begin(); its != table[i].end(); advance(its, 1)){

			}
		}
	}
}

void Hashtable::addMember(string in){
	int hash = hashFunction(in);


}*/
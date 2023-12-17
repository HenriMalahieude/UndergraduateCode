#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

struct Element{
	string data;
	int count;
	friend ostream& operator<<(ostream& out, const Element &e){ return out << e.data << " " << e.count; };
	bool operator==(Element rhs) const{ return data == rhs.data; };
	Element(string d): data(d), count(1){};
};

void InsertionSort(vector<Element> &arr){
	for(unsigned i = 1; i < arr.size(); i++){
		unsigned j = i;
		while(j > 0 && arr.at(j).count > arr.at(j-1).count){
			Element temp = arr[j];
			arr[j] = arr[j-1];
			arr[j-1] = temp;
			--j;
		}
	}
}

int main(int argc, char *argv[]){
	ifstream inputFile("input.txt");

	if (!inputFile.is_open()){
		cout << "Error opening file" << endl;
		return 1;
	}

	vector<Element> words;

	string word = "";
	while (inputFile >> word){
		Element temp(word);
		vector<Element>::iterator its = find(words.begin(), words.end(), temp);
		if (its != words.end()){
			its->count++;
			continue;
		}

		words.push_back(temp);
	}

	InsertionSort(words);

	//TODO: Turn this into a ofstream instead of cout, which writes down the code/frequency
	for (unsigned i = 0; i < words.size(); i++){
		cout << words.at(i) << endl;
	}

	//TODO: "Zip" the file using their index in the sorted vector

	return 0;
}
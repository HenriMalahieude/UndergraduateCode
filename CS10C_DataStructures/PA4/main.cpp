#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <iterator>
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
	
	inputFile.close();
	InsertionSort(words);

	//TODO: Turn this into a ofstream instead of cout, which writes down the code/frequency
	ofstream outFS("code.txt");

	if(!outFS.is_open()){
		cout << "Error opening file" << endl;
		return 1;
	}
	
	map<string, int> Token_code;

	for (unsigned i = 0; i < words.size() && i < 30; i++){
		outFS << words.at(i) << " " << i+1 << endl;
		Token_code.insert(pair<string, int> (words.at(i).data, i+1));
	}

	outFS.close();
	

	//TODO: "Zip" the file using their index in the sorted vector

	/*
	cout <<"Token_code[the] is "<< Token_code["the"] <<endl;
	cout <<"Token_code[,] is "<< Token_code[","] <<endl; 
	cout <<"Token_code[.] is "<< Token_code["."] <<endl;  
	*/
	ifstream inFS("input.txt");
	ofstream zip("zip.txt");

	if(!inFS.is_open()){
		cout << "Error opening file" << endl;
		return 1;
	}

	if(!zip.is_open()){
		cout << "Error opening file" << endl;
		return 1;
	}

	string token;
	char follower;
	while(inFS >> token){	
		string numero = to_string(Token_code[token]);

		if (numero != "0"){
			zip << numero;
		}else{
			zip << token;
		}
		
		
		inFS.get(follower);
		zip << follower;
	}

	inFS.close();
	zip.close();

	return 0;
}
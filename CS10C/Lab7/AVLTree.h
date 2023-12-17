#include <string>
#include <iostream>
#include <fstream>
#include "Node.h"
using namespace std;



class BSTree{
	private:
		Node *root;
		void visualizeTree(ofstream &, Node*); //done
		Node* rotate(Node*,string,int); //done
		Node* rotateLeft(Node*); //done
		Node* rotateRight(Node*); //done
		void printBalanceFactors(Node*); //done
		Node* insert(Node* root, string d); //done
		int max(int a, int b); //done
		int height(Node*); //done
	public:
		BSTree():root(0){}; //done
		void insert(const string &); //done
		int balanceFactor(Node*); //done
		void printBalanceFactors(); //done
		void visualizeTree(const string &); //done
};
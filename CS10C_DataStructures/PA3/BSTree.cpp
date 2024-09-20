#include <iostream>
#include "BSTree.h"

BSTree::BSTree(){
	root = nullptr;
}

BSTree::~BSTree(){
	clear(root);
	root = nullptr;
}

void BSTree::clear(Node *n){
	if (n == nullptr){
		return;
	}

	clear(n->left);
	n->left = nullptr;
	clear(n->right);
	n->right = nullptr;

	delete n;
}

void BSTree::insert(const string &word){
	if (root == nullptr){
		root = new Node(word);
		return;
	}

	//cout << endl << "Inserting " << word;

	Node *cur = root;
	while (cur != nullptr){
		if (cur->data == word){ //if duplicate word
			//cout << endl << cur->data << " " << cur->count << endl;
			cur->count++;
			break;
		}

		if (word < cur->data){ //less than the current word
			if (cur->left != nullptr){
				cur = cur->left;
				continue;
			}

			cur->left = new Node(word);
			break;
		}else{ //greater than the current word
			if (cur->right != nullptr){
				cur = cur->right;
				continue;
			}

			cur->right = new Node(word);
			break;
		}
	}

	//cout << cur->data << " " << cur->count << endl;
}

int recursiveHeight(Node *n){
	if (n == nullptr){
		return 0;
	}
	int lef = recursiveHeight(n->left);
	int rig = recursiveHeight(n->right);

	if (lef > rig){
		return lef + 1;
	}
	return rig + 1;
}

int BSTree::height(const string &word) const{
	bool inTree = search(word);

	if (inTree){
		Node *cur = root;
		while (cur != nullptr){
			if (cur->data == word){
				break;
			}

			if (word < cur->data){
				cur = cur->left;
				continue;
			}

			cur = cur->right;
		}
		return (recursiveHeight(cur) - 1);
	}

	return -1;
}
void  BSTree::remove(const string &key){
	Node *par = nullptr;
	Node *cur = root;
	while (cur != nullptr)
	{
		if(cur->data == key){
			if(cur->count > 1){  //if duplicate word
				//cout << endl << cur->data << " " << cur->count << endl;
				cur->count--;
				break;
			}
			
			if(cur->left == nullptr && cur->right == nullptr){
				if(par == nullptr){
					root = nullptr;
				}
				else if(par->left == cur){
					par->left = nullptr;
				}
				else{
					par->right = nullptr;
				}
			}
			else if(cur->right == nullptr){// remove node with only left child
				if(par == nullptr){
					root = cur->left;
				}
				else if(par->left == cur){
					par->left = cur->left;
				}
				else{
					par->right = cur->left;
				}
			}
			else if(cur->left == nullptr){ // remove node with only right child
				if(par == nullptr){
					root = cur->right;
				}
				else if(par->left == cur){
					par->left = cur->right;
				}
				else{
					par->right = cur->right;
				}
			}
			else{   // remove Node with two children
				Node *suc = cur->right;
				while(suc->left !=nullptr){
					suc = suc->left;
				}
				string successorData = suc->data;
				remove(suc->data);
				cur->data = successorData;
			}
			return;
		}
		else if(cur->data < key){
			par = cur;
			cur = cur->right;
		}
		else{
			par = cur;
			cur = cur->left;
		}
	}
	return;
}

bool BSTree::search(const string &key) const{
	if(root == nullptr){
		return 0;
	}
	Node *cur = root;
	while(cur != nullptr){
		if(key == cur->data){
			//cout << endl << cur->data << " " << cur->count << endl;
			return true;
		}
		if(key > cur->data){
			cur = cur->right;
		}
		else{
			cur = cur->left;
		}
	}
	return false;	
}

string BSTree::largest() const{
	Node *cur = root;
	//cout<<"here"<< endl;
	if(cur == nullptr){
		
		return "";
	}
	while(cur->right!= nullptr){
		cur = cur->right;
	}
	return cur->data;
}

string BSTree::smallest() const{
	Node *cur = root;
	if(cur == nullptr){
		return "";
	}
	while(cur->left!= nullptr){
		cur = cur->left;
	}
	return cur->data;
}

void BSTree::preOrder() const{
	preOrder(root);
}

void BSTree::preOrder(Node *n) const{
	if (n == nullptr){return;}
	cout << n->data << "(" << n->count << "), ";
	preOrder(n->left);
	preOrder(n->right);
}

void BSTree::inOrder() const{
	inOrder(root);
}

void BSTree::inOrder(Node *n) const{
	if (n == nullptr){return;}
	inOrder(n->left);
	cout << n->data << "(" << n->count << ", ";
	inOrder(n->right);
}

void BSTree::postOrder() const{
	postOrder(root);
}

void BSTree::postOrder(Node *n) const{
	if (n == nullptr){return;}
	postOrder(n->left);
	postOrder(n->right);
	cout << n->data << "(" << n->count << ", ";
}
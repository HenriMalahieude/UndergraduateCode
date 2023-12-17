#include <iostream>
#include <fstream>
#include "AVLTree.h"

int BSTree::max(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

int BSTree::height(Node *n){
    if(n == nullptr){
        return 0;
    }
    return n->getHeight();
}

void BSTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS, root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void BSTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->getleft()){
            visualizeTree(outFS,n->getleft());
            outFS<<n->getdata() <<" -> " <<n->getleft()->getdata()<<";"<<endl;    
        }

        if(n->getright()){
            visualizeTree(outFS,n->getright());
            outFS<<n->getdata() <<" -> " <<n->getright()->getdata()<<";"<<endl;    
        }
    }
}

int BSTree::balanceFactor(Node* n){
    if(n == nullptr){
        return 0;
    }
    return height(n->getleft()) - height(n->getright());
}

Node* BSTree::rotate(Node* n,string d,int balance){
    if(balance > 1 && d < n->getleft()->getdata()){
        return rotateRight(n);
    }
    if(balance > 1 && d > n->getleft()->getdata()){
        n->setleft(rotateLeft(n->getleft()));
        return rotateRight(n);
    } 

    if(balance < -1 && d > n->getright()->getdata()){
        return rotateLeft(n);
    }
    if(balance < -1 && d < n->getright()->getdata()){
        n->setright(rotateRight(n->getright()));
        return rotateLeft(n);
    }

    return n;
}

Node* BSTree::rotateLeft(Node* n){
    Node* r = n->getright();
    Node* rl = r->getleft();

    r->setleft(n); 
    n->setright(rl);
    n->setHeight(max(height(n->getleft()),height(n->getright()))+1);
    r->setHeight(max(height(r->getleft()),height(r->getright()))+1);

    return r;
}

Node* BSTree::rotateRight(Node* n){
    Node* l = n->getleft();
    Node* lr = l->getright();

    l->setright(n);
    n->setleft(lr);
    n->setHeight(max(height(n->getleft()),height(n->getright()))+1);
    l->setHeight(max(height(l->getleft()),height(l->getright()))+1);

    return l;
}

void BSTree::insert(const string &d){
    root = insert(root,d);
}


Node* BSTree::insert(Node* r, string d){
    if(r == nullptr){
        return (new Node(d));
    }

    //cout << "uh" << endl;
    //cout << r->getdata() << endl;
    //cout << "hum" << endl;
    if( d < r->getdata()){
        //cout << "1!" << endl;
        r->setleft(insert(r->getleft(),d));
    }else if(d > r->getdata()){
        //cout << "2!" << endl;
        r->setright(insert(r->getright(),d));
    }else{
        //cout << "hm" << endl;
        return r;  // equal data;
    }
    r->setHeight(1+max(height(r->getleft()),height(r->getright())));

    int balance = balanceFactor(r);

    if(balance < -1 || balance > 1){
        return rotate(r,d,balance);
    }
    return r;
}

void BSTree::printBalanceFactors(){
    printBalanceFactors(root);
    cout << endl;
}

void BSTree::printBalanceFactors(Node *n){
    if (n != nullptr){
        printBalanceFactors(n->getleft());
        cout << n->getdata() << "(" << balanceFactor(n) << "), ";
        printBalanceFactors(n->getright());
        
    }
}
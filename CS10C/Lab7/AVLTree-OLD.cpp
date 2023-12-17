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
        return -1;
    }
    return balanceFactor(n->getleft()) - balanceFactor(n->getright());
}

Node* BSTree::rotate(Node* n,string d,int balance){
    if(balance > 1 && d < n->getleft()->getdata()){
        return rotateRight(n);
    }
    if(balance > 1 && d > n->getleft()->getdata()){
        n->setleft(rotateLeft(n->getleft()));
        return rotateRight(n);
    } 

    if(balance < -1 && d > n->getleft()->getdata()){
        return rotateLeft(n);
    }
    if(balance < -1 && d < n->getleft()->getdata()){
        n->setleft(rotateRight(n->getleft()));
        return rotateLeft(n);
    }

    return n;
}

Node* BSTree::rotateLeft(Node* n){
    Node* r = n->getright();
    Node* rl = r->getleft();

    r->setleft(n); 
    n->setright(rl);

    return r;
}

Node* BSTree::rotateRight(Node* n){
    Node* l = n->getleft();
    Node* lr = l->getright();

    l->setright(n);
    n->setleft(lr);

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
    int balance1 = balanceFactor(r);
    if( balance1 < 1){
        //cout << "1!" << endl;
        r->setleft(insert(r->getleft(),d));
    }else if(balance1 >= 1){
        //cout << "2!" << endl;
        r->setright(insert(r->getright(),d));
    }

    /*int balance = balanceFactor(r);

    if(balance < -1 || balance > 1){
        return rotate(r,d,balance);
    }*/
    return r;
}

void BSTree::printBalanceFactors(){
    printBalanceFactors(root);
    cout << endl;
}

void BSTree::printBalanceFactors(Node *n){
    if (n != nullptr){
        cout << "(";
        printBalanceFactors(n->getleft());
        cout << " " << n->getdata() << ":" << balanceFactor(n) << " ";
        printBalanceFactors(n->getright());
        cout << ")";
    }else{
        //cout << " ";
        return;
    }
}
#include "arithmeticExpression.h"
#include <stack>
#include <string>
#include <sstream>
#include <fstream>

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

arithmeticExpression::arithmeticExpression(const string &expression){
    infixExpression = expression;
    root = 0;
}

void arithmeticExpression::infix(TreeNode *Node){
    if(Node){
        if(Node->left != 0||Node->right != 0)
            cout<< "(";
        
        infix(Node->right);
        cout<<Node->data;
        infix(Node->left);
        if(Node->left != 0||Node->right != 0)
            cout<< ")";    
        
    }
    else{
        return;
    }
}

void arithmeticExpression::prefix(TreeNode *Node){
    if(Node){
        cout << Node->data;
        prefix(Node->right);
        prefix(Node->left);
    }
    else{
        return;
    }
}

void arithmeticExpression::postfix(TreeNode *Node){
    if(Node){
        postfix(Node->right);
        postfix(Node->left);
        cout << Node->data;
    }
    else{
        return;
    }
}

void arithmeticExpression::infix(){
    if(root == 0){
        return;
    }
    else{
        infix(root);
    }
}

void arithmeticExpression::prefix(){
    if(root == 0){
        return;
    }
    else{
        prefix(root);
    }
}

void arithmeticExpression::postfix(){
    if(root == 0){
        return;
    }
    else{
        postfix(root);
    }
}

void arithmeticExpression::buildTree(){
    string post = infix_to_postfix();

    stack<TreeNode*> nodes;

    int plusCount = 0;
    int divideCount = 0;
    int timeCount = 0;
    int minusCount = 0;
    int numCount = 0;
    for (unsigned i = 0; i < post.size(); i++){
        string key = "";
        
        if (post[i] == '+'){
            key = "plus" + to_string(plusCount++);
        }else if(post[i] == '/'){
            key = "divide" + to_string(divideCount++);
        }else if(post[i] == '*'){
            key = "multiply" + to_string(timeCount++);
        }else if (post[i] == '-'){
            key = "minus" + to_string(minusCount++);
        }else{
            key = post.substr(i, 1) + "_" + to_string(numCount++);
        }
        
        TreeNode* node = new TreeNode(post[i], key);
        
        if (priority(post[i]) > 0){
            node->left = nodes.top();
            nodes.pop();

            node->right = nodes.top();
            nodes.pop();
        }

        nodes.push(node);
    }

    root = nodes.top();
    nodes.pop();
}

void arithmeticExpression::visualizeTree(ofstream &file, TreeNode *node){
    if (node->left != nullptr && node->left != 0){
        file << node->key << " -> " << node->left->key << endl;
        visualizeTree(file, node->left);
    }

    if (node->right != nullptr && node->right != 0){
        file << node->key << " -> " << node->right->key << endl;
        visualizeTree(file, node->right);
    }
}
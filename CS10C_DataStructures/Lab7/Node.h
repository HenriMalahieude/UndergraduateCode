#include<string>

using namespace std;

class Node
{
private:
    Node *left;
	Node *right;
	string data;
	int height;
public:
    Node(string d);
    string getdata();
    int getHeight();
    void setHeight(int h);
    void setleft(Node* left);
    Node *getleft();
    void setright(Node* right);
    Node *getright();
};

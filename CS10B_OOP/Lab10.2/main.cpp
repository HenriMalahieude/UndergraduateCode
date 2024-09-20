#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool rCopy(string, string);
bool rpCopy(ifstream&, ofstream&);

int main(int argc, char *argv[]){
    if (argc == 3){
        rCopy(argv[1], argv[2]);
    }

    return 0;
}

bool rCopy(string inputName, string outputName){
    //Input
    ifstream in;
    in.open(inputName);
    if (!in.is_open()){
        cout << "Error opening " << inputName << endl;
        cout << "Copy not completed" << endl;
        return false;
    }

    ofstream out;
    out.open(outputName);
    if (!out.is_open()){
        cout << "Error opening " << outputName << endl;
        cout << "Copy not implemented" << endl;
        return false;
    }

    bool recurs = rpCopy(in, out);
    if (!recurs){
        return false;
    }

    in.close();
    out.close();
    return true;
}

bool rpCopy(ifstream &in, ofstream &out){
    char ch;
    in.get(ch);

    if (!in.good()){
        return true;
    }

    bool temp = rpCopy(in, out); //done
    out << ch;
    return temp;
}
#include <fstream>
#include "WordLadder.h"

WordLadder::WordLadder(const string &dictionary)
{
    ifstream inputFile;

    inputFile.open(dictionary);
    if (!inputFile.is_open())
    {
        cout << "Could not open file \n";
        return;
    }

    string word;
    while (inputFile >> word)
    {
        if (word.size() != 5)
        {
            cout << "Dictionary contains a non-five-letter word!\n";
            return;
        }

        dict.push_back(move(word));
    }
}

void inputStackOntoFile(stack<string> &st, const string &outputFile){
    ofstream out;

    out.open(outputFile);
    if(!out.is_open()){
        return;
    }

    //cout << "recieved " << st.size() << endl;
    unsigned max = st.size();
    for (unsigned i = 0; i < max; i++){
        //cout << st.top() << " " << i << " < " << st.size() << endl;
        out << st.top() << endl;
        st.pop();
    }
}

void failOntoFile(const string &outputFile){
    stack<string> fin;
    fin.push("No Word Ladder Found.");

    inputStackOntoFile(fin, outputFile);
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile)
{
    if (start == end){
        stack<string> fin;
        fin.push(start);

        inputStackOntoFile(fin, outputFile);
        return;
    }

    bool foundStart = false;
    bool foundEnd = false;
    for (list<string>::iterator it = dict.begin(); it != dict.end(); advance(it, 1)){
        if (*it == start){
            foundStart = true;
        }else if (*it == end){
            foundEnd = true;
        }
        if (foundStart && foundEnd){
            break;
        }
    }

    if (!foundStart || !foundEnd){
        failOntoFile(outputFile);
        return;
    }else{
        dict.remove(start);
        dict.remove(end);
    }

    queue<stack<string>> allStacks;

    stack<string> first;
    first.push(start);

    allStacks.push(first);
    while (allStacks.size() > 0){
        string word = allStacks.front().top();

        //cout << allStacks.front().size() << endl;

        for (list<string>::iterator it = dict.begin(); it != dict.end(); advance(it, 1)){
            if (letterDifference(word, *it)){
                stack<string> cop = allStacks.front();
                cop.push(*it);

                if (letterDifference(*it, end)){
                    cop.push(end);

                    inputStackOntoFile(cop, outputFile);
                    return;
                }

                dict.remove(*it);
                allStacks.push(cop);
            }
        }

        allStacks.pop();
    }

    failOntoFile(outputFile);
}

bool WordLadder::letterDifference(const string &a, const string &b)
{
    int diffCount = 0;
    for (int i = 0; i < 5; i++){
        if (a.at(i) != b.at(i)){
            diffCount++;
            
            if (diffCount > 1){ //optimize it minorly
                break;
            }
        }
    }

    return diffCount == 1;
}

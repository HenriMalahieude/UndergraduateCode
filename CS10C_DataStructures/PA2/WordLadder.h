#ifndef __WORDLAD_H
#define __WORDLAD_H
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>

using namespace std;

class WordLadder {

  private:
    list<string> dict;        //list of possible words in ladder
    void NooutputLadder(const string &outputFile);
    //Outputs whether the two words compared have exactly one letter difference
    bool letterDifference(const string &, const string &);

  public:
    /* Passes in the name of a file that contains a dictionary of 5-letter words.
       Fills the list (dict) with the words within this file. 
       If the file does not open for any reason or if any word within the file
       does not have exactly 5 characters, this function should output an
       error message and return.
    */
    WordLadder(const string &);

    /* Passes in two 5-letter words and the name of an output file.
       Outputs to this file a word ladder that starts from the first word passed in
       and ends with the second word passed in.
       If either word passed in does not exist in the dictionary (dict),
       this function should output an error message and return.
       Otherwise, this function outputs to the file the word ladder it finds or outputs
       to the file, the message, "No Word Ladder Found."
    */
    void outputLadder(const string &start, const string &end, const string &outputFile);
};

#endif
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

// Place charCnt prototype (declaration) here
int charCnt(string fileName, char ch);

int main() {
   string filename;
   char ch;
   int chCnt = 0;
   
   cout << "Enter the name of the input file: ";
   cin >> filename;
   cout << endl;
   cout << "Enter a character: ";
   cin.ignore(); // ignores newline left in stream after previous input statement
   cin.get(ch);
   cout << endl;

   chCnt = charCnt(filename, ch);   
   cout << "# of " << ch << "'s: " << chCnt << endl;
   
   return 0;
}

// Place charCnt implementation here
int charCnt(string fileName, char ch){
   int sum = 0;
   char curChar;
   
   ifstream inputFile;
   inputFile.open(fileName);

   if(!inputFile.is_open()){
      cout << "Error opening " << fileName << endl;
      exit(1);
   }

   while(inputFile.get(curChar)){
      if (curChar == ch){
         sum++;
      }
   }

   return sum;
}

#include <fstream>
#include <iostream>
#include <cstdlib> //needed for exit function

using namespace std;

// Place fileSum prototype (declaration) here
int fileSum(string fileName);

int main() {

   string filename;
   int sum = 0;
   
   cout << "Enter the name of the input file: ";
   cin >> filename;
   cout << endl;
   
   sum = fileSum(filename);

   cout << "Sum: " << sum << endl;
   
   return 0;
}

// Place fileSum implementation here
int fileSum(string fileName){
   int sum = 0;
   int tempNum = 0;
   ifstream inputFile;
   inputFile.open(fileName);

   if(!inputFile.is_open()){
      cout << "Error opening " << fileName << endl;
      exit(1);
   }

   while (inputFile >> tempNum){
      sum += tempNum;
   }

   return sum;
}
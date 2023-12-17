#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
   
   string inputFile;
   string outputFile;
   
   // Assign to inputFile value of 2nd command line argument
   inputFile = argv[1];

   // Assign to outputFile value of 3rd command line argument
   outputFile = argv[2];

   // Create input stream and open input csv file.
   ifstream fileRead;
   fileRead.open(inputFile);
   
   // Verify file opened correctly.
   // Output error message and return 1 if file stream did not open correctly.
   if(!fileRead.is_open()){
      cout << "Error opening " << inputFile << endl;
      return 1;
   }
   
   // Read in integers from input file to vector.
   vector<int> csvNumbers;
   int tempNum;
   char filler;
   while(fileRead >> tempNum){
      fileRead >> filler;
      csvNumbers.push_back(tempNum);
   }
   
   // Close input stream.
   fileRead.close();

   // Get integer average of all values read in.
   int sum = 0;
   int avg = 0;
   for (unsigned i = 0; i < csvNumbers.size(); i++){
      sum += csvNumbers.at(i);
   }
   avg = sum / csvNumbers.size();

   // Convert each value within vector to be the difference between the original value and the average.
   for(unsigned i = 0; i < csvNumbers.size(); i++){
      csvNumbers[i] -= avg;
   }

   // Create output stream and open/create output csv file.
   ofstream fileWrite;
   fileWrite.open(outputFile);

   // Verify file opened or was created correctly.
   // Output error message and return 1 if file stream did not open correctly.
   if(!fileWrite.is_open()){
      cout << "Error opening " << outputFile << endl;
      return 1;
   }
   
   // Write converted values into ouptut csv file, each integer separated by a comma.
   for (unsigned i = 0; i < csvNumbers.size(); i++){
      fileWrite << csvNumbers[i];
      if(csvNumbers.size()-1 > i){
         fileWrite << ',';
      }
   }
   
   // Close output stream.
   fileWrite.close();
   
   return 0;
}
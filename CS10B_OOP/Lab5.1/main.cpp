//include any standard libraries needed
#include <iostream>
#include <fstream>

using namespace std;

//  - Passes in an array along with the size of the array.
//  - Returns the mean of all values stored in the array.
double mean(const double array[], int arraySize);

//  - Passes in an array, the size of the array by reference, and the index of a value to be removed from the array.
//  - Removes the value at this index by shifting all of the values after this value up, keeping the same relative order of all values not removed.
//  - Reduces arraySize by 1.
void remove(double array[], int &arraySize, int index);


// - Passes in an array and the size of the array.
// - Outputs each value in the array separated by a comma and space, with no comma, space or newline at the end.
void display(const double array[], int arraySize);


const int ARR_CAP = 100;

int main(int argc, char *argv[]) {
   
   // verify file name provided on command line
   if (argc != 2){
      cout << "USAGE: " << argv[0] << " [file location]" << endl;
      return 1;
   }

   // open file and verify it opened
   ifstream fin;
   fin.open(argv[1]);

   if (!fin.is_open()){
      cout << "Error opening file" << endl;
      return 1;
   }

   // Declare an array of doubles of size ARR_CAP.
   const int ARR_CAP = 100;
   double arr[ARR_CAP];
   int arrSize = 0;
    
   // Fill the array with up to ARR_CAP doubles from the file entered at the command line.
   while(arrSize < ARR_CAP && fin >> arr[arrSize]){
      ++arrSize;
   }
    
   // Call the mean function passing it this array and output the 
   // value returned.
   cout << "Mean: " << mean(arr, arrSize) << endl << endl;
    
   // Ask the user for the index (0 to size - 1) of the value they want to remove.
   int rIndex = arrSize;
   cout << "Enter index of value to be removed (0 to " << arrSize - 1 << ") :" << endl;
	cin >> rIndex;
   cout << endl;

   // Call the display function to output the array.
   cout << "Before removing value: ";
   display(arr, arrSize);
   cout << endl << endl;
   
   // Call the remove function to remove the value at the index
   // provided by the user.
   remove(arr, arrSize, rIndex);
    
   // Call the display function again to output the array
   // with the value removed.
   cout << "After removing value: ";
   display(arr, arrSize);
   cout << endl << endl;
   
   // Call the mean function again to get the new mean
   cout << "Mean: " << mean(arr, arrSize) << endl;
   
	return 0;
}

double mean(const double array[], int arraySize){
   double sum = 0;
   for (int i = 0; i < arraySize; i++){
      sum += array[i];
   }
   return sum / arraySize;
}

void display(const double array[], int arraySize){
   cout << array[0];
   for (int i = 1; i < arraySize; i++){
      cout << ',' << array[i];
   }
}

void remove(double array[], int &arraySize, int index){
   if (index < 0 || index >= arraySize){
      return;
   }else if (index == (arraySize-1)){
      arraySize -= 1;
      return;
   }

   for (int i = index; i < arraySize; i++){
      array[i] = array[i+1];
   }

   arraySize -= 1;
}
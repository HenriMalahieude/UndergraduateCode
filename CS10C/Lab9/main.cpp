#include <iostream>
#include <chrono>

using namespace std;

const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds
const int NUMBERS_SIZE = 50000;

int Partition(int numbers[], int i, int k, int pivot);
void Quicksort_midpoint(int numbers[], int i, int k);
void Quicksort_medianOfThree(int numbers[], int i, int k);
void InsertionSort(int numbers[], int numberSize);
int genRandInt(int low, int high);
void fillArrays(int arr1[], int arr2[],int arr3[]);
void outputArray(int input[]);

int main(){
	//Set Up
	int numbers1[NUMBERS_SIZE];
	int numbers2[NUMBERS_SIZE];
	int numbers3[NUMBERS_SIZE];
	fillArrays(numbers1, numbers2, numbers3);

	//outputArray(numbers1);
	//outputArray(numbers2);
	//outputArray(numbers3);

	clock_t QM_Start = clock();
	Quicksort_medianOfThree(numbers1, 0, NUMBERS_SIZE - 1);
	clock_t QM_End = clock();
	int QM_elapsedTime = (QM_End - QM_Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
	cout << "Quicksort_midpoint took " << QM_elapsedTime << "ms" << endl;

	clock_t QMOT_Start = clock();
	Quicksort_medianOfThree(numbers2, 0, NUMBERS_SIZE - 1);
	clock_t QMOT_End = clock();
	int QMOT_elapsedTime = (QMOT_End - QMOT_Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
	cout << "Quicksort_medianOfThree took " << QMOT_elapsedTime << "ms" << endl;

	clock_t I_Start = clock();
	InsertionSort(numbers3, NUMBERS_SIZE);
	clock_t I_End = clock();
	int I_elapsedTime = (I_End - I_Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
	cout << "InsertionSort took " << I_elapsedTime << "ms" << endl;

	return 0;
}

int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}
void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

void outputArray(int input[]){
	//size_t n = sizeof(input)/sizeof(input[0]);
 
    // loop through the array elements
    for (int i = 0; i < NUMBERS_SIZE; i++) {
        cout << input[i] << ' ';
    }
	cout << endl;
}

int Partition(int numbers[], int i, int k, int pivot){
	bool done = false;
	int lowIndex = i;
	int highIndex = k;
	while(!done){
		while(numbers[lowIndex] < pivot){
			lowIndex++;
		}

		while(numbers[highIndex] > pivot){
			highIndex--;
		}
		
		if (lowIndex >= highIndex){
			done = true;
		}else{
			int holder = numbers[lowIndex];
			numbers[lowIndex] = numbers[highIndex];
			numbers[highIndex] = holder;

			lowIndex++;
			highIndex--;
		}
	}
	return highIndex;
}

void Quicksort_midpoint(int numbers[], int i, int k){
	if (i >= k){
		return;
	}

	int middle = (i+k)/2;
	int pivot = numbers[middle];

	int partitionMid = Partition(numbers, i, k, pivot);

	Quicksort_midpoint(numbers, i, partitionMid);
	Quicksort_midpoint(numbers, partitionMid + 1, k);
}

void Quicksort_medianOfThree(int numbers[], int i, int k){
	if (i >= k){
		return; //Low Is greater than or higher than High
	}

	int leftMost = numbers[i];
	int midPoint = numbers[(i+k)/2];
	int rightMost = numbers[k];

	int pivot = midPoint;
	if ((leftMost >= midPoint && leftMost < rightMost) || (leftMost < midPoint && leftMost >= rightMost)){
		pivot = leftMost;
	}else if ((rightMost >= leftMost && rightMost < midPoint) || (rightMost < leftMost && rightMost >= midPoint)){
		pivot = rightMost; 
	}

	int partitionMid = Partition(numbers, i, k, pivot);
	//cout << leftMost << " " << midPoint << " " << rightMost << " " << pivot << endl;
	Quicksort_medianOfThree(numbers, i, partitionMid); //Partition the bottom
	Quicksort_medianOfThree(numbers, partitionMid + 1, k); //Partition the top
}

void InsertionSort(int numbers[], int numberSize){
	for(int i = 1; i < numberSize; i++){
		int j = i;
		while(j > 0 && numbers[j] < numbers[j-1]){
			int temp = numbers[j];
			numbers[j] = numbers[j-1];
			numbers[j-1] = temp;
			--j;
		}
	}
}
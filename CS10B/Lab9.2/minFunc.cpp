#include "minFunc.h"
const int * min(const int arr[], int arrSize) {
    if (arrSize <= 0){
        return nullptr;
    }else if (arrSize == 1){
        return (arr);
    }

    const int *small = (arr + (arrSize-1));
    if (*small > arr[arrSize-2]){
        small = (arr + (arrSize-2));
    }

    const int *comparedSmall = min(arr, arrSize-1);
    if (comparedSmall != nullptr && *comparedSmall < *small){
        return comparedSmall;
    }

    return small;
}
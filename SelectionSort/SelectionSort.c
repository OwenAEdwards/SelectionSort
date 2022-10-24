#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval start,stop;

static int numSwaps=0,numComparisons=0;

int *randDataStructPopulator(int numOfElements,int *dataStruct) {
   srand(time(NULL));
   for (int i=0;i<=numOfElements;i++) {
      dataStruct[i]=rand()%100; // only numbers from 0 to 99
   }
   return dataStruct;
}

// NOTE: initially the swap() function wouldn't work but once I switched it to call by reference, it actually swaps the values of
// dataStruct instead of swapping dummy variables from call by value
void swap(int *a,int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void selectionSort(int numOfElements,int *dataStruct) {
    int currMinIdx; // we need a currMinIdx
    // we begin by looping through each individual element of the dataStruct
    for (int i=0;i<numOfElements-1;i++) {
        currMinIdx = i; // we start by setting the currMinIdx to the current dataStruct element's index (i)
        // then we loop through every element in the dataStruct from the current index plus one to the end, checking every element
        for (int j=i+1;j<numOfElements;j++) {
            numComparisons++;
            // we check if any of the elements from the current element of the dataStruct plus one to the end of the dataStruct
            // are less than the currMinIdx
            if (dataStruct[j]<dataStruct[currMinIdx]) {
                // if any element is less than the currMinIdx's element, then we set that element's index to become the new
                // currMinIdx
                currMinIdx=j;
            }
        }
        // now that we have found the currMinIdx in the entire dataStruct, we swap the original, start index with the currMinIdx
        if (currMinIdx!=i) {
            swap(&dataStruct[i],&dataStruct[currMinIdx]);
            numSwaps++;
        }
    }
}


int main() {

    int numOfElements;
    int *dataStruct;

    printf("Number of elements in data structure (N): ");
    scanf("%d",&numOfElements);

    dataStruct=(int*)malloc(numOfElements*sizeof(int)); // allocating space in the data structure

    dataStruct=randDataStructPopulator(numOfElements,dataStruct);

    gettimeofday(&start,NULL);
    selectionSort(numOfElements,dataStruct);
    gettimeofday(&stop,NULL);

    printf("The selection sort lasted: %fms\n",(((double)stop.tv_sec-start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);

    printf("The number of swaps was %d and the number of comparisons was %d\n",numSwaps,numComparisons);

    printf("For reference, the time complexity for selection sort is (%d*(%d-1))/2 or %d comparisons, which is approximately O(N^2) for larger N\n",
    numOfElements,numOfElements,(numOfElements*(numOfElements-1))/2);

    return 0;

}
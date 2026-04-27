/**
 *                 DESIGN AND ANALYSIS OF ALGORITHMS
 * PROGRAMMING PROJECT 1 - EMPIRICAL ANALYSIS OF SORTING ALGORITHMS
 *
 * Members:
 * Maria Francia Abdula
 * Angelica Bilaos
 * Melbert Bonina
 * Ginno Buenaobra
 * Isabela Nuñez
 * 
 */


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void restoreOriginal(unsigned long int *array, unsigned long int *originalArray, unsigned long int numElements);
void selectionSort(unsigned long int arr[], unsigned long int numElements);
// Insertion Sort
void insertionSort(unsigned long int arr[], unsigned long int numElements);
// Bubble Sort
void bubbleSort(unsigned long int arr[], unsigned long int numElements);
// Merge Sort
void mergeSort(unsigned long int arr[], unsigned long int left, unsigned long int right);
void merge(unsigned long int arr[], unsigned long int left, unsigned long int mid, unsigned long int right);
// Quick Sort
void quickSort(unsigned long int array[], int leftMostIndex, int rightMostIndex);
void medianOfThree(unsigned long int array[], int leftMostIndex, int rightMostIndex);
int partition(unsigned long int array[], int leftMostIndex, int rightMostIndex);
// Heap Sort
void heapSort(unsigned long int arr[], unsigned long int numElements);
void maxHeapify(unsigned long int arr[], unsigned long int i, unsigned long int numElements);
void convertToMaxHeap(unsigned long int arr[], unsigned long int numElements);
// Other Functions: 
int min(unsigned long int  arr[], long int k, long int numElements);
void swap(unsigned long int *item1, unsigned long int *item2);
void print(FILE *output, unsigned long int array[], unsigned long int numElements);

#define MAX_RANGE 1000000000

int main(){
    FILE *output;
    unsigned long int *originalArray;
    unsigned long int *array;
    int choice;   

    do{
        printf("\n\n\n            ╔═╗╔═╗╦═╗╔╦╗╦╔╗╔╔═╗  \n");     
        printf("            ╚═╗║ ║╠╦╝ ║ ║║║║║ ╦  \n");     
        printf("            ╚═╝╚═╝╩╚═ ╩ ╩╝╚╝╚═╝  \n");    
        printf("        ╔═╗╦  ╔═╗╔═╗╦═╗╦╔╦╗╦ ╦╔╦╗╔═╗\n");
        printf("        ╠═╣║  ║ ╦║ ║╠╦╝║ ║ ╠═╣║║║╚═╗\n");
        printf("        ╩ ╩╩═╝╚═╝╚═╝╩╚═╩ ╩ ╩ ╩╩ ╩╚═╝\n\n");
        printf("                 COMPARATIVE \n\n\n");
        printf("            Sort [Enter 1] \n");
        printf("            Exit [Enter 2] \n\n");
        printf("        Enter your choice: ");
        scanf("%d", &choice);

        if(choice == 1){
            long int firstValue;
            long int numberOfElements;
            int choice;
            long int i;
            do{
                output = fopen("output.txt", "w");
                if (output == NULL) {
                    printf("Error opening file!\n");
                    return 1;
                }
                printf("        Enter the number of\n        elements to be sorted: ");
                scanf("%ld", &numberOfElements);

                if(numberOfElements <= 1){
                    printf("        Number of elements should\n        be greater than 1. Try again!\n");
                    continue;
                }else{
                    do{
                        originalArray = malloc(numberOfElements * sizeof(unsigned long int));
                        array = malloc(numberOfElements * sizeof(unsigned long int));
                        
                        if (originalArray == NULL || array == NULL) {
                            printf("        Memory allocation failed!\n");
                            exit(1); // Exit program on failure
                        }

                        printf("\n\n\n                ╔═╗╔═╗╦═╗╔╦╗\n");
                        printf("                ╚═╗║ ║╠╦╝ ║ \n");
                        printf("                ╚═╝╚═╝╩╚═ ╩ \n");
                        printf("                ╔╦╗╔═╗╔╗╔╦ ╦\n");
                        printf("                ║║║║╣ ║║║║ ║\n");
                        printf("                ╩ ╩╚═╝╝╚╝╚═╝\n\n\n");
                        printf("   Select method for generating elements:\n\n");
                        printf("         Random numbers    [ENTER 1] \n");
                        printf("         Increasing order  [ENTER 2]\n");
                        printf("         Back to menu      [ENTER 3]\n\n");
                        printf("     Enter your choice: ");
                        scanf("%d", &choice);
                    
                        switch(choice){
                            case 1:
                                    // fills the array with random values 
                                    srand(time(NULL));
                                    unsigned long int randomNum; 
                                    for(i = 0; i < numberOfElements; i++){
                                        randomNum = rand() % (MAX_RANGE + 1);
                                        originalArray[i] = randomNum;
                                    }
                                    break;
                            case 2:
                                    printf("     Enter a starting value: ");
                                    scanf("%lu", &firstValue);
                                    // fills the array with increasing values from firstValue to numberOfElements - 1
                                    for(i = 0; i < numberOfElements; i++){
                                        originalArray[i] = firstValue + i;
                                    }
                                    break;
                            case 3:
                                    break;
                            default: 
                                    printf("     Your choice should either\n     be 1, 2, or 3. Try again!");
                                    continue;
                        }

                        if(choice == 3){
                            break;
                        }
                        
                        clock_t start, end;
                        double cpu_time_used;
                        long int i;
                        
                        // prints header for running time
                        printf("\n\n        PROGRAM OUTPUT:\n");
                        printf("        NUMBER OF ELEMENTS: %lu\n", numberOfElements);
                        // prints the original array in the output file
                        fprintf(output, "     Original Array: \n ");
                        print(output, originalArray, numberOfElements);
                        fprintf(output, "\n");
                        // Sorts the array
                        
                        // Selection Sort
                        restoreOriginal(array, originalArray, numberOfElements);

                        start = clock();
                        selectionSort(array, numberOfElements);
                        end = clock();
                        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                        
                        // prints the sorted array in the output file
                        fprintf(output, "     [SELECTION SORT] Sorted Array: \n ");
                        print(output, array, numberOfElements);
                        printf("          [SELECTION SORT] RUNNING TIME: %lfs \n", cpu_time_used);
                        fprintf(output, "     RUNNING TIME: %lfs \n", cpu_time_used);
                        fprintf(output, "\n");

                        // Insertion Sort
                        restoreOriginal(array, originalArray, numberOfElements);

                        start = clock();
                        insertionSort(array, numberOfElements);
                        end = clock();
                        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                        
                        // prints the sorted array in the output file
                        fprintf(output, "     [INSERTION SORT] Sorted Array: \n ");
                        print(output, array, numberOfElements);
                        printf("          [INSERTION SORT] RUNNING TIME: %lfs \n", cpu_time_used);
                        fprintf(output, "     RUNNING TIME: %lfs \n", cpu_time_used);
                        fprintf(output, "\n");

                        // Bubble Sort
                        array = malloc(numberOfElements * sizeof(unsigned long int));
                        restoreOriginal(array, originalArray, numberOfElements);

                        start = clock();
                        bubbleSort(array, numberOfElements);
                        end = clock();
                        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                        
                        // prints the sorted array in the output file
                        fprintf(output, "     [BUBBLE SORT] Sorted Array: \n ");
                        print(output, array, numberOfElements);
                        printf("          [BUBBLE SORT]    RUNNING TIME: %lfs \n", cpu_time_used);
                        fprintf(output, "     RUNNING TIME: %lfs \n", cpu_time_used);
                        fprintf(output, "\n");

                        // Merge Sort
                        restoreOriginal(array, originalArray, numberOfElements);

                        start = clock();
                        mergeSort(array, 0, numberOfElements - 1);
                        end = clock();
                        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                        
                        // prints the sorted array in the output file
                        fprintf(output, "     [MERGE SORT] Sorted Array: \n ");
                        print(output, array, numberOfElements);
                        printf("          [MERGE SORT]     RUNNING TIME: %lfs \n", cpu_time_used);
                        fprintf(output, "     RUNNING TIME: %lfs \n", cpu_time_used);
                        fprintf(output, "\n");
 
                        // Quick Sort
                        restoreOriginal(array, originalArray, numberOfElements);

                        start = clock();
                        quickSort(array, 0, numberOfElements - 1);
                        end = clock();
                        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                        
                        // prints the sorted array in the output file
                        fprintf(output, "     [QUICK SORT] Sorted Array: \n ");
                        print(output, array, numberOfElements);
                        printf("          [QUICK SORT]     RUNNING TIME: %lfs \n", cpu_time_used);
                        fprintf(output, "     RUNNING TIME: %lfs \n", cpu_time_used);
                        fprintf(output, "\n");

                        // Heap Sort
                        restoreOriginal(array, originalArray, numberOfElements);

                        start = clock();
                        heapSort(array, numberOfElements);
                        end = clock();
                        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                        
                        // prints the sorted array in the output file
                        fprintf(output, "     [HEAP SORT] Sorted Array: \n ");
                        print(output, array, numberOfElements);
                        printf("          [HEAP SORT]      RUNNING TIME: %lfs \n\n\n", cpu_time_used);
                        fprintf(output, "     RUNNING TIME: %lfs \n", cpu_time_used);
                        fprintf(output, "\n");

                        fclose(output);
                        free(originalArray);
                        free(array);
                        return 0;
                    }while(choice != 3);
                    break;
                }
            }while(numberOfElements > 1);
            
        }else if(choice == 2){
            break;
        }else{
            printf("        Your choice should either\n        be 1 or 2. Try again!\n");
        }
    }while(choice != 2);
    return 0;
}

// Selection Sort
void selectionSort(unsigned long int arr[], unsigned long int numElements){
    long int i;
    long int minPosition;
    for(i = 0 ; i < numElements - 1; i++){
        minPosition = min(arr, i, numElements);
        swap(&arr[i], &arr[minPosition]);
    }
}

// Insertion Sort
void insertionSort(unsigned long int arr[], unsigned long int numElements){
    long int curr;
    long int prev;
    long int j;
    for(j = 1; j < numElements; j++){
        curr = arr[j];
        prev = j - 1;
        while(prev >= 0 && curr < arr[prev]){
            arr[prev+1] = arr[prev];
            prev--;
        }
        arr[prev + 1] = curr;
    }
}

// Bubble Sort
void bubbleSort(unsigned long int arr[], unsigned long int numElements){
    long int i;
    long int j;
    for(i = 0; i < numElements - 1; i++){
        for(j = 0; j < numElements - i - 1; j++){
            if(arr[j] > arr[j + 1]){
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Merge Sort
void mergeSort(unsigned long int arr[], unsigned long int left, unsigned long int right){
    long int mid;
    if(left < right){
        // Calculates mid point
        mid = left + (right - left) / 2;

        // Recursively split and sort
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merges the sorted halves
        merge(arr, left, mid, right);
    }
}

// merge two sorted subarrays into one sorted array
void merge(unsigned long int arr[], unsigned long int left, unsigned long int mid, unsigned long int right){
    long int leftArrLen = mid - left + 1;
    long int rightArrLen = right - mid;
    
    long int *leftArr = (long int *)malloc(leftArrLen * sizeof(long int));
    long int *rightArr = (long int *)malloc(rightArrLen * sizeof(long int));

    for(long int i = 0; i < leftArrLen; i++)
        leftArr[i] = arr[left + i];
    for(long int j = 0; j < rightArrLen; j++)
        rightArr[j] = arr[mid + 1 + j];

    long int i = 0, j = 0, k = left;
    while(i < leftArrLen && j < rightArrLen){
        if (leftArr[i] <= rightArr[j]){
            arr[k] = leftArr[i];
            i++;
        }else{
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while(i < leftArrLen){
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while(j < rightArrLen){
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    free(leftArr);
    free(rightArr);
}
//Quick Sort

//median of three for pivot
void medianOfThree(unsigned long int array[], int leftMostIndex, int rightMostIndex) {
    int mid = (leftMostIndex + rightMostIndex) / 2;
    if (array[leftMostIndex] > array[mid]) swap(&array[leftMostIndex], &array[mid]);
    if (array[mid] > array[rightMostIndex]) swap(&array[mid], &array[rightMostIndex]);
    if (array[leftMostIndex] > array[mid]) swap(&array[leftMostIndex], &array[mid]);
    
    swap(&array[leftMostIndex], &array[mid]);
}

// Partition function
int partition(unsigned long int array[], int leftMostIndex, int rightMostIndex) {
    unsigned long int pivot = array[leftMostIndex]; 
    int left = leftMostIndex + 1;
    int right = rightMostIndex;

    while (left <= right) {
        while (left <= right && array[left] <= pivot) left++; 
        while (left <= right && array[right] > pivot) right--; 
        if (left < right) {
            swap(&array[left], &array[right]);
            left++;
            right--;
        }
    }

    swap(&array[leftMostIndex], &array[right]);  // Place pivot in the correct position
    return right;  // Return the pivot index
}
// QuickSort function 
void quickSort(unsigned long int array[], int leftMostIndex, int rightMostIndex) {
    if (leftMostIndex >= rightMostIndex) return;
    medianOfThree(array, leftMostIndex, rightMostIndex);
    int pivotIndex = partition(array, leftMostIndex, rightMostIndex);
    quickSort(array, leftMostIndex, pivotIndex - 1);
    quickSort(array, pivotIndex + 1, rightMostIndex);
}

// Heap Sort
void heapSort(unsigned long int arr[], unsigned long int numElements){
	convertToMaxHeap(arr, numElements);
    long int i;
	for(i = numElements - 1; i >= 1; i--){
		swap(&arr[0], &arr[i]);
		maxHeapify(arr, 0, i);
	} 
}

// ensures that the heap has a max heap property
void maxHeapify(unsigned long int arr[], unsigned long int i, unsigned long int numElements){
	long int leftNode = 2 * i + 1;
	long int rightNode = 2 * i + 2;
	long int largestNode = i;
	
	if(leftNode < numElements && arr[leftNode] > arr[largestNode])
		largestNode = leftNode;
	if(rightNode < numElements && arr[rightNode] > arr[largestNode])
		largestNode = rightNode;
	if(largestNode != i){
		swap(&arr[i], &arr[largestNode]);
		maxHeapify(arr, largestNode, numElements);
	}
}

// converts an array to max heap
void convertToMaxHeap(unsigned long int arr[], unsigned long int numElements){
    long int i;
	for(i = floor(numElements/2) - 1; i >= 0; i--){
		maxHeapify(arr, i, numElements);
	}
}

// other functions
// finds the smallest value in the array
int min(unsigned long int  arr[], long int k, long int numElements){
    long int min = k;
    long int j;
    for (j = k + 1; j < numElements; j++) {
        if (arr[j] < arr[min]) { 
            min = j; 
        }
    }
    return min;
}

// swaps two values
void swap(unsigned long int *item1, unsigned long int *item2){
    long int temp = *item1;
    *item1 = *item2;
    *item2 = temp;
}

// prints the array in the output file
void print(FILE *output, unsigned long int *array, unsigned long int numElements){
    long int i;
    fprintf(output, "    ");
    for(i = 0; i < numElements; i++){
        if (i % 10 == 9) { 
            fprintf(output, " %lu\n     ", array[i]);
        } else if (i == numElements - 1) { 
            fprintf(output, " %lu", array[i]);
        } else {
            fprintf(output, " %lu,", array[i]);
        }
    }
    fprintf(output, "\n");
}

// restores the array back to the original array
void restoreOriginal(unsigned long int *array, unsigned long int *originalArray, unsigned long int numElements){
    long int i;
    for (i = 0; i < numElements; i++) {
        array[i] = originalArray[i];
    }
}
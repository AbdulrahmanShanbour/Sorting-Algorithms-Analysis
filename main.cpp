#include <iostream> // for console input/output
#include <fstream> // for file input/output
#include <ctime> // for measuring clock (CPU Time)
#include<chrono> // for high-resolution clock. More accurate than <ctime> 
#include <stdexcept> // for the throws & Exceptions 
#include <algorithm> // for (copy function)
using namespace std; 

// Global Variables
const int arrSize = 100000; 
int randomArr[arrSize]; 
int sortedArr[arrSize]; 
int sortedBackwardsArr[arrSize]; 
int tempArr[arrSize]; // for storing the array before sorting so that the original is not modified 
chrono::high_resolution_clock::time_point start; // Global so that (stopTimer) can access it
clock_t cStart, cEnd; // for CPU clock time measurement
double clockTime; 
double chronoTime; 


// --------------------- Prototypes ---------------------
// --------------------- Sorting Algorithms ---------------------
void bubbleSortV1(int arr[], const int size = arrSize); // Classic Version
void bubbleSortV2(int arr[], const int size = arrSize); // Modified Version 
void selectionSortV1(int arr[], const int size = arrSize); // Classic Version
void selectionSortV2(int arr[], const int size = arrSize); // Modified Version
void insertionSortV1(int arr[], const int size = arrSize); // Classic Version
void insertionSortV2(int arr[], const int size = arrSize); // Modified Version
void quickSortV1(int arr[], int low, int high); // Classic Version
void quickSortV2(int arr[], int low, int high); // Modified Version
// --------------------- Other functions ---------------------
void readFiles(int[], int[], int[]); 
int binarySearch(int[], int, int, int); // insertionSortV2 helper function
int partition(int[], int, int); // quickSoertV1 helper function
void testAllAlgorithms(); // For analyzing the performance of all the algorithms in all cases
void specificAlgorithm(); // In case specific algorithm is wanted
void startChronoTimer(); 
double stopChronoTimer(); 


int main(){
    // Read the files first: 
    try {
        readFiles(randomArr, sortedArr, sortedBackwardsArr);
    }
    catch (const ios_base::failure& e) {
        cout << "File error: " << e.what() << endl;
    }
    entryMenu(); 

    return 0; 
}

void readFiles(int randomArr[], int sortedArr[], int sortedBackwardsArr[]) {
    ifstream random("randomList.txt"); 
    ifstream sorted("Sorted.txt"); 
    ifstream sortedBackwards ("SortedBackwards.txt"); 
    if (!random) {
        throw ios_base::failure("Failed to open randomList.txt");
    }

    if (!sorted) {
        throw ios_base::failure("Failed to open Sorted.txt");
    }

    if (!sortedBackwards) {
        throw ios_base::failure("Failed to open SortedBackwards.txt");
    }
    for (int i = 0; i < arrSize; i++)
        random >> randomArr[i];

    for (int i = 0; i < arrSize; i++)
        sorted >> sortedArr[i];

    for (int i = 0; i < arrSize; i++)
        sortedBackwards >> sortedBackwardsArr[i];
    // Files will be closed automatically when the ifstream object goes out of scope.
    cout <<"All the input files are read successfully"<<endl; 
}


void startChronoTimer() {
    start = chrono::high_resolution_clock::now();
}
double stopChronoTimer() {
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration<double>(end - start).count();
}


// --------------------- Implementations for the Sorting Algorithms ---------------------
void bubbleSortV1(int arr[], const int size = arrSize){
    int pass, temp; 
    for ( pass =1; pass < size; pass++ ){
        // moves the largest element to the end of the array in each pass, so we can ignore it in the next pass
        for (int x = 0; x < size - pass; x++){
        //compare adjacent elements
            if ( arr[x]>arr[x+1] ){ // swap elements
                temp = arr[x];
                arr[x] = arr[x+1];
                arr[x+1] = temp;
            }    
        }
    }
} // end bubbleSortV1


void bubbleSortV2(int arr[], const int size = arrSize){
    int temp;
    bool sorted = false; // false when swaps occur
    for (int pass = 1; (pass < size) && !sorted; ++pass){
        sorted = true; // assume sorted
        for (int x = 0; x < size-pass; ++x){ 
            if (arr[x] > arr[x+1]){ // exchange items
            temp = arr[x];
            arr[x] = arr[x+1];
            arr[x+1] = temp;
            sorted = false; // signal exchange
            }
        }
    }
} // end bubbleSortV2


void selectionSortV1(int arr[], const int size = arrSize){
    for (int last = size - 1; last >= 1; --last)
    {   // select largest item in the array
        int largestIndex = 0;
        // largest item is assumed to start at index 0
        for (int p = 1; p <= last; ++p)
        {
            if (arr[p] > arr[largestIndex])
                largestIndex = p;
        } // end for
        // swap largest item Data[largestIndex] with Data[last]
        int temp = arr[largestIndex];
        arr[largestIndex] = arr[last];
        arr[last] = temp;
    } // end for
} // end selectionSortV1


void selectionSortV2(int arr[], const int size = arrSize) {
    // Early termination
    if (size <= 1) return;
    // Checking if already sorted
    bool is_sorted = true;
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            is_sorted = false;
            break;
        }
    }
    if (is_sorted) return;
    
    //Bidirectional sorting
    for (int i = 0; i < size / 2; i++) {
        int min_idx = i;
        int max_idx = i;
        
        //Single pass finds BOTH min and max
        for (int j = i + 1; j < size - i; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
            if (arr[j] > arr[max_idx]) {
                max_idx = j;
            }
        }
        //Conditional swap for minimum
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
        //Conditional swap
        int back_pos = size - 1 - i;
        if (arr[back_pos] != arr[max_idx]) {
            int temp = arr[back_pos];
            arr[back_pos] = arr[max_idx];
            arr[max_idx] = temp;
        }
    }
}  // end selectionSortV2


void insertionSortV1(int arr[], const int size = arrSize){
    int item, pass, insertIndex;
    for (pass = 1; pass < size; pass++)
    {
        item = arr[pass];
        insertIndex = pass;
        while ((insertIndex > 0) && (arr[insertIndex - 1] > item))
        {
            // insert the right item
            arr[insertIndex] = arr[insertIndex - 1];
            insertIndex--;
        }
        arr[insertIndex] = item; // insert item at the right place
    }
} // end insertionSortV1


int binarySearch(int arr[], int item, int low, int high) {
    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == item)
            return mid + 1;

        if (arr[mid] < item)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
} // end binary search 


void insertionSortV2(int arr[], const int size = arrSize) {
    // Step 1: Sentinel optimization
    int minIndex = 0;
    for (int i = 1; i < size; i++)
    {
        if (arr[i] < arr[minIndex])
            minIndex = i;
    }
    // Swap the smallest element with arr[0]
    if (minIndex != 0)
    {
        int temp = arr[0];
        arr[0] = arr[minIndex];
        arr[minIndex] = temp;
    }
    // Binary insertion sort
    for (int pass = 1; pass < size; pass++)
    {
        int item = arr[pass];
        // Binary search in arr[0..pass-1] to find insert position
        int insertIndex = binarySearch(arr, item, 0, pass - 1);
        // Shift elements to make space
        for (int j = pass - 1; j >= insertIndex; j--)
        {
            arr[j + 1] = arr[j];
        }
        // Insert the item
        arr[insertIndex] = item;
    }
}


int partition(int arr[], int first, int last) {
    int pivot, temp;
    int loop, cutPoint, bottom, top;
    pivot = arr[first];
    bottom = first; top = last;
    loop = 1; // always TRUE
    while (loop)
    {
        while (arr[top] > pivot)  // find smaller value than pivot from top
            top--;

        while (arr[bottom] < pivot)  // find larger value than pivot from bottom
            bottom++;

        if (bottom < top)
        {
            // change pivot place
            temp = arr[bottom];
            arr[bottom] = arr[top];
            arr[top] = temp;
        }
        else
        {
            loop = 0;        // loop false
            cutPoint = top;
        }
    } // end while
    return cutPoint;
} // end partition


void quickSortV1(int arr[], int low, int high) {
    int cut;
    if (low < high)
    {
        cut = partition(arr, low, high);
        quickSortV1(arr, low, cut);
        quickSortV1(arr, cut + 1, high);
    }
}


// Enrty Menu
void entryMenu() {
    int entryChoice; 
    cout<<"Would you like to: \n"; 
    cout <<"1. Test the performance of all the algorithms for all the cases at once" <<endl; 
    cout <<"2. Choose a specific algorithm"<<endl; 
    cin >> entryChoice; 
    while (entryChoice != 1 && entryChoice != 2) {
        cerr << "Invalid Choice!! Please try again: ";
        cin >> entryChoice;
    }
    switch (entryChoice) {
        case 1: 
            testAllAlgorithms();
            break;  
        case 2: 
            specificAlgorithm(); 
            break; 
    }
}


void testAllAlgorithms() {
    // --------------------- Bubble Sort ---------------------
    cout << "1. Original Bubble Sort: " << endl; 
    cout << "\tRandom List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(randomArr, randomArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        bubbleSortV1(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart); 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime; 
    } 
    cout << "\tSorted List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedArr, sortedArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        bubbleSortV1(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart); 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime; 
    } 
    cout << "\tSorted Backwards List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedBackwardsArr, sortedBackwardsArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        bubbleSortV1(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart); 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime; 
    } 

}
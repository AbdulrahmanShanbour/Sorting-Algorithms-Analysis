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
int caseChoice; 


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
void entryMenu();
void readFiles(int[], int[], int[]); 
void chooseCase(); 
int binarySearch(int[], int, int, int); // insertionSortV2 helper function
int partition(int[], int, int); // quickSoertV1 helper function
void insertionHelper(int arr[], int low, int high); // quickSortV2 helper function 
int medianOfThree(int arr[], int low, int high); // quickSortV2 helper function
void testAllAlgorithms(); // For analyzing the performance of all the algorithms in all cases
void specificAlgorithm(); // In case specific algorithm is wanted
void startChronoTimer(); // for starting high-resolution clock
double stopChronoTimer(); // for stopping high-resolution clock
// Classic Bubble Sort
void bubbleV1Random(); 
void bubbleV1Sorted(); 
void bubbleV1SortedBackwards(); 
// Improved Bubble Sort
void bubbleV2Random(); 
void bubbleV2Sorted(); 
void bubbleV2SortedBackwards(); 
// Classic Selection Sort
void selectionV1Random(); 
void selectionV1Sorted(); 
void selectionV1SortedBackwards();
// Improved Selection Sort
void selectionV2Random(); 
void selectionV2Sorted(); 
void selectionV2SortedBackwards();
// Classic Insertion Sort
void insertionV1Random(); 
void insertionV1Sorted(); 
void insertionV1SortedBackwards(); 
// Improved Insertion Sort
void insertionV2Random(); 
void insertionV2Sorted(); 
void insertionV2SortedBackwards(); 
// Classic Quick Sort
void quickV1Random(); 
void quickV1Sorted(); 
void quickV1SortedBackwards(); 
// Improved Quick Sort
void quickV2Random(); 
void quickV2Sorted(); 
void quickV2SortedBackwards();


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
void bubbleSortV1(int arr[], const int size){
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


void bubbleSortV2(int arr[], const int size){
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


void selectionSortV1(int arr[], const int size){
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


void selectionSortV2(int arr[], const int size) {
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


void insertionSortV1(int arr[], const int size){
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
        int mid = low + (high - low) / 2;

        if (arr[mid] == item)
            return mid + 1;

        if (arr[mid] < item)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
} // end binary search 


void insertionSortV2(int arr[], const int size) {
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
    int pivot = arr[last];
    int i = first - 1;

    for(int j = first; j < last; j++){
        if(arr[j] < pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[last]);
    return i + 1;
} // end partition


void quickSortV1(int arr[], int low, int high) {
    while(low < high){
        int pi = partition(arr, low, high);

        // Recurse on smaller part first (IMPORTANT)
        if(pi - low < high - pi){
            quickSortV1(arr, low, pi - 1);
            low = pi + 1;
        } else {
            quickSortV1(arr, pi + 1, high);
            high = pi - 1;
        }
    }
}


void insertionHelper(int arr[], int low, int high){
    for(int i = low + 1; i <= high; i++){
        int key = arr[i];
        int j = i - 1;

        while(j >= low && arr[j] > key){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


int medianOfThree(int arr[], int low, int high){
    int mid = low + (high - low) / 2;
    if(arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    if(arr[low] > arr[high]) swap(arr[low], arr[high]);
    if(arr[mid] > arr[high]) swap(arr[mid], arr[high]);
    swap(arr[mid], arr[high]); // use median as pivot
    return high;
}


// Improved Quick Sort (v2) with median-of-three pivot selection and insertion sort for small partitions
void quickSortV2(int arr[], int low, int high){
    while(low < high){

        // Use insertion sort for small subarrays
        if(high - low < 20){
            insertionHelper(arr, low, high);
            return;
        }
        // median-of-three pivot selection
        medianOfThree(arr, low, high);
        long long pivot = arr[high];
        // 3-way partition
        int lt = low, gt = high, i = low;
        while(i <= gt){
            if(arr[i] < pivot){
                swap(arr[i], arr[lt]);
                i++; lt++;
            }
            else if(arr[i] > pivot){
                swap(arr[i], arr[gt]);
                gt--;
            }
            else{
                i++;
            }
        }
        // Tail recursion optimization 
        if(lt - low < high - gt){
            quickSortV2(arr, low, lt - 1);
            low = gt + 1;
        } else {
            quickSortV2(arr, gt + 1, high);
            high = lt - 1;
        }
    }
}


// Enrty Menu
void entryMenu() {
    int entryChoice; 
    while(true) {
        cout<<"Would you like to: \n"; 
        cout <<"1. Test the performance of all the algorithms for all the cases at once" <<endl; 
        cout <<"2. Choose a specific algorithm"<<endl; 
        cout <<"3. Exit Program"<< endl; 
        cin >> entryChoice; 
        while (entryChoice != 1 && entryChoice != 2 && entryChoice != 3) {
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
            default: // Will be 3 anyway
                return; 
        }
    }
}


void testAllAlgorithms() {
    // --------------------- Bubble Sort ---------------------
    cout << "1. Original Bubble Sort: " << endl; 
    bubbleV1Random(); 
    bubbleV1Sorted(); 
    bubbleV1SortedBackwards(); 
    cout << "2. Improved Bubble Sort: " <<endl; 
    bubbleV2Random(); 
    bubbleV2Sorted(); 
    bubbleV2SortedBackwards(); 
    // --------------------- Selection Sort ---------------------
    cout << "3. Original Selection Sort:  " << endl; 
    selectionV1Random(); 
    selectionV1Sorted(); 
    selectionV1SortedBackwards();
    cout << "4. Improved Selection Sort:  " << endl; 
    selectionV2Random(); 
    selectionV2Sorted(); 
    selectionV2SortedBackwards();
    // --------------------- Insertion Sort ---------------------
    cout << "5. Original Insertion Sort:  " << endl; 
    insertionV1Random(); 
    insertionV1Sorted();
    insertionV1SortedBackwards(); 
    cout << "6. Improved Insertion Sort:  " << endl; 
    insertionV2Random(); 
    insertionV2Sorted();
    insertionV2SortedBackwards();
    // --------------------- Quick Sort ---------------------
    cout << "7. Original Quick Sort:  " << endl; 
    quickV1Random(); 
    quickV1Sorted();
    quickV1SortedBackwards();
    cout << "8. Improved Quick Sort:  " << endl; 
    quickV2Random(); 
    quickV2Sorted();
    quickV2SortedBackwards();
}


void chooseCase() {
    cout << "Which case would you like to test? " << endl; 
    cout << "1. Random"<<endl<<"2. Sorted"<<endl<<"3. Sorted Backwards"<<endl;
    cin >> caseChoice; 
    while (caseChoice<1 || caseChoice>3){
        cout << "Invalid Choice!! Try Again"; 
        cin >> caseChoice; 
    }
}


void specificAlgorithm() {
    int algorithmChoice; 
    cout << "Which algorithm would you like to test? "<<endl; 
    cout << "1. Classic Bubble Sort"<<endl; 
    cout << "2. Improved Bubble Sort"<<endl; 
    cout << "3. Classic Selection Sort"<<endl; 
    cout << "4. Improved Selection Sort"<<endl; 
    cout << "5. Classic Insertion Sort"<<endl; 
    cout << "6. Improved Insertion Sort"<<endl; 
    cout << "7. Classic Quick Sort"<<endl; 
    cout << "8. Improved Quick Sort"<<endl; 
    cin>>algorithmChoice; 
    while (algorithmChoice < 1 || algorithmChoice > 8){
        cout << "Invalid choice!! Try Again: "; 
        cin >> algorithmChoice; 
    }
    switch (algorithmChoice) {
        case 1: 
            chooseCase(); 
            switch(caseChoice) {
                case 1: bubbleV1Random(); 
                break;
                case 2: bubbleV1Sorted(); 
                break;
                case 3: bubbleV1SortedBackwards(); 
            }
            break; 
        case 2: 
            chooseCase(); 
            switch(caseChoice) {
                case 1: bubbleV2Random(); 
                break;
                case 2: bubbleV2Sorted(); 
                break;
                case 3: bubbleV2SortedBackwards(); 
            }
            break; 
        case 3: 
            chooseCase(); 
            switch(caseChoice) {
                case 1: selectionV1Random(); 
                break;
                case 2: selectionV1Sorted(); 
                break;
                case 3: selectionV1SortedBackwards(); 
            }
            break; 
        case 4: 
            chooseCase(); 
            switch(caseChoice) {
                case 1: selectionV2Random(); 
                break;
                case 2: selectionV2Sorted(); 
                break;
                case 3: selectionV2SortedBackwards(); 
            }
            break; 
        case 5: 
            chooseCase(); 
            switch(caseChoice) {
                case 1: insertionV1Random(); 
                break;
                case 2: insertionV1Sorted(); 
                break;
                case 3: insertionV1SortedBackwards(); 
            }
            break;
        case 6:
            chooseCase(); 
            switch(caseChoice) {
                case 1: insertionV2Random(); 
                break;
                case 2: insertionV2Sorted(); 
                break;
                case 3: insertionV2SortedBackwards(); 
            }
            break; 
        case 7: 
            chooseCase(); 
            switch(caseChoice) {
                case 1: quickV1Random(); 
                break;
                case 2: quickV1Sorted(); 
                break;
                case 3: quickV1SortedBackwards(); 
            }
            break;
        case 8: 
            chooseCase(); 
            switch(caseChoice) {
                case 1: quickV2Random();
                break; 
                case 2: quickV2Sorted(); 
                break;
                case 3: quickV2SortedBackwards(); 
            }
    }
}


// --------------------- The functions of all the cases for all the algorithms ---------------------
void bubbleV1Random () {
    cout << "\tRandom List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(randomArr, randomArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        bubbleSortV1(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl;
    } 
}
void bubbleV1Sorted() {
    cout << "\tSorted List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedArr, sortedArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        bubbleSortV1(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime<< endl; 
    } 
}
void bubbleV1SortedBackwards() {
    cout << "\tSorted Backwards List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedBackwardsArr, sortedBackwardsArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        bubbleSortV1(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime<< endl; 
    }
}


void bubbleV2Random () {
    cout << "\tRandom List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(randomArr, randomArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        bubbleSortV2(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    } 
}
void bubbleV2Sorted() {
    cout << "\tSorted List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedArr, sortedArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        bubbleSortV2(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    } 
}
void bubbleV2SortedBackwards() {
    cout << "\tSorted Backwards List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedBackwardsArr, sortedBackwardsArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        bubbleSortV2(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    }
}


void selectionV1Random(){
    cout << "\tRandom List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(randomArr, randomArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        selectionSortV1(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    } 
}
void selectionV1Sorted(){
    cout << "\tSorted List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedArr, sortedArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        selectionSortV1(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    } 
}
void selectionV1SortedBackwards(){
    cout << "\tSorted Backwards List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedBackwardsArr, sortedBackwardsArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        selectionSortV1(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    }
}


void selectionV2Random(){
    cout << "\tRandom List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(randomArr, randomArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        selectionSortV2(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    } 
}
void selectionV2Sorted(){
    cout << "\tSorted List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedArr, sortedArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        selectionSortV2(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    }
}
void selectionV2SortedBackwards(){
    cout << "\tSorted Backwards List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedBackwardsArr, sortedBackwardsArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        selectionSortV2(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    }
}


void insertionV1Random(){
    cout << "\tRandom List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(randomArr, randomArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        insertionSortV1(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    }
}
void insertionV1Sorted(){
    cout << "\tSorted List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedArr, sortedArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        insertionSortV1(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    }
} 
void insertionV1SortedBackwards(){
    cout << "\tSorted Backwards List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedBackwardsArr, sortedBackwardsArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        insertionSortV1(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    }
}


void insertionV2Random(){
    cout << "\tRandom List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(randomArr, randomArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        insertionSortV2(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    }
}
void insertionV2Sorted(){
    cout << "\tSorted List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedArr, sortedArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        insertionSortV2(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    }
} 
void insertionV2SortedBackwards(){
    cout << "\tSorted Backwards List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedBackwardsArr, sortedBackwardsArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        insertionSortV2(tempArr); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    }
}


void quickV1Random(){
    cout << "\tRandom List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(randomArr, randomArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        quickSortV1(tempArr, 0, arrSize - 1); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    }
}
void quickV1Sorted(){
    cout << "\tSorted List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedArr, sortedArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        quickSortV1(tempArr, 0, arrSize - 1); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    }
}
void quickV1SortedBackwards(){
    cout << "\tSorted Backwards List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedBackwardsArr, sortedBackwardsArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        quickSortV1(tempArr, 0, arrSize - 1); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    }
}


void quickV2Random(){
    cout << "\tRandom List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(randomArr, randomArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        quickSortV2(tempArr, 0, arrSize - 1); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    }
}
void quickV2Sorted(){
    cout << "\tSorted List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedArr, sortedArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        quickSortV2(tempArr, 0, arrSize - 1); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    }
}
void quickV2SortedBackwards(){
    cout << "\tSorted Backwards List: " << endl;
    for (int i = 1; i<4; i++) {
        cout << "\t\tTrial "<< i <<": "<<endl; 
        copy(sortedBackwardsArr, sortedBackwardsArr + arrSize, tempArr);
        cStart = clock();
        startChronoTimer(); 
        quickSortV2(tempArr, 0, arrSize - 1); 
        cEnd = clock();
        chronoTime = stopChronoTimer(); 
        clockTime = double(cEnd - cStart) / CLOCKS_PER_SEC; 
        cout<<"\t\tClock Time: " << clockTime << endl; 
        cout <<"\t\tChrono Time: " << chronoTime << endl; 
    }
}
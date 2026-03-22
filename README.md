# Sorting Algorithm Performance Analysis

A comprehensive C++ program for analyzing and comparing the performance of various sorting algorithms under different data conditions.

## Overview

This project implements multiple sorting algorithms and measures their performance characteristics across three distinct test cases:
- **Random data**: Unsorted, randomly shuffled values
- **Sorted data**: Already sorted in ascending order
- **Reverse sorted data**: Sorted in descending order

This comprehensive testing framework allows students and developers to understand how different algorithms perform under various real-world scenarios.

## Features

- **8 Sorting Algorithm Implementations**
  - Bubble Sort (Classic & Optimized versions)
  - Selection Sort (Classic & Optimized versions)
  - Insertion Sort (Classic & Optimized versions)
  - Quick Sort (Classic & Optimized pivot selection & Hybrid insertion approach)

- **Performance Metrics**
  - High-resolution timing using C++11 `<chrono>` library
  - CPU clock time measurement using `<ctime>`
  - Detailed performance analysis across all test cases

- **Three Data Scenarios**
  - 100,000 random integers
  - 100,000 pre-sorted integers
  - 100,000 reverse-sorted integers

- **User-Friendly Interface**
  - Interactive menu system for selecting algorithms and test cases
  - Color-coded console output (ANSI color support) for easy visualization
  - Option to test all algorithms or specific implementations

## Project Structure

```
├── main.cpp                 # Main program with implementations and UI
├── randomList.txt           # Input: 100,000 random integers
├── Sorted.txt              # Input: 100,000 sorted integers (ascending)
├── SortedBackwards.txt      # Input: 100,000 reverse-sorted integers
└── README.md               # Project documentation
```

## Compilation & Execution

### Requirements
- C++11 or later
- Compatible C++ compiler (g++, clang, MSVC, etc.)

### Compile

```bash
g++ -o SortAnalyzer main.cpp -std=c++11
```

### Run

```bash
./SortAnalyzer
```

**Note for Windows users:**
```cmd
g++ -o SortAnalyzer.exe main.cpp -std=c++11
SortAnalyzer.exe
```

## Usage

1. Launch the program
2. Select from the interactive menu:
   - View performance of all algorithms (all test cases)
   - Test a specific algorithm with detailed metrics
3. The program will output timing results and algorithm performance data

## Algorithm Details

### Classic Versions (V1)
- **Bubble Sort V1**: Traditional nested-loop implementation with O(n²) complexity
- **Selection Sort V1**: Standard selection approach with O(n²) complexity
- **Insertion Sort V1**: Basic insertion approach with O(n²) average complexity
- **Quick Sort V1**: Standard Lomuto partition with O(n log n) average complexity

### Optimized Versions (V2)
- **Bubble Sort V2**: Early termination when array becomes sorted
- **Selection Sort V2**: Reduced operations and enhanced performance
- **Insertion Sort V2**: Binary search for insertion position + Quick Sort hybrid for subarrays
- **Quick Sort V2**: Median-of-three pivot selection + Insertion sort for small subarrays

## Time Complexity

| Algorithm | Best Case | Average Case | Worst Case | Space |
|-----------|-----------|--------------|-----------|-------|
| Bubble Sort V1 | O(n²) | O(n²) | O(n²) | O(1) |
| Bubble Sort V2 | O(n) | O(n²) | O(n²) | O(1) |
| Selection Sort V1 | O(n²) | O(n²) | O(n²) | O(1) |
| Selection Sort V2 | O(n²) | O(n²) | O(n²) | O(1) |
| Insertion Sort V1 | O(n) | O(n²) | O(n²) | O(1) |
| Insertion Sort V2 | O(n log n) | O(n log n) | O(n²) | O(1) |
| Quick Sort V1 | O(n log n) | O(n log n) | O(n²) | O(log n) |
| Quick Sort V2 | O(n log n) | O(n log n) | O(n log n) | O(log n) |

## Learning Outcomes

This project demonstrates:
- Implementation of fundamental sorting algorithms
- Performance analysis and benchmarking techniques
- Impact of algorithmic optimizations on real-world performance
- How data characteristics (random, sorted, reverse-sorted) affect algorithm efficiency
- Hybrid sorting approaches combining multiple algorithms

## Academic Context

Course: CSCI 215  
Topic: Algorithm Analysis and Design

## Contributing

Suggestions for improvements:
- Additional sorting algorithms (Merge Sort, Heap Sort, etc.)
- Visualization of sorting process
- Statistical analysis of results
- Export performance data to CSV/JSON

## License

This project is for educational purposes.

---

**Author**: Created for CSCI 215 Project  
**Last Updated**: March 2026

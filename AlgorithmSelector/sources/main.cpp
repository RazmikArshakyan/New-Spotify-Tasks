#include <iostream>

#include "..\\headers\sorting.hpp"
#include "..\\headers\fileIO.hpp"

int main() {
    std::string fileName = "NumsFile.txt";
    SortingStrategy strategy;

    std::cout << "Enter wanted size: ";
    int size;
    std::cin >> size;

    if (size < 50) 
        strategy = SortingStrategy::InsertionSort;
    else if (size <= 10000)
        strategy = SortingStrategy::QuickSort;
    else
        strategy = SortingStrategy::HeapSort;
    
    std::vector<int> arr = generateRandomArray(size);
    SortingOption sortingOption(strategy);
    sortingOption.sort(arr);

    writeArrayToFile(fileName, arr);
    std::cout << "Sorted array saved to file: " << fileName << std::endl;

    std::cout << "Reading array from the file after sorting" << std::endl;
    std::vector<int> sortedArr = readArrayFromFile(fileName);
    for (auto num : sortedArr)
        std::cout << num << " ";
    
    return 0;
}

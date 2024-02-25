#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <memory>

enum class SortingStrategy {
    InsertionSort,
    QuickSort,
    HeapSort
};

class SortingOption {
public:
    SortingOption(SortingStrategy strategy);
    void sort(std::vector<int>& arr);
private:
    class SortingOptionImpl;
    std::shared_ptr<SortingOptionImpl> pImpl;
};

#endif
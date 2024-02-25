#include "..\\headers\sorting.hpp"

#include <algorithm>
#include <random>
#include <ctime>

class SortingOption::SortingOptionImpl {
public:
    SortingOptionImpl(SortingStrategy strategy) : strategy(strategy) {}

    void sort(std::vector<int>& arr) {
        switch (strategy) {
            case SortingStrategy::InsertionSort:
                insertionSort(arr);
                break;
            case SortingStrategy::QuickSort:
                quickSort(arr);
                break;
            case SortingStrategy::HeapSort:
                heapSort(arr);
                break;
        }
    }

private:
    SortingStrategy strategy;
    void insertionSort(std::vector<int>& arr) {
        int n = arr.size();
        for (int i = 1; i < n; ++i) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }

    int partition(std::vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; ++j)
            if (arr[j] <= pivot) 
                std::swap(arr[++i], arr[j]);

        std::swap(arr[++i], arr[high]);
        return i;
    }

    int randomizedPartition(std::vector<int>& arr, int low, int high) {
        std::srand(std::time(0));
        int randomIndex = low + rand() % (high - low + 1);
        std::swap(arr[randomIndex], arr[high]);

        return partition(arr, low, high);
    }

    void quickSort(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int pivot = randomizedPartition(arr, low, high);
            quickSort(arr, low, pivot - 1);
            quickSort(arr, pivot + 1, high);
        }
    }

    void quickSort(std::vector<int>& arr) {
        quickSort(arr, 0, arr.size() - 1);
    }

    void heapify(std::vector<int>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    void buildMaxHeap(std::vector<int>& arr) {
        int n = arr.size();
        for (int i = n / 2 - 1; i >= 0; --i)
            heapify(arr, n, i);
    }

    void heapSort(std::vector<int>& arr) {
        int n = arr.size();
        buildMaxHeap(arr);

        for (int i = n - 1; i > 0; --i) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
};

SortingOption::SortingOption(SortingStrategy strategy) : pImpl(std::make_shared<SortingOptionImpl>(strategy)) {}

void SortingOption::sort(std::vector<int>& arr) {
    pImpl->sort(arr);
}

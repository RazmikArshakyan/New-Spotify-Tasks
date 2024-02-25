#include "..\\headers\fileIO.hpp"

#include <fstream>
#include <iostream>
#include <random>
#include <ctime>

std::vector<int> readArrayFromFile(const std::string& fileName) {
    std::vector<int> arr;
    std::ifstream file(fileName);

    if (file.is_open()) {
        int num;
        while (file >> num) {
            arr.push_back(num);
        }
        file.close();
    }
    return arr;
}

void writeArrayToFile(const std::string& fileName, const std::vector<int>& arr) {
    std::ofstream file(fileName);
    if (file.is_open()) {
        for (int num : arr) {
            file << num << " ";
        }
        file.close();
    }
}

std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100000);

    for (int i = 0; i < size; ++i)
        arr[i] = dist(gen);
    
    return arr;
}

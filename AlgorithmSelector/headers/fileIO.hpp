#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <vector>

std::vector<int> readArrayFromFile(const std::string& fileName);
void writeArrayToFile(const std::string& fileName, const std::vector<int>& arr);
std::vector<int> generateRandomArray(int size);

#endif

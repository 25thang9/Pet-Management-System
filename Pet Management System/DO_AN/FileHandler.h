// FileHandler.h - Đọc/ghi file (Abstraction)
#pragma once
#include <vector>
#include "Pet.h"
using std::vector;
class FileHandler {
public:
    static void loadFromFile(vector<Pet*>& list);
    static void saveToFile(const vector<Pet*>& list);
};
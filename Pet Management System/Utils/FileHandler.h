#pragma once
#include <vector>
#include "Core/Pet.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class FileHandler {
public:
    static void loadFromFile(std::vector<Pet*>& list);
    static void saveToFile(const std::vector<Pet*>& list);
};
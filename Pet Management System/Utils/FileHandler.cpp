#include "Utils/FileHandler.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void FileHandler::saveToFile(const vector<Pet*>& list)
{
    ofstream file("Data/pets.txt");
    if (!file.is_open()) {
        cout << "Cannot open pets.txt for saving!\n";
        return;
    }

    for (const auto& p : list) {
        file << p->getSpecies() << "|"
             << p->getName()    << "|"
             << p->getAge()     << "|"
             << p->getColor()   << "|"
             << p->getBreed()   << "|"
             << p->getOwner()   << "\n";
    }

    file.close();
}

void FileHandler::loadFromFile(vector<Pet*>& list)
{
    // Xóa dữ liệu cũ trước khi load
    for (auto p : list) delete p;
    list.clear();

    ifstream file("Data/pets.txt");
    if (!file.is_open()) {
        cout << "pets.txt not found -> starting with empty list\n\n";
        return;
    }

    string line;
    int count = 0;

    while (getline(file, line)) {
        // Xóa \r nếu có (Windows line ending)
        if (!line.empty() && line.back() == '\r') line.pop_back();

        if (line.empty()) continue;

        stringstream ss(line);

        string species, name, color, breed, owner;
        string ageStr;
        int age;

        // Dùng getline với delimiter '|' → an toàn tuyệt đối với khoảng trắng
        if (!getline(ss, species, '|')) continue;
        if (!getline(ss, name,    '|')) continue;
        if (!getline(ss, ageStr,  '|')) continue;
        if (!getline(ss, color,   '|')) continue;
        if (!getline(ss, breed,   '|')) continue;
        if (!getline(ss, owner,   '|')) owner = ""; // owner có thể rỗng

        // Chuyển age sang int, kiểm tra lỗi
        try {
            age = stoi(ageStr);
            if (age < 0) continue; // tuổi âm thì bỏ qua dòng
        }
        catch (...) {
            continue; // không phải số → bỏ qua dòng
        }

        list.push_back(new Pet(species, name, age, color, breed, owner));
        count++;
    }

    file.close();
    cout << "Loaded " << count << " pets successfully!\n\n";
}
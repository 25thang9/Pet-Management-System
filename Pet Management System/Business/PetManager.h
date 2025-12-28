#pragma once
#include "Core/Pet.h"
#include "Utils/FileHandler.h"
#include "Menu/SubMenu.h"
#include <vector>
#include <algorithm>
#include <map>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <cctype>
using namespace std;
class PetManager {
    vector<Pet*> pets;
public:
    ~PetManager();                          // Tự động dọn dẹp
    void loadData();
    void saveData() const;
    void addPet();
    void displayAll() const;
    void displayAndSearchMenu();            // Mục 2 – có menu con
    void editPet();
    void deletePet();
    void sortMenu();                        
    void statisticsMenu() const;            
    void fileManagementMenu();                
private:
    void searchByName() const;
    void filterBySpecies() const;
    void filterByColor() const;
    void filterByOwner() const;
};
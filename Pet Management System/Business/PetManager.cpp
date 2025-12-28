#include "Business/PetManager.h"
using namespace std;
static string toLowerASCII(string s) {
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c){ return tolower(c); });
    return s;
}
PetManager::~PetManager() {
    for (auto p : pets) delete p;
    pets.clear();
}

void PetManager::loadData() {
    for (auto p : pets) delete p;
    pets.clear();

    FileHandler::loadFromFile(pets);
}

void PetManager::saveData() const { FileHandler::saveToFile(pets); }
// ============================= THÊM THÚ CƯNG MỚI =============================
void PetManager::addPet() {
    system("cls");
    cout << "╔══════════════════════════════════╗\n";
    cout << "║          ADD NEW PET             ║\n";
    cout << "╚══════════════════════════════════╝\n\n";
    cout << "Leave any field blank (just press Enter) to cancel adding.\n\n";

    string species, name, color, breed, owner;
    int age;

    cout << "Species           : ";
    if (!getline(cin, species) || species.empty()) {
        cout << "\nAdding cancelled.\n\n";
        system("pause");
        return;
    }

    cout << "Name              : ";
    if (!getline(cin, name) || name.empty()) {
        cout << "\nAdding cancelled.\n\n";
        system("pause");
        return;
    }

    cout << "Age               : ";
    string ageInput;
    if (!getline(cin, ageInput) || ageInput.empty()) {
        cout << "\nAdding cancelled.\n\n";
        system("pause");
        return;
    }
    try {
        age = stoi(ageInput);
        if (age < 0) throw 1;
    }
    catch (...) {
        cout << "\nInvalid age! Adding cancelled.\n\n";
        system("pause");
        return;
    }

    cout << "Color             : ";
    if (!getline(cin, color) || color.empty()) {
        cout << "\nAdding cancelled.\n\n";
        system("pause");
        return;
    }

    cout << "Breed             : ";
    if (!getline(cin, breed) || breed.empty()) {
        cout << "\nAdding cancelled.\n\n";
        system("pause");
        return;
    }

    cout << "Owner (optional)  : ";
    getline(cin, owner);

    pets.push_back(new Pet(species, name, age, color, breed, owner));
    cout << "\nPet added successfully!\n\n";
    saveData();
    cout << "Data has been saved to pets.txt!\n\n";
    system("pause");
}

// ============================= HIỂN THỊ TẤT CẢ =============================
void PetManager::displayAll() const {
    system("cls");
    if (pets.empty()) {
        cout << "Empty list!\n\n";
        cout << "Press any key to continue...";
        _getch();
        system("cls");
        return;
    }

    // In bảng như bình thường
    cout << left
         << setw(5)  << "STT"     << " | "
         << setw(15) << "SPECIES" << " | "
         << setw(25) << "NAME"    << " | "
         << setw(5)  << "AGE"     << " | "
         << setw(20) << "COLOR"   << " | "
         << setw(40) << "BREED"   << " | "
         << setw(30)  << "OWNER"   << endl;

    cout << string(145, '-') << endl;

    for (size_t i = 0; i < pets.size(); ++i) {
        cout << left << setw(5) << (i + 1) << " | ";
        pets[i]->display();
    }

    cout << string(145, '-') << endl;
    cout << "Total: " << pets.size() << " pets\n\n";

    // In thông báo chờ phím
    cout << "Press any key to continue...";
    _getch();           // Chờ phím, không in newline

    // Buộc xuống 1 dòng mới để con trỏ không dính vào dòng cũ
    cout << '\n';

    system("cls");      // Xóa sạch màn hình → con trỏ về đầu trang
}
// ============================= TÌM KIẾM & LỌC  =============================
void PetManager::searchByName() const {
    system("cls");
    cout << "\n\n";

    string n;
    cout << "Enter name: ";
    getline(cin, n);

    if (n.empty()) {
        cout << "No name entered.\n\n";
        system("pause");
        return;
    }

    // Chuyển tên nhập về chữ thường không dấu để so sánh
    string lowerInput = toLowerASCII(n);

    bool found = false;
    for (const auto& p : pets) {
        string petName = toLowerASCII(p->getName());

        if (petName == lowerInput) {
            if (!found) {
                cout << "\n======== RESULTS ========\n";
                cout << left << setw(12) << "SPECIES" << setw(20) << "NAME"
                     << setw(6) << "AGE" << setw(15) << "COLOR"
                     << setw(20) << "BREED" << "OWNER" << endl;
                cout << string(90, '-') << endl;
                found = true;
            }
            cout << left
                 << setw(12) << p->getSpecies()
                 << setw(20) << p->getName()
                 << setw(6)  << p->getAge()
                 << setw(15) << p->getColor()
                 << setw(20) << p->getBreed()
                 << p->getOwner() << endl;
        }
    }
    if (!found) cout << "Not found!\n";
    cout << "\n";
    system("pause");
}

void PetManager::filterBySpecies() const {
    system("cls");
    cout << "\n\n";
    string s;
    cout << "Enter species: ";
    getline(cin, s);

    bool found = false;
    for (const auto& p : pets) {
        if (p->getSpecies() == s) {
            if (!found) {
                cout << "\n======== RESULTS ========\n";
                cout << left << setw(12) << "SPECIES" << setw(20) << "NAME"
                     << setw(6) << "AGE" << setw(15) << "COLOR"
                     << setw(20) << "BREED" << "OWNER" << endl;
                cout << string(90, '-') << endl;
                found = true;
            }
            cout << left
                 << setw(12) << p->getSpecies()
                 << setw(20) << p->getName()
                 << setw(6)  << p->getAge()
                 << setw(15) << p->getColor()
                 << setw(20) << p->getBreed()
                 << p->getOwner() << endl;
        }
    }
    if (!found) cout << "No pets found!\n";
    cout << "\n";
    system("pause");
}

void PetManager::filterByColor() const {
    system("cls");
    cout << "\n\n";
    string c;
    cout << "Enter color: ";
    getline(cin, c);

    bool found = false;
    for (const auto& p : pets) {
        if (p->getColor() == c) {
            if (!found) {
                cout << "\n======== RESULTS ========\n";
                cout << left << setw(12) << "SPECIES" << setw(20) << "NAME"
                     << setw(6) << "AGE" << setw(15) << "COLOR"
                     << setw(20) << "BREED" << "OWNER" << endl;
                cout << string(90, '-') << endl;
                found = true;
            }
            cout << left
                 << setw(12) << p->getSpecies()
                 << setw(20) << p->getName()
                 << setw(6)  << p->getAge()
                 << setw(15) << p->getColor()
                 << setw(20) << p->getBreed()
                 << p->getOwner() << endl;
        }
    }
    if (!found) cout << "No pets found!\n";
    cout << "\n";
    system("pause");
}

void PetManager::filterByOwner() const {
    system("cls");
    cout << "\n\n";
    string o;
    cout << "Enter owner: ";
    getline(cin, o);

    bool found = false;
    for (const auto& p : pets) {
        if (p->getOwner() == o) {
            if (!found) {
                cout << "\n======== RESULTS ========\n";
                cout << left << setw(12) << "SPECIES" << setw(20) << "NAME"
                     << setw(6) << "AGE" << setw(15) << "COLOR"
                     << setw(20) << "BREED" << "OWNER" << endl;
                cout << string(90, '-') << endl;
                found = true;
            }
            cout << left
                 << setw(12) << p->getSpecies()
                 << setw(20) << p->getName()
                 << setw(6)  << p->getAge()
                 << setw(15) << p->getColor()
                 << setw(20) << p->getBreed()
                 << p->getOwner() << endl;
        }
    }
    if (!found) cout << "No pets found!\n";
    cout << "\n";
    system("pause");
}

// ============================= MENU CON MỤC 2  =============================
void PetManager::displayAndSearchMenu() {
    vector<string> items = {
        "1. Display all pets",
        "2. Search by name",
        "3. Filter by species",
        "4. Filter by color",
        "5. Filter by owner",
        "0. Back to main menu"
    };

    while (true) {
        system("cls");  // Xóa màn hình trước khi hiện menu mới → fix chồng lấn

        SubMenu menu("DISPLAY / SEARCH / FILTER", items);
        int choice = menu.show();

        if (choice == -1 || choice == 5) return;  // ESC hoặc chọn 0

        switch (choice) {
            case 0: displayAll();       break;
            case 1: searchByName();     break;
            case 2: filterBySpecies();  break;
            case 3: filterByColor();    break;
            case 4: filterByOwner();    break;
        }
    }
}

// ============================= SẮP XẾP =============================
void PetManager::sortMenu() {
    system("cls");
    cout << "\n\n";
    vector<string> items = {
        "1. Name A-Z",
        "2. Name Z-A",
        "3. Age ascending",
        "4. Age descending",
        "5. Breed A-Z",
        "6. Color A-Z",
        "0. Back"
    };
    SubMenu menu("SORT MENU", items);

    while (true) {
        system("cls");  // Thêm để menu sạch
        int c = menu.show();
        if (c == -1 || c == 6) return;

        vector<Pet*> tmp = pets;
        switch (c) {
            case 0: sort(tmp.begin(), tmp.end(), [](Pet* a, Pet* b){ return a->getName() < b->getName(); }); break;
            case 1: sort(tmp.begin(), tmp.end(), [](Pet* a, Pet* b){ return a->getName() > b->getName(); }); break;
            case 2: sort(tmp.begin(), tmp.end(), [](Pet* a, Pet* b){ return a->getAge()  < b->getAge(); }); break;
            case 3: sort(tmp.begin(), tmp.end(), [](Pet* a, Pet* b){ return a->getAge()  > b->getAge(); }); break;
            case 4: 
    sort(tmp.begin(), tmp.end(), [](Pet* a, Pet* b) {
        return toLowerASCII(a->getBreed()) < toLowerASCII(b->getBreed());
    });
    break;

case 5:
    sort(tmp.begin(), tmp.end(), [](Pet* a, Pet* b) {
        return toLowerASCII(a->getColor()) < toLowerASCII(b->getColor());
    });
    break;
        }
        system("cls");
        cout << "=== SORTED LIST ===\n";
        for (size_t i = 0; i < tmp.size(); ++i) {
            cout << left << setw(5) << (i+1) << " | ";
            tmp[i]->display();
        }
        cout << string(100, '-') << endl;
        system("pause");
    }
}

// ============================= THỐNG KÊ =============================
void PetManager::statisticsMenu() const {
    system("cls");
    cout << "\n\n";
    map<string,int> sp, cl, br;
    for (const auto& p : pets) {
        sp[p->getSpecies()]++;
        cl[p->getColor()]++;
        br[p->getBreed()]++;
    }

    vector<string> items = {
        "1. Total pets",
        "2. By species",
        "3. By breed",
        "4. By color",
        "0. Back"
    };
    SubMenu menu("STATISTICS", items);

    while (true) {
        system("cls");
        int c = menu.show();
        if (c == -1 || c == 4) return;

        system("cls");
        switch(c) {
            case 0: cout << "Total: " << pets.size() << " pets\n\n"; break;
            case 1: cout << "BY SPECIES:\n"; for(auto& x:sp) cout << "  " << x.first << ": " << x.second << "\n"; cout << endl; break;
            case 2: cout << "BY BREED:\n";   for(auto& x:br) cout << "  " << x.first << ": " << x.second << "\n"; cout << endl; break;
            case 3: cout << "BY COLOR:\n";   for(auto& x:cl) cout << "  " << x.first << ": " << x.second << "\n"; cout << endl; break;
        }
        system("pause");
    }
}

// ============================= SỬA THÔNG TIN =============================
void PetManager::editPet() {
    system("cls");
    if (pets.empty()) {
        cout << "Empty list!\n\n";
        system("pause");
        return;
    }

    displayAll();   

    string name;
    cout << "\nEnter name to edit: ";
    getline(cin, name);   // 

    Pet* pet = nullptr;
    for (auto p : pets) {
        if (p->getName() == name) {
            pet = p;
            break;
        }
    }

    if (!pet) {
        cout << "\nNot found!\n\n";
        system("pause");
        return;
    }

    cout << "\nCurrent info:\n";
    pet->display();
    cout << "\nEnter new info (press Enter to keep old):\n";

    string input;

    cout << "Species [" << pet->getSpecies() << "]: ";
    getline(cin, input);
    if (!input.empty()) pet->setSpecies(input);

    cout << "Name [" << pet->getName() << "]: ";
    getline(cin, input);
    if (!input.empty()) pet->setName(input);

    cout << "Age [" << pet->getAge() << "]: ";
    getline(cin, input);
    if (!input.empty() && all_of(input.begin(), input.end(), ::isdigit))
        pet->setAge(stoi(input));

    cout << "Color [" << pet->getColor() << "]: ";
    getline(cin, input);
    if (!input.empty()) pet->setColor(input);

    cout << "Breed [" << pet->getBreed() << "]: ";
    getline(cin, input);
    if (!input.empty()) pet->setBreed(input);

    cout << "Owner [" << pet->getOwner() << "]: ";
    getline(cin, input);
    if (!input.empty()) pet->setOwner(input);

    cout << "\nUpdated successfully!\n\n";
    saveData();
    cout << "Data has been saved to pets.txt!\n\n";
    system("pause");
}

// ============================= XÓA =============================
void PetManager::deletePet() {
    system("cls");

    if (pets.empty()) {
        cout << "Empty list!\n\n";
        system("pause");
        return;
    }

    // HIỂN THỊ BẢNG NGAY TRÊN TRANG DELETE
    cout << left
         << setw(5)  << "STT"     << " | "
         << setw(15) << "SPECIES" << " | "
         << setw(25) << "NAME"    << " | "
         << setw(5)  << "AGE"     << " | "
         << setw(20) << "COLOR"   << " | "
         << setw(40) << "BREED"   << " | "
         << setw(30)  << "OWNER"   << endl;

    cout << string(145, '-') << endl;

    for (size_t i = 0; i < pets.size(); ++i) {
        cout << left << setw(5) << (i + 1) << " | ";
        pets[i]->display();
    }

    cout << string(145, '-') << endl;
    cout << "Total: " << pets.size() << " pets\n\n";

    string name;
    cout << "Enter name to delete: ";
    getline(cin, name);

    if (name.empty()) {
        cout << "\nNo name entered. Delete cancelled.\n\n";
        system("pause");
        return;
    }

    // Tìm pet (không phân biệt hoa/thường)
    auto it = find_if(pets.begin(), pets.end(), [&](Pet* p) {
        string petName = p->getName();
        string lowerPet = petName;
        string lowerInput = name;
        transform(lowerPet.begin(), lowerPet.end(), lowerPet.begin(), ::tolower);
        transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);
        return lowerPet == lowerInput;
    });

    if (it == pets.end()) {
        cout << "\nNot found!\n\n";
        system("pause");
        return;
    }

    cout << "\nPet to delete:\n";
    (*it)->display();

    cout << "\nType YES to confirm delete: ";
    string confirm;
    getline(cin, confirm);

    if (confirm == "YES" || confirm == "yes" || confirm == "Y" || confirm == "y") {
        delete *it;
        pets.erase(it);
        cout << "\nDeleted successfully!\n";
        saveData();
        cout << "Data has been saved to pets.txt!\n\n";
    } else {
        cout << "\nDelete cancelled.\n\n";
    }
    system("pause");
}
// ============================= MỤC 7 =============================
void PetManager::fileManagementMenu() {
    vector<string> items = {
        "1. Save data to file",
        "2. Load data from file",
        "0. Back to main menu"
    };
    SubMenu menu("FILE MANAGEMENT", items);

    while (true) {
        system("cls");
        int choice = menu.show();

        if (choice == -1 || choice == 2) return;

        switch (choice) {
            case 0:
                saveData();
                cout << "\nData saved successfully to pets.txt!\n\n";
                system("pause");
                break;

            case 1:
                for (auto p : pets) delete p;
                pets.clear();
                loadData();
                cout << "\nData loaded successfully from pets.txt!\n\n";
                system("pause");
                break;

            default:
                cout << "\nInvalid option!\n\n";
                system("pause");
                break;
        }
    }
}
#include "Core/Pet.h"
#include "Utils/Utf8Console.h"
#include <iomanip>
using namespace std;

// Constructor
Pet::Pet(string s, string n, int a, string c, string b, string o)
    : species(s), name(n), age(a), color(c), breed(b), owner(o) {}

// Hiển thị 1 dòng bảng – CHUẨN UTF-8
void Pet::display() const {
    printCol(species, 15); cout << " | ";
    printCol(name,    25); cout << " | ";
    cout << setw(5) << age << " | ";
    printCol(color,   20); cout << " | ";
    printCol(breed,   40); cout << " | ";
    cout << owner << endl;
}

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
#include "Utils/Utf8Console.h"
using namespace std;

class BeautifulMenu {
private:
    vector<string> items;
    string title;
    int selected = 0;

    void gotoxy(short x, short y) {
        COORD pos = {x, y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }

    void setColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

public:
    BeautifulMenu(const string& t, const vector<string>& menuItems)
        : title(t), items(menuItems) {}

    int show() {
        system("cls");
        const int startX = 25;
        const int startY = 6;
        const int boxWidth = 50;

        while (true) {
            gotoxy(startX + (boxWidth - utf8Length(title)) / 2, startY - 2);
            setColor(14);
            cout << title;
            setColor(7);

            gotoxy(startX - 3, startY - 1);
            cout << string(boxWidth + 6, '=');

            gotoxy(startX - 3, startY + items.size());
            cout << string(boxWidth + 6, '=');

            for (int i = 0; i < items.size(); ++i) {
                gotoxy(startX, startY + i);
                if (i == selected) {
                    setColor(240);
                    cout << " > " << items[i];
                    cout << string(boxWidth - utf8Length(items[i]) - 3, ' ');
                } else {
                    setColor(15);
                    cout << "   " << items[i];
                    cout << string(boxWidth - utf8Length(items[i]) - 3, ' ');
                }
                setColor(7);
            }

            gotoxy(startX - 3, startY + items.size() + 2);
            setColor(14);
            cout << "↑↓ di chuyen • Enter chon • ESC thoat";

            int key = _getch();
            if (key == 0 || key == 224) key = _getch();

            switch (key) {
                case 72: selected = (selected - 1 + items.size()) % items.size(); break;
                case 80: selected = (selected + 1) % items.size(); break;
                case 13: return selected;
                case 27: return -1;
            }
        }
    }
};

#pragma once
#include <string>
#include <iostream>
using namespace std;

// Đếm số ký tự HIỂN THỊ (không phải byte)
inline int utf8Length(const string& s) {
    int len = 0;
    for (size_t i = 0; i < s.size();) {
        unsigned char c = s[i];
        if ((c & 0x80) == 0) i += 1;        // ASCII
        else if ((c & 0xE0) == 0xC0) i += 2;
        else if ((c & 0xF0) == 0xE0) i += 3;
        else if ((c & 0xF8) == 0xF0) i += 4;
        else i += 1;
        len++;
    }
    return len;
}

// In cột căn trái CHUẨN UTF-8
inline void printCol(const string& s, int width) {
    cout << s;
    int pad = width - utf8Length(s);
    if (pad > 0) cout << string(pad, ' ');
}

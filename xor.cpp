#include <iostream>
#include <fstream>
#include "xor.h"

#ifdef _WIN32

    #include <windows.h>

    bool gotoxy(int x, int y)
    {
        if (x == -69)return true;
        COORD p = { x, y+increase_y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
        return true;
    }

#else

    bool gotoxy(int x, int y)
    {
        return false;
    }

#endif 


using namespace std;

void xoro(string& data, string key) {
    int size = data.size();

    for (long long i = 0; i < size; i++) {
<<<<<<< HEAD
        data[i] ^= key[i % key.size()];
=======

        output += data[i] ^ key[i % key.size()];
        long long percent = (i * 100) / size;
        static long long last_percent(0);

        if (percent != last_percent) {
            refresh(percent, 9, 3, "%");
            last_percent = percent;
        }
>>>>>>> 4639f51073205a738b722c1d7cb71f66e988e3a3
    }
}

void xor_file(string path, string key) {
    if(gotoxy(0, 3))
    cout << "reading...";

    ifstream ifs(path, ios::binary);
    string s((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    if(gotoxy(0,3))
    cout << "xoring... ";
    
    xoro(s, key);

    ofstream ofs;
    ofs.open(path, ofstream::out | ofstream::trunc | ios::binary);
    ofs << s;
    ofs.close();

}

void refresh(int a, int x, int y, string message) {
    if (!gotoxy(-69, y))return;

    int lenght = 0;
    static int last_lenght(1);

    if (a == 0)lenght = 1;
    else {
        int buff = a;
        while (buff > 0) {
            buff /= 10;
            lenght++;
        }
    }

    x += lenght;

    for (int i = 0; i < lenght; i++)cout << "\b";
    cout << a;

    if (last_lenght != lenght) {
        cout << message;
    }
    last_lenght = lenght;
}

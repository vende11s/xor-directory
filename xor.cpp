#include <iostream>
#include <fstream>
#include "xor.h"

#ifdef _WIN32

    #include <windows.h>

    void gotoxy(int x, int y)
    {
        COORD p = { x, y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
    }

#else

    #include <unistd.h>
    #include <term.h>

    void gotoxy(int x, int y)
    {
        int err;
        if (!cur_term)
            if (setupterm(NULL, STDOUT_FILENO, &err) == ERR)
                return;
       putp(tparm(tigetstr("cup"), y, x, 0, 0, 0, 0, 0, 0, 0));
    }

#endif 


using namespace std;

string xoro(string data, string key) {
    string output = "";
    int size = data.size();

    for (int i = 0; i < size; i++) {

        output += data[i] ^ key[i % key.size()];
        int percent = (i * 100) / size;
        static int last_percent(0);

        if (percent != last_percent) {
            refresh(percent, 9, 3, "%");
            last_percent = percent;
        }
    }

    return output;
}

void xor_file(string path, string key) {
    gotoxy(0, 3);
    cout << "reading...  ";

    ifstream ifs(path, ios::binary);
    string s((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    for (int i = 0; i < 13; i++)cout << "\b";
    cout << "xoring...0%";
    s = xoro(s, key);

    ofstream ofs;
    ofs.open(path, ofstream::out | ofstream::trunc | ios::binary);
    ofs << s;
    ofs.close();

}

void refresh(int a, int x, int y, string message) {
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

    gotoxy(x, y);

    for (int i = 0; i < lenght; i++)cout << "\b";
    cout << a;

    if (last_lenght != lenght) {
        cout << message;
    }
    last_lenght = lenght;
}
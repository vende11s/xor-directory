#include <iostream>
#include <filesystem>
#include "xor.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char** argv)
{
    string key, dir;

    if (argc == 2) { cout << "usage\n" <<argv[0]<<" [key] [dir]\n '.' for current dir\n"; increase_y = 3; }

    if (argc > 2) {
        key = argv[1];
        dir = argv[2];
        increase_y = -2;
    }
    else {
        cout << "Enter Key: ";
        cin >> key;

        cout << "Enter dir ('.' for " << fs::current_path().string() << "):";
        cin >> dir;
    }

    if (dir == ".") dir = fs::current_path().string();
    else {
        if (fs::exists(fs::current_path().string() + dir)) dir = fs::current_path().string() + dir;
        if (fs::exists(fs::current_path().string() + "/" + dir)) dir = fs::current_path().string() + "/" + dir;

        if (!fs::exists(dir)) {
            cout << "Wrong path!\n";
            cout << "Quiting...\n";
            return 1;
        }
    }
    int count_files = 0;
    for (const auto& entry : fs::directory_iterator(dir)) if(!entry.is_directory())count_files++;

    if (gotoxy(-69, 0))cout << "file " << 0 << " of " << count_files << " done" << endl;
    else cout << count_files << " to xor, please be paceful and wait...";

    for (const auto& entry : fs::directory_iterator(dir)) {

        if (entry.path().filename().string() == argv[0]);
        if (entry.is_directory()) continue; 

        static int counter(0);
        xor_file(entry.path().string(), key);
        refresh(++counter, 5, 2, " of " + to_string(count_files) + " done");
    }
}
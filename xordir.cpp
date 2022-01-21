#include <iostream>
#include <filesystem>
#include "xor.h"

using namespace std;
namespace fs = std::filesystem;

int main()
{
    string key, dir;
    cout << "Enter Key: ";
    cin >> key;

    cout << "Enter dir ('.' for " << fs::current_path() << "):";
    cin >> dir;

    if (dir == ".")dir = fs::current_path().string();
    else {
        if (fs::exists(fs::current_path().string() + dir)) dir = fs::current_path().string() + dir;
        if (fs::exists(fs::current_path().string() + "/" + dir)) dir = fs::current_path().string() + "/" + dir;

        if (!fs::exists(dir)) {
            cout << "Wrong path!\n";
            cout << "Quiting...";
            return 1;
        }
    }

    int count_files = 0;
    for (const auto& entry : fs::directory_iterator(dir)) count_files++;

    cout << "file " << 0 << " of " << count_files << " done"<<endl;

    for (const auto& entry : fs::directory_iterator(dir)) {
        static int counter(0);
        xor_file(entry.path().string(), key);
        refresh(++counter, 5, 2, " of " + to_string(count_files) + " done");
    }
}
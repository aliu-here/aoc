#include <iostream>
#include <fstream>

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    int dial = 50;
    int count = 0;
    while (getline(in, line)) {
        int val = stoi(line.substr(1));

        if (line[0] == 'L') {
            count += (val + (100 - dial) % 100) / 100;
            dial -= val;
        } else {
            count += (val + dial) / 100;
            dial += val;
        }
        dial = (dial + 1000000) % 100; // big number so if really big left rotation it still mods correctly

//        std::cout << line << ' ' << count << '\n';
    }
    std::cout << count << '\n';
}

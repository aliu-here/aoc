#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    std::vector<std::string> schematic;
    std::vector<std::array<int, 5>> keys, locks;
    while (getline(in, line)) {
        schematic.clear();
        schematic.push_back(line);
        for (int i=0; i<6; i++) {
            getline(in, line);
            schematic.push_back(line);
        }
        if (schematic[0] == "#####") {
            std::array<int, 5> values;
            for (int i=0; i<5; i++) {
                int count = 0;
                for (int j=1; j<6; j++) {
                    if (schematic[j][i] != '#')
                        break;
                    count++;
                }
                values[i] = count;
            }
            locks.push_back(values);
        } else if (schematic[6] == "#####") {
            std::array<int, 5> values;
            for (int i=0; i<5; i++) {
                int count = 0;
                for (int j=5; j>0; j--) {
                    if (schematic[j][i] != '#')
                        break;
                    count++;
                }
                values[i] = count;
            }
            keys.push_back(values);
        }
        getline(in, line); //empty spaces
    }

    int out = 0;
    for (auto key_vals : keys) {
        for (auto lock_vals : locks) {
            bool works = true;
            for (int i=0; i<5; i++) {
                if (lock_vals[i] + key_vals[i] > 5)
                    works = false;
            }
            out += works;
        }
    }

    std::cout << "p1: " << out << '\n';
}

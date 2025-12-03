#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    std::vector<std::string> lines;
    while (getline(in, line)) {
        lines.push_back(line);
    }

    auto start = std::chrono::steady_clock::now();


    long long out = 0;
    for (std::string line : lines) {
        std::vector<std::vector<int>> locs(9);
        int idx = 0;
        for (char ch : line) {
            locs[57-ch].push_back(idx);
            idx++;
        }

        int max = 0, first_digit = 9;
        for (std::vector<int> first : locs) {
            if (first_digit * 10 + 9 < max) {
                break;
            }
            for (int start : first) {
                for (int i=start + 1; i<line.size(); i++) {
                    max = std::max(max, 10 * (first_digit) + line[i] - 48);
                    if (max == first_digit*10+9) {
                        break;
                    }
                }
            }
            first_digit--;
        }

        out += max;
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';

    std::cout << out << '\n';}

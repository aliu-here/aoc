#include <iostream>
#include <vector>
#include <fstream>
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

    int dial = 50;
    int count = 0;
    for (std::string line : lines) {
        int val = stoi(line.substr(1));
        if (line[0] == 'L') {
            dial -= val;
        } else {
            dial += val;
        }
        dial = (dial + 10000000) % 100;
        if (dial == 0) {
            count++;
        }
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';
    std::cout << count << '\n';
}

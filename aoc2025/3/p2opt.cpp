#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

long long best(std::string value, int digits_to_take = 12) {
    long long out = 0;
    int index = 0;
    for (int i=digits_to_take; i>0; i--) {
        int max_value = 0;
        for (int j=index; j<value.size()- i + 1; j++) {
            max_value = std::max(value[j]-48, max_value);
        }
        for (int j=index; j<value.size() - i + 1; j++) {
            if (value[j]-48 == max_value) {
                index = j+1;
                break;
            }
        }
        out *= 10;
        out += max_value;
    }

    return out;
}

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
        out += best(line, 12);
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';

    std::cout << out << '\n';}

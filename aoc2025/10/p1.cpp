#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <cmath>

std::vector<std::string> split(const std::string s, const std::string delimiter) 
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(s.substr (pos_start));
    return res;
}

int main()
{
    std::ifstream in("input.txt");
    std::vector<std::string> lines;
    std::string line;
    while (getline(in, line)) {
        lines.push_back(line);
    }

    auto start = std::chrono::steady_clock::now();

    long long out = 0;
    for (std::string line : lines) {
        auto data = split(line, " ");
        std::string target = data[0].substr(1, data[0].size() - 2);
        int target_val = 0, counter = 1;
        for (int i=0; i < target.size(); i++) {
            target_val += (target[i] == '#') * counter;
            counter *= 2;
        }
        std::vector<int> button_wires;
        for (int i=1; i<data.size() - 1; i++) {
            auto tmp = split(data[i].substr(1, data[i].size() - 2), ",");
            int val = 0;
            for (std::string str_val : tmp) {
                val += (int)(std::pow(2, std::stoi(str_val)));
            }
            button_wires.push_back(val);
        }

        int shortest = 1000;
        for (int i=0; i<pow(2, button_wires.size()); i++) {
            int val=i, state = 0, count = 0;
            for (int j=0; j<button_wires.size(); j++) {
                if (val % 2) {
                    state ^= button_wires[j];
                    count++;
                }
                val /= 2;
            }
            bool match = (state == target_val);
            if (match) {
                shortest = std::min(shortest, count);
            }
        }
        out += shortest;
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';
    std::cout << out << '\n';
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

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
    std::string line;
    std::vector<std::string> lines;
    while (getline(in, line)) {
        lines.push_back(line);
    }

    auto start = std::chrono::steady_clock::now();

    long long out = 0;

    std::vector<std::vector<std::string>> ranges;
    bool ranges_section = true;
    for (std::string line : lines) {
        if (line == "") {
            ranges_section = false;
            continue;
        }
        if (ranges_section) {
            ranges.push_back(split(line, "-"));
        } else {
            long val = std::stol(line);
            for (auto range : ranges) {
                long l = std::stol(range[0]), r=std::stol(range[1]);
                if (val >= l && val <= r) {
                    out++;
                    break;
                }
            }
        }

    }

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';

    std::cout << out << '\n';
}

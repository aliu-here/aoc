#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>

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

    std::vector<std::vector<long long>> ranges;
    bool ranges_section = true;
    for (std::string line : lines) {
        if (line == "") {
            ranges_section = false;
            break;
        }
        if (ranges_section) {
            std::vector<std::string> tmp = split(line, "-");
            ranges.push_back({std::stol(tmp[0]), std::stol(tmp[1])});
        }
    }


    std::sort(ranges.begin(), ranges.end(), [](std::vector<long long> a, std::vector<long long> b) {
            return a[0] < b[0];
            });

    std::vector<std::vector<long long>> comp_ranges;
    long long curr_begin = ranges[0][0], curr_end = ranges[0][1];
    for (int i=0; i<ranges.size(); i++) {
        auto range = ranges[i];
        if (range[0] <= curr_end + 1) {
            curr_end = std::max(curr_end, range[1]);
        } else {
            comp_ranges.push_back({curr_begin, curr_end});
            curr_begin = range[0];
            curr_end = range[1];
        }
    }

    comp_ranges.push_back({curr_begin, curr_end});

    for (auto range : comp_ranges) {
        out += range[1] - range[0] + 1;
    }


    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';

    std::cout << out << '\n';
}

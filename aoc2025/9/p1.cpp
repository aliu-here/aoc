#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <array>

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
    
    std::vector<std::array<long long, 2>> points;
    for (std::string line : lines) {
        auto tmp = split(line, ",");
        points.push_back({std::stol(tmp[0]), std::stol(tmp[1])});
    }

    for (int i=0; i<points.size(); i++) {
        for (int j=i+1; j<points.size(); j++) {
            if (std::abs(points[i][0]-points[j][0] + 1) * std::abs(points[i][1] - points[j][1] + 1) > out) {
                std::cout << points[i][0] << ',' << points[i][1] << ' ' << points[j][0] << ',' << points[j][1] << ", area: " << std::abs(points[i][0]-points[j][0] + 1) * std::abs(points[i][1] - points[j][1] + 1) << '\n';
            }
            out = std::max(out, std::abs(points[i][0]-points[j][0] + 1) * std::abs(points[i][1] - points[j][1] + 1));
        }
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';
    std::cout << out << '\n';
}

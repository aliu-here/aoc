#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <unordered_map>

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
    std::vector<std::vector<std::vector<bool>>> shapes;
    std::vector<int> volumes;
    int lineptr = 1;
    for (int i=0; i<=5; i++) {
        int count = 0;
        for (int j=0; j<3; j++) {
            for (char ch : lines[lineptr]) {
                count += ch == '#';
            }
            lineptr++;
        }
        volumes.push_back(count);
        lineptr += 2;
    }
    
    std::cout << lines[lineptr] << '\n';

    for (; lineptr < lines.size(); lineptr++) {
        auto tmp = split(lines[lineptr], " ");
        auto range = split(tmp[0].substr(0, tmp[0].size() - 1), "x");
        int total_vol = 0;
        for (int i=1; i<tmp.size(); i++) {
            int presentnum = std::stoi(tmp[i]);
            total_vol += volumes[i-1] * presentnum;
        }
        int available_area = std::stoi(range[0]) * std::stoi(range[1]);

        out += available_area >= total_vol;
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';

    std::cout << out << '\n';
}

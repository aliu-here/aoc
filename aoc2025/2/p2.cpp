#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <unordered_set>

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

long long pow10(int val) {
    long long out = 1;
    for (int i=0; i<val; i++) {
        out *= 10;
    }
    return out;
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    getline(in, line);
    std::vector<std::string> ranges = split(line, ",");

    std::unordered_set<long long> invalids;
    for (std::string range : ranges) {
        std::vector<std::string> bounds = split(range, "-");
        int l_size = bounds[0].size(), r_size = bounds[1].size();
        long long l_bound = stol(bounds[0]), r_bound = stol(bounds[1]);
//        std::cout << bounds[0] << ' ' << bounds[1] << '\n';
//        std::cout << pow10((l_size - 1) / 2) << ' ' << pow10((r_size - 1) / 2 + 1) << '\n';
        for (int i=1; i <= pow10((r_size - 1) / 2 + 1); i++) {
            for (int j=2; j<=std::ceil(r_size / std::ceil(std::log10(i + 1))); j++) {
                std::string val;
                for (int reps = 0; reps < j; reps++) {
                    val += std::to_string(i);
                }
//                std::cout << val << '\n';
                long long converted_val = stol(val);
                if (converted_val >= l_bound && converted_val <= r_bound) {
//                    std::cout << converted_val << '\n';
                    invalids.insert(converted_val);
                }
                if (converted_val > r_bound) {
                    continue;
                }
            }
        }
//        std::cout << '\n';
    }

    long long out = 0;
    for (long long val : invalids) {
//        std::cout << val << '\n';
        out += val;
    }

    std::cout << out << '\n';
}

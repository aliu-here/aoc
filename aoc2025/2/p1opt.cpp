#include <iostream>
#include <vector>
#include <fstream>

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

    long long out = 0;
    for (std::string range : ranges) {
        std::vector<std::string> bounds = split(range, "-");
        int l_size = bounds[0].size(), r_size = bounds[1].size();
        long long l_bound = stol(bounds[0]), r_bound = stol(bounds[1]);
        if (l_size % 2 == 1) {
            l_bound = pow10(l_size);
            l_size++;
        }
        if (r_size % 2 == 1) {
            r_bound = pow10(r_size - 1) - 1;
            r_size--;
        }

        long long half_lower = stol(std::to_string(l_bound).substr(0, l_size / 2)), half_upper = stol(std::to_string(r_bound).substr(0, l_size / 2));

        for (long long i = half_lower; i <= half_upper; i++) {
            long long val = stol(std::to_string(i) + std::to_string(i));
            if (val >= l_bound && val <= r_bound) {
                out += val;
            }
            if (val > r_bound) {
                break;
            }
        }
    }
    std::cout << out << '\n';
}

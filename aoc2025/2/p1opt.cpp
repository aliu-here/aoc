#include <iostream>
#include <vector>
#include <fstream>

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
    
    auto start = std::chrono::steady_clock::now();

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

        if (r_bound < l_bound) {
            continue;
        }

        long long half_lower = stol(std::to_string(l_bound).substr(0, l_size / 2)), half_upper = stol(std::to_string(r_bound).substr(0, r_size / 2));

        long long doubled_l = half_lower * (pow10(l_size / 2) + 1), doubled_r = half_upper * (pow10(r_size / 2) + 1);

        if (doubled_l < l_bound) {
            half_lower++;
        }
        if (doubled_r > r_bound) {
            half_upper--;
        }

        if (half_lower > half_upper) {
            continue;
        }

        out += ((half_upper * (half_upper + 1)) - (half_lower * (half_lower - 1))) / 2 * (pow10(r_size / 2) + 1);
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';

    std::cout << out << '\n';
}

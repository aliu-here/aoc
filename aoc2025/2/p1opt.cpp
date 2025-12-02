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

int ceil_log10(long long val) {
    long long tmp = 1;
    int count = 0;
    while (tmp <= val) {
        tmp *= 10;
        count++;
    }
    return count;
}
long long repeat_val(int repeat_count, int repeat_len) {
    return (pow10(repeat_count * repeat_len) - 1) / (pow10(repeat_len) - 1);
} 
long long count_invalid_under(long long val) {
    int log = ceil_log10(val);
    long long out = 0;
    for (int j=1; j<=log / 2; j++) {
        long long repeat_multiplier = repeat_val(2, j);
        long long div = (val % repeat_val(2, j) == 0) ? val/repeat_multiplier : (val/repeat_multiplier) + 1;
        long long min_rep = std::min(div, pow10(j));
        out += (min_rep + pow10(j - 1) - 1) * (min_rep - pow10(j - 1)) * repeat_multiplier;
    }

    out /= 2;
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
        long long l_bound = stol(bounds[0]), r_bound = stol(bounds[1]);
        out += count_invalid_under(r_bound + 1) - count_invalid_under(l_bound);
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';

    std::cout << out << '\n';
}

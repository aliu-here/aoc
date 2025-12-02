#include <iostream>
#include <vector>
#include <fstream>
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

    long long out = 0;

    std::unordered_set<long long> values;

    for (std::string range : ranges) {
        std::vector<std::string> bounds = split(range, "-");
        int l_size = bounds[0].size(), r_size = bounds[1].size();

        for (int repeat_number = 2; repeat_number <= r_size; repeat_number++) {
            bool could_work = 0;
            for (int i=l_size; i<=r_size; i++) {
                could_work |= (i % repeat_number == 0);
            }
            if (!could_work) {
                continue;
            }
            long long l_bound = stol(bounds[0]), r_bound = stol(bounds[1]);
            long long l_length = l_size, r_length = r_size;
            if (l_length % repeat_number == repeat_number - 1) {
                l_bound = pow10(l_length);
                l_length++;
            }
            if (r_length % repeat_number == 1) {
                r_bound = pow10(r_length - 1) - 1;
                r_length--;
            }

            long long half_lower = stol(std::to_string(l_bound).substr(0, l_length / repeat_number)), half_upper = stol(std::to_string(r_bound).substr(0, l_length / repeat_number));

            for (long long i = half_lower; i <= half_upper; i++) {
                std::string str_val;
                for (int rep = 0; rep < repeat_number; rep++) {
                    str_val += std::to_string(i);
                }
                long long val = stol(str_val);
                if (val >= l_bound && val <= r_bound && values.find(val) == values.end()) {
                    out += val;
                    values.insert(val);
                }
                if (val > r_bound) {
                    break;
                }
            }
        }
    }
    std::cout << out << '\n';
}

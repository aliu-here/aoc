#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>

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

std::unordered_set<int> primes = {2};
std::vector<int> mobius_cache = {1};
int mobius_func(int val) {
    if (mobius_cache.size() >= val && mobius_cache[val - 1] != -100) {
        return mobius_cache[val - 1];
    }
    int prime_count = 0;
    int orig_val = val;
    for (int prime : primes) {
        int div_count = 0;
        if (val % prime == 0) {
            prime_count++;
        }
        while (val % prime == 0) {
            val /= prime;
            div_count++;
            if (div_count >= 2) {
                return 0;
            }
        }
    }

    if (prime_count == 0) {
        primes.insert(val);
        prime_count++;
    }
    
    int out = (prime_count % 2) ? -1 : 1;
    mobius_cache.resize(val, -100);

    mobius_cache[val - 1] = out;

    return (prime_count % 2) ? -1 : 1;
}

long long repeat_val(int repeat_count, int repeat_len) {
    return (pow10(repeat_count * repeat_len) - 1) / (pow10(repeat_len) - 1);
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

long long sum_invalid_to(long long val) {
    int log = ceil_log10(val);
    long long out = 0;
    for (int i=2; i<=log; i++) {
        int mobius_val = mobius_func(i);
        if (mobius_val == 0) {
            continue;
        }

        for (int j=1; j<=log / i; j++) {
            long long repeat_multiplier = repeat_val(i, j);
            long long div = (val % repeat_val(i, j) == 0) ? val/repeat_multiplier : (val/repeat_multiplier) + 1;
            long long min_rep = std::min(div, pow10(j));
            out += (min_rep + pow10(j - 1) - 1) * (min_rep - pow10(j - 1)) * repeat_multiplier * mobius_val;
        }
    }

    out /= -2;
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

    std::unordered_set<long long> values;

    for (std::string range : ranges) {
        std::vector<std::string> bounds = split(range, "-");
        int l_size = bounds[0].size(), r_size = bounds[1].size();
        out += sum_invalid_to(std::stol(bounds[1]) + 1) - sum_invalid_to(std::stol(bounds[0]));
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';


    std::cout << out << '\n';
}

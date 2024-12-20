#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

std::vector<std::string> split(const std::string& s, const std::string& delimiter) 
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

std::unordered_map<std::string, long long> memoize;
std::vector<std::string> poss_patterns;

long long pattern_creatable(std::string to_create);

long long call_pattern_creatable(std::string to_create)
{
    if (memoize.find(to_create) == memoize.end()) {
        long long result = pattern_creatable(to_create);
        memoize[to_create] = result;
        return result;
    } else {
        return memoize[to_create];
    }
}

long long pattern_creatable(std::string to_create)
{
    if (to_create == "")
        return true;

    long long output = 0;
    for (std::string pattern : poss_patterns) {
        bool works = true;
        if (to_create.size() < pattern.size())
            continue;
//        std::cout << "to_create: " << to_create << '\n';
//        std::cout << "pattern: " << pattern << '\n';
        for (long long i=0; i<pattern.size(); i++) {
            if (to_create[i] != pattern[i]) {
                works = false;
                break;
            }
        }

//        std::cout << "works: " << works << '\n';

        if (works) {
            output += call_pattern_creatable(to_create.substr(pattern.size(), to_create.size() - pattern.size()));
        }
    }
    return output;
}

int  main()
{
    std::ifstream in("input.txt");
    std::string line;
    getline(in, line);
    poss_patterns = split(line, ", ");

    getline(in, line);
    long long p2 = 0;
    while (getline(in, line)) {
        p2 += call_pattern_creatable(line);
//        std::cout << "line done\n";
    }
    std::cout << p2 << '\n';
}

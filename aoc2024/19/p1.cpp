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

std::unordered_map<std::string, bool> memoize;

bool pattern_creatable(std::string to_create, std::vector<std::string> &poss_patterns);

bool call_pattern_creatable(std::string to_create, std::vector<std::string> &poss_patterns)
{
    std::string concated="";
    for (std::string pattern : poss_patterns)
        concated += pattern;
    if (memoize.find(to_create + concated) == memoize.end()) {
        bool result = pattern_creatable(to_create, poss_patterns);
        memoize[to_create + concated] = result;
        return result;
    } else {
        return memoize[to_create + concated];
    }
}

bool pattern_creatable(std::string to_create, std::vector<std::string> &poss_patterns)
{
    if (to_create == "")
        return true;

    for (std::string pattern : poss_patterns) {
        bool works = true;
        if (to_create.size() < pattern.size())
            continue;
//        std::cout << "to_create: " << to_create << '\n';
//        std::cout << "pattern: " << pattern << '\n';
        for (int i=0; i<pattern.size(); i++) {
            if (to_create[i] != pattern[i]) {
                works = false;
                break;
            }
        }

//        std::cout << "works: " << works << '\n';

        if (works) {
            if (call_pattern_creatable(to_create.substr(pattern.size(), to_create.size() - pattern.size()), poss_patterns))
                return true;
        }
    }
    return false;
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    getline(in, line);
    std::vector<std::string> subpatterns = split(line, ", ");
    getline(in, line);
    int p1 = 0;
    while (getline(in, line)) {
        if (call_pattern_creatable(line, subpatterns))
            p1++;
        std::cout << "line done\n";
    }
    std::cout << p1 << '\n';
}

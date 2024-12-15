#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

//stolen from stackoverflow
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

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    long long p1 = 0;
    std::string input;
    std::vector<std::vector<std::string>> rules;
    bool in_rules=true;
    while (getline(in, line)) {
        if (line == "\n" || line == "") {
            in_rules = false;
            continue;
        }
        if (in_rules) {
            rules.push_back(split(line, "|"));
        } else {
            std::unordered_map<std::string, int> page_loc;
            std::vector<std::string> pages = split(line, ",");
            for (int i=0; i<pages.size(); i++) {
                page_loc[pages[i]] = i;
            }
            bool works = true;
            for (std::vector<std::string> rule : rules) {
                if ((page_loc.find(rule[0]) != page_loc.end() &&
                     page_loc.find(rule[1]) != page_loc.end()) &&
                    page_loc[rule[0]] > page_loc[rule[1]]) {
                    works = false;
                    break;
                }
            }
            if (works) {
                p1 += std::stoi(pages[pages.size() / 2]);
            }
        }
    }
    std::cout << "p1: " << p1 << '\n';
}

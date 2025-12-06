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
    std::vector<std::vector<long long>> vals; 
    for (int i=0; i<lines.size() - 1; i++) {
        std::vector<long long> tmp;
        for (std::string val : split(lines[i], " ")) {
            if (val == "") {
                continue;
            }
            tmp.push_back(std::stol(val));
        }
        vals.push_back(tmp);
    }

    std::vector<char> ops;
    for (std::string token : split(lines[lines.size() - 1], " ")) {
        if (token == "") {
            continue;
        }
        ops.push_back(token[0]);
    }

    std::cout << "finished parsing\n";

    for (int i=0; i<vals[0].size(); i++) {
        long long tmp = vals[0][i];
        for (int j=1; j<vals.size(); j++) {
            if (ops[i] == '*') {
                tmp *= vals[j][i];
            } else {
                tmp += vals[j][i];
            }
        }
        out += tmp;
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';
    std::cout << out << '\n';
}

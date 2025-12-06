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

    unsigned long long out = 0;
    std::vector<char> ops;
    for (std::string token : split(lines[lines.size() - 1], " ")) {
        if (token == "") {
            continue;
        }
        ops.push_back(token[0]);
    }

    std::vector<unsigned long long> vals;
    int curr_op = ops.size() - 1;
    for (int j=lines[0].size() - 1; j >= 0; j--) {
        std::string col;
        for (int i=0; i<lines.size() - 1; i++) {
            if (lines[i][j] != ' ') {
                col += lines[i][j];
            }
        }
        if (col != "") {
            vals.push_back(std::stol(col));
        }
        if (col == "" || j == 0){
            if (vals.size() == 0) {
                continue;
            }
            unsigned long long tmp = vals[0];
            for (int val_idx = 1; val_idx < vals.size(); val_idx++) {
                if (ops[curr_op] == '*') {
                    tmp *= vals[val_idx];
                } else {
                    tmp += vals[val_idx];
                }
            }
            out += tmp;
            curr_op--;
            vals.clear();
        }
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';
    std::cout << out << '\n';
}

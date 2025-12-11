#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <unordered_map>

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
    std::unordered_map<std::string, int> ids;
    std::vector<std::vector<int>> conn_list;
    int curr_id = 0;

    for (auto row : lines) {
        auto data = split(row, " ");
        for (int i=1; i<data.size(); i++) {
            if (ids.find(data[i]) == ids.end()) {
                ids[data[i]] = curr_id;
                curr_id++;
            }
        }

        std::string src = data[0].substr(0, 3);
        if (ids.find(src) == ids.end()) {
            ids[src] = curr_id;
            curr_id++;
        }

        conn_list.resize(curr_id + 1);
        for (int i=1; i<data.size(); i++) {
            std::cout << data[i] << ' ';
            conn_list[ids[src]].push_back(ids[data[i]]);
        }
        std::cout << '\n';
    }

    std::string start_node = "you";
    std::vector<int> next = {ids[start_node]};
    while (next.size()) {
        std::vector<int> queue = {};
        for (int val : next) {
            for (int to_add : conn_list[val]) {
                if (to_add == ids["out"]) {
                    out++;
                } else {
                    queue.push_back(to_add);
                }
            }
        }

        next = queue;
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';

    std::cout << out << '\n';
}

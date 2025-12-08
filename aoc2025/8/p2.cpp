#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
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

long long squareddist(std::vector<long long> a, std::vector<long long> b) {
    return (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]) + (a[2] - b[2]) * (a[2] - b[2]);
}

bool complete(std::vector<std::vector<int>> connectivity_list) {
    std::vector<int> to_visit = {0};
    std::vector<bool> visited(connectivity_list.size());
    int visit_count = 0;
    do {
        std::vector<int> next_visits;
        for (int val : to_visit) {
            if (visited[val] != 0) {
                continue;
            }
            visited[val] = 1;
            visit_count++;
            next_visits.insert(next_visits.end(), connectivity_list[val].begin(), connectivity_list[val].end());
        }
        to_visit = next_visits;
    } while (to_visit.size() > 0);
    return visit_count == connectivity_list.size();
}

int main()
{
    std::vector<std::string> lines;
    std::ifstream in("input.txt");
    std::string line;
    while (getline(in, line)) {
        lines.push_back(line);
    }

    auto start = std::chrono::steady_clock::now();
    
    std::vector<std::vector<long long>> posns;

    for (std::string line : lines) {
        auto vals = split(line, ",");
        posns.push_back({std::stol(vals[0]), std::stol(vals[1]), std::stol(vals[2])});
    }

    std::vector<std::pair<long long, std::array<int, 2>>> squareddists;
    for (int i=0; i<posns.size(); i++) {
        for (int j=i+1; j<posns.size(); j++) {
            squareddists.push_back(std::pair<long long, std::array<int, 2>>(squareddist(posns[i], posns[j]), {i, j}));
        }
    }

    std::sort(squareddists.begin(), squareddists.end(), [](std::pair<long long, std::array<int, 2>> a, std::pair<long long, std::array<int, 2>> b) {
            return std::get<0>(a) < std::get<0>(b);
            });

    std::unordered_set<int> joined;
    long long out = 0;
    std::vector<std::vector<int>> connectivity_list(posns.size());
    for (auto val : squareddists) {
        auto pair = std::get<1>(val);
        connectivity_list[pair[0]].push_back(pair[1]);
        connectivity_list[pair[1]].push_back(pair[0]);
        if (complete(connectivity_list)) {
            out = posns[pair[0]][0] * posns[pair[1]][0];
            std::cout << posns[pair[0]][0] << ' '<< posns[pair[1]][0] << '\n';
            break;
        }
    }
 
    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';
    std::cout << out << '\n';
}

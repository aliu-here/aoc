#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
#include <array>

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

    std::vector<std::vector<int>> links(posns.size());
    for (int i=0; i<posns.size(); i++) {
        auto link = std::get<1>(squareddists[i]);
        links[link[0]].push_back(link[1]);
        links[link[1]].push_back(link[0]);
    }

    int cycle_num = 1, cycle_size = 0;
    long long out = 1;
    std::vector<int> box_vals(posns.size(), 0);
    std::vector<int> circuits;
    for (int i=0; i<posns.size(); i++) {
        if (links[i].size() == 0 || box_vals[i] != 0) {
            continue;
        }
        std::vector<int> to_visit = {i};
        do {
            std::vector<int> next_visits;
            for (int val : to_visit) {
                if (box_vals[val] != 0) {
                    continue;
                }
                box_vals[val] = cycle_num;
                cycle_size++;
                next_visits.insert(next_visits.end(), links[val].begin(), links[val].end());
            }
            to_visit = next_visits;
        } while (to_visit.size() > 0);
        circuits.push_back(cycle_size);
        cycle_num++;
        cycle_size = 0;
    }

    std::sort(circuits.begin(), circuits.end(), std::greater<int>());
    out = circuits[0] * circuits[1] * circuits[2];
        
    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';
    std::cout << out << '\n';
}

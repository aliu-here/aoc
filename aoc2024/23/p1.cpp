#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

struct node {
    std::string name;
    std::vector<std::string> neighbors;
};

std::vector<std::string> find_overlaps(std::vector<std::string> a, std::vector<std::string> b)
{
    std::vector<std::string> out;
    for (std::string a_str : a) {
        for (std::string b_str : b) {
            if (a_str == b_str)
                out.push_back(a_str);
        }
    }
    return out;
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    std::unordered_map<std::string, node> network;
    while (getline(in, line)) {
        std::string cmp1 = line.substr(0, 2), cmp2 = line.substr(3, 2);
        if (network.find(cmp1) == network.end()) {
            node new_cmp;
            new_cmp.name = cmp1;
            new_cmp.neighbors.push_back(cmp2);
            network[cmp1] = new_cmp;
        } else {
            network[cmp1].neighbors.push_back(cmp2);
        }
        if (network.find(cmp2) == network.end()) {
            node new_cmp;
            new_cmp.name = cmp2;
            new_cmp.neighbors.push_back(cmp1);
            network[cmp2] = new_cmp;
        } else {
            network[cmp2].neighbors.push_back(cmp1);
        }
    }

    std::set<std::set<std::string>> cycles;

    int count = 0;
    for (auto pair : network) {
        node curr_cmp = pair.second;
        if (curr_cmp.name[0] != 't')
            continue;
        std::cout << curr_cmp.name << '\n';
        for (std::string neighbor : curr_cmp.neighbors) {
            std::cout << neighbor << '\n';
            for (std::string shared : find_overlaps(network[neighbor].neighbors, curr_cmp.neighbors)) {
                std::set<std::string> temp;
                temp.insert(curr_cmp.name); temp.insert(neighbor); temp.insert(shared);
                cycles.insert(temp);
            }
        }
    }
    std::cout << "p1: " <<cycles.size() << '\n';
}

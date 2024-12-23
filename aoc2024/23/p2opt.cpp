#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

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

//bron-kerbosch
std::unordered_map<std::string, node> bron_kerbosch(std::unordered_map<std::string, node> R, std::unordered_map<std::string, node> &P)
{
    if (P.size() == 0)
       return R;
    std::unordered_map<std::string, node> final_out;
    auto pair = *P.begin();
//    std::cout << "pair.first: " << pair.first << '\n';
    std::unordered_map<std::string, node> new_P, new_X, new_R = R;
    new_R[pair.first] = pair.second;
    std::vector<std::string> p_strings, x_strings;
    for (auto node : P) 
        p_strings.push_back(node.first);

    for (std::string p_intersect : find_overlaps(p_strings, pair.second.neighbors))
        new_P[p_intersect] = P[p_intersect];

//    std::cout << '\t';
    std::unordered_map<std::string, node> output = bron_kerbosch(new_R, new_P);
    if (output.size() > final_out.size())
        final_out = output;

    P.erase(pair.first);
    return final_out;
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

    std::cout << "network size: " << network.size() << '\n';

    std::unordered_map<std::string, node> out;
    while (network.size() > 0) {
        auto temp = bron_kerbosch({}, network);
        if (temp.size() > out.size())
            out = temp;
    }
    std::cout << '\n';
    std::vector<std::string> best_vals;
    for (auto pair : out)
        best_vals.push_back(pair.first);

    std::sort(best_vals.begin(), best_vals.end());

    std::cout << "p2: ";
    for (std::string val : best_vals)
        std::cout << val << ',';
    std::cout << '\n';
}

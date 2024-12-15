#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    getline(in, line); //only one line
    std::vector<int> expanded_fs;
    std::vector<std::vector<int>> gaps;
    int net_size = 0;
    int current_id = 0;
    bool isfile = true;
    for (char ch : line) {
        if (isfile) {
            net_size += ch-48;
            for (int i=0; i<ch-48; i++) {
                expanded_fs.push_back(current_id);
            }
            current_id++;
        } else {
            if (ch - 48 != 0)
                gaps.push_back({(int)expanded_fs.size(), ch-48});
            for (int i=0; i<ch-48; i++) {
                expanded_fs.push_back(-1);
            }
        }
        isfile = !isfile;
    }

    int gap_index = 0;
    std::vector<int> curr_gap = gaps[gap_index];
    int curr_loc = curr_gap[0];
    for (int i=expanded_fs.size() - 1; i>=net_size; i--) {
        if (expanded_fs[i] != -1) {
            expanded_fs[curr_loc] = expanded_fs[i];
            expanded_fs[i] = -1;
            
            curr_loc++;
            if (curr_loc == curr_gap[0]+curr_gap[1]) {
                gap_index++;
                curr_gap = gaps[gap_index];
                curr_loc = curr_gap[0];
            }
        }
    }

    long long p1 = 0;
    for (int i=0; i<net_size; i++) {
        p1 += expanded_fs[i] * i;
    }
    std::cout << "p1: " << p1 << '\n';
}

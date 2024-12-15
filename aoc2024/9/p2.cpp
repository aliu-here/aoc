#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    getline(in, line); //only one line
    std::vector<int> expanded_fs;
    int file_count = 0;
    std::vector<std::vector<int>> freespace;
    std::vector<int> filestarts;
    std::vector<int> sizes;
    int current_id = 0;
    bool isfile = true;
    for (char ch : line) {
        if (isfile) {
            filestarts.push_back(expanded_fs.size());
            sizes.push_back(ch - 48);
            file_count += ch-48;
            for (int i=0; i<ch-48; i++) {
                expanded_fs.push_back(current_id);
            }
            current_id++;
        } else {
            if (ch-48 > 0) {
                freespace.push_back({(int)expanded_fs.size(), ch - 48});
            }
            for (int i=0; i<ch-48; i++) {
                expanded_fs.push_back(-1);
            }
        }
        isfile = !isfile;
    }


    bool any_works;
    std::set<int> locs_to_skip;
    for (int i=filestarts.size() - 1; i >= 0; i--) {
        if (locs_to_skip.find(i) != locs_to_skip.end())
            continue;
        bool this_works = false;
        for (int j=0; j<freespace.size(); j++) {
            if (freespace[j][0] > filestarts[i])
                break;
            if (freespace[j][1] >= sizes[i]) {
                this_works = true;
                for (int copy_idx = 0; copy_idx < sizes[i]; copy_idx++) {
                    expanded_fs[freespace[j][0] + copy_idx] = expanded_fs[filestarts[i] + copy_idx];
                    expanded_fs[filestarts[i] + copy_idx] = -1;
                }
                freespace[j][0] += sizes[i];
                freespace[j][1] -= sizes[i];
            }
            if (this_works) {
                locs_to_skip.insert(i);
                break;
            }
        }
    }


    long long p2 = 0;
    for (int i=0; i<expanded_fs.size(); i++) {
        if (expanded_fs[i] == -1)
            continue;
        p2 += expanded_fs[i] * i;
    }
    std::cout << "p2: " << p2 << '\n';
}

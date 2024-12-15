#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int main()
{
    std::ifstream in("input4.txt");
    std::string line;
    getline(in, line); //only one line
    std::vector<int> expanded_fs;
    int file_count = 0;
    std::vector<std::vector<int>> freespace;
    int current_id = 0;
    bool isfile = true;
    for (char ch : line) {
        if (isfile) {
            file_count += ch-48;
            for (int i=0; i<ch-48; i++) {
                expanded_fs.push_back(current_id);
            }
            current_id++;
        } else {
            if (ch-48 > 0) {
                freespace.insert(freespace.begin(), {(int)expanded_fs.size(), ch - 48});
            }
            for (int i=0; i<ch-48; i++) {
                expanded_fs.push_back(-1);
            }
        }
        isfile = !isfile;
    }


    int last_file = expanded_fs.size() - 1;
    int working_files = line[0] - 48;
    while (working_files != file_count) {
        std::vector<int> firstfreespace = freespace[freespace.size() - 1];
        freespace.pop_back();
        int filesleft = 0;
        for (int end = last_file; end >= firstfreespace[0] + firstfreespace[1]; end--) {
            if (expanded_fs[end] != -1) {
                expanded_fs[firstfreespace[0] + filesleft] = expanded_fs[end];
                expanded_fs[end] = -1;
                filesleft++;
            } 
            if (filesleft == firstfreespace[1]) {
                break;
            }
        }
        for (int i = 0; i < expanded_fs.size(); i++) {
            if (expanded_fs[i] == -1) {
                working_files = i;
                break;
            }
        }
        for (int end = last_file; end >= 0; end--) {
            if (expanded_fs[end] != -1) {
                last_file = end;
                break;
            }
        }
    }


    long long p1 = 0;
    for (int i=0; i<file_count; i++) {
        p1 += expanded_fs[i] * i;
    }
    std::cout << "p1: " << p1 << '\n';
}

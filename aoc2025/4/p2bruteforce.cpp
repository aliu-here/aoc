#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

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

    int tmp_count = 0;
    for (int i=0; i<lines.size(); i++) {
        for (int j=0; j<lines[i].size(); j++) {
            if (lines[i][j] != '@') {
                continue;
            }
            int count = 0;
            for (int rows=std::max(0, i-1); rows < std::min((int)lines.size(), i+2); rows++) {
                for (int cols = std::max(0, j-1); cols < std::min((int)lines[i].size(), j+2); cols++) {
                    if (lines[rows][cols] == '@') {
                        count++;
                    }
                }
            }

            if (count <= 4) {
                tmp_count++;
                lines[i][j] = '.';
            }
        }
    }
    out += tmp_count;

    while (tmp_count > 0) {
        tmp_count = 0;
        for (int i=0; i<lines.size(); i++) {
            for (int j=0; j<lines[i].size(); j++) {
                if (lines[i][j] != '@') {
                    continue;
                }
                int count = 0;
                for (int rows=std::max(0, i-1); rows < std::min((int)lines.size(), i+2); rows++) {
                    for (int cols = std::max(0, j-1); cols < std::min((int)lines[i].size(), j+2); cols++) {
                        if (lines[rows][cols] == '@') {
                            count++;
                        }
                    }
                }

                if (count <= 4) {
                    tmp_count++;
                    lines[i][j] = '.';
                }
            }
        }

        out += tmp_count;
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';

    std::cout << out << '\n';}

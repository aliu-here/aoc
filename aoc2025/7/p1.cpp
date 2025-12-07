#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>
#include <unordered_set>

struct pos {
    pos(int inrow, int incol) {
        row = inrow;
        col = incol;
    }
    int row, col;
};

int main()
{
    std::vector<std::string> grid;
    std::ifstream in("input.txt");
    std::string line;
    while (getline(in, line)) {
        grid.push_back(line);
    }

    auto start = std::chrono::steady_clock::now();

    std::vector<pos> beamstarts;
    for (int i=0; i<grid[0].size(); i++) {
        if (grid[0][i] == 'S') {
            beamstarts.push_back(pos(0, i));
            break;
        }
    }

    int out = 0;
    while (beamstarts.size() > 0) {
        std::unordered_set<long long> new_beamstarts;
        for (pos startpos : beamstarts) {
            for (int row = startpos.row; row < grid.size(); row++) {
                if (grid[row][startpos.col] == '|') {
                    break;
                }
                if (grid[row][startpos.col] == '^') {
                    out++;
                    if (startpos.col > 0) {
                        long long tmp = ((long long)(row) << 32) + (long long)(startpos.col - 1);
                        new_beamstarts.insert(tmp);
                    }
                    if (startpos.col < grid.size() - 1) {
                        long long tmp = ((long long)(row) << 32) + (long long)(startpos.col + 1);
                        new_beamstarts.insert(tmp);
                    }
                    break;
                }
                grid[row][startpos.col] = '|';
            }
        }

        beamstarts.clear();

        for (long long val : new_beamstarts) {
            int row = val >> 32;
            int col = (int)val;
            beamstarts.push_back(pos(row, col));
        }
    }

    std::cout << out << '\n';
}

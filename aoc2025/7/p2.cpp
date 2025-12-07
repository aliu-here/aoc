#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>
#include <unordered_map>

struct pos {
    pos(int inrow, int incol) {
        row = inrow;
        col = incol;
    }
    int row, col;
};

std::unordered_map<long long, long long> cache;
long long recursive(std::vector<std::string>& grid, pos startpos) {
    long long index = ((long long)(startpos.row) << 32) + (long long)(startpos.col);
    if (cache.find(index) != cache.end()) {
        return cache[index];
    }
    if (startpos.col < 0 || startpos.col >= grid.size()) {
        cache[index] = 0;
        return 0;
    }
    for (int row=startpos.row; row < grid.size(); row++) {
        if (grid[row][startpos.col] == '^') {
            long long out =  recursive(grid, pos(row, startpos.col - 1)) + recursive(grid, pos(row, startpos.col + 1));
            cache[index] = out;
            return out;
        }
    }

    cache[index] = 1;
    return 1;
}

int main()
{
    std::vector<std::string> grid;
    std::ifstream in("input.txt");
    std::string line;
    while (getline(in, line)) {
        grid.push_back(line);
    }

    auto start = std::chrono::steady_clock::now();

    pos startpos(0, 0);
    for (int i=0; i<grid[0].size(); i++) {
        if (grid[0][i] == 'S') {
            startpos = pos(0, i);
            break;
        }
    }
    long long out = recursive(grid, startpos);
    std::cout << out << '\n';
}

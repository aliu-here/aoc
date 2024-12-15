#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>


typedef std::vector<int> point;


void try_pos(std::vector<std::string> &map, int x, int y, std::set<std::vector<point>> &out, std::vector<point> so_far, int prev_val=-1)
{
    if (!(0 <= x && x < map.size()) || !(0 <= y && y < map[0].size())) {
        return;
    }
    if (map[x][y]-48 != prev_val + 1) {
        return;
    }
    if (prev_val == 8) {
        so_far.push_back({x, y});
        out.insert(so_far);
        return;
    }
    so_far.push_back({x, y});
    try_pos(map, x-1, y, out, so_far, prev_val + 1);
    try_pos(map, x+1, y, out, so_far, prev_val + 1);
    try_pos(map, x, y-1, out, so_far, prev_val + 1);
    try_pos(map, x, y+1, out, so_far, prev_val + 1);
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    std::vector<std::string> map;
    while (getline(in, line))
        map.push_back(line);
    int p2 = 0;
    for (int i=0; i<map.size(); i++) {
        for (int j=0; j<map[i].size(); j++) {
            if (map[i][j] == '0') {
                std::set<std::vector<point>> temp;
                try_pos(map, i, j, temp, {});
                p2 += temp.size();
            }
        }
    }
    std::cout << "p2: " << p2 << '\n';
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

std::set<std::vector<int>> try_pos(std::vector<std::string> &map, int x, int y, int prev_val=-1)
{
    std::set<std::vector<int>> visited_posns;
    if (!(0 <= x && x < map.size()) || !(0 <= y && y < map[0].size()))
        return {{-1, -1}};
    if (map[x][y]-48 != prev_val + 1)
        return {{-1, -1}};
    if (prev_val == 8)
        return {{x, y}};
    std::set<std::vector<int>> temp;
    temp = try_pos(map, x+1, y, prev_val + 1);
    visited_posns.insert(temp.begin(), temp.end());
    temp = try_pos(map, x-1, y, prev_val + 1);
    visited_posns.insert(temp.begin(), temp.end());
    temp = try_pos(map, x, y+1, prev_val + 1);
    visited_posns.insert(temp.begin(), temp.end());
    temp = try_pos(map, x, y-1, prev_val + 1);
    visited_posns.insert(temp.begin(), temp.end());

    return visited_posns;
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    std::vector<std::string> map;
    while (getline(in, line))
        map.push_back(line);
    int p1 = 0;
    for (int i=0; i<map.size(); i++) {
        for (int j=0; j<map[i].size(); j++) {
            if (map[i][j] == '0')
                p1 += try_pos(map, i, j).size() - 1;
        }
    }
    std::cout << "p1: " << p1 << '\n';
}

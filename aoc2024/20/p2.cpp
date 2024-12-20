#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <map>

//dijkstra's
enum dirs {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

struct node {
    std::array<int, 2> pos;
    long long dist = 2 << 20;
    int dir;
    bool known_best = 0;
};

std::array<int, 2> add_vecs(std::array<int, 2> v1, std::array<int, 2> v2)
{
    return {v1[0] + v2[0], v1[1] + v2[1]};
}

std::array<int, 2> sub_vecs(std::array<int, 2> v1, std::array<int, 2> v2)
{
    return {v1[0] - v2[0], v1[1] - v2[1]};
}

int manhattan_dist(std::array<int, 2> v1, std::array<int, 2> v2)
{
    return std::abs(v1[0] - v2[0]) + std::abs(v1[1] - v2[1]);
}

int bfs_search(std::vector<std::string> grid, int x, int y)
{
    std::map<std::array<int, 2>, node> visited;
    std::queue<node> to_visit;
    node first;
    first.pos = {x, y};
    first.dist = 0;
    to_visit.push(first);

    std::array<std::array<int, 2>, 4> moves;
    moves[0] = {-1, 0};
    moves[1] = {0, 1};
    moves[2] = {1, 0};
    moves[3] = {0, -1};

    while (to_visit.size() > 0) {
        node curr = to_visit.front();
        to_visit.pop();
        for (int i=0; i<4; i++) {
            node neighbor;
            neighbor.pos = add_vecs(curr.pos, moves[i]);
            neighbor.dist = curr.dist + 1;
            if (grid[neighbor.pos[0]][neighbor.pos[1]] != '#' && visited.find(neighbor.pos) == visited.end())
                to_visit.push(neighbor);
        }
        visited[curr.pos] = curr;
    }

    int out = 0;

    for (auto it = visited.begin(); it != visited.end(); it++) {
        node start = it->second;
        for (auto it2 = visited.begin(); it2 != visited.end(); it2++) {
            node dest = it2->second;
            if ((dest.dist - start.dist - manhattan_dist(dest.pos, start.pos)) >= 100 && manhattan_dist(dest.pos, start.pos) <= 20) {
                out++;
            }
        }
    }
    return out;
}

std::vector<std::string> split(const std::string& s, const std::string& delimiter) 
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

int main()
{
    std::string line;
    std::vector<std::string> grid;
    std::ifstream in("input.txt");

    while (getline(in, line))
        grid.push_back(line);

    int start_x = -1, start_y = -1;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[i].size(); j++) {
            if (grid[i][j] == 'S') {
                start_x = i; start_y = j;
                break;
            }
        }
        if (start_x != -1)
            break;
    }

    std::cout << "p2: " << std::endl;
    std::cout << bfs_search(grid, start_x, start_y) << '\n';
}

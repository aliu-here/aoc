#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

//dijkstra's
enum dirs {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct pos_dist_dir {
    std::array<int, 2> pos;
    int dist;
    char dirs;
};

std::array<int, 2> add_vecs(std::array<int, 2> v1, std::array<int, 2> v2)
{
    return {v1[0] + v2[0], v1[1] + v2[1]};
}

void print_grid(std::vector<std::string> grid)
{
    for (std::string line : grid)
        std::cout << line << '\n';
    std::cout << '\n';
}

int dijkstra_search(std::vector<std::string> grid, int x, int y, char start_dir)
{
    pos_dist_dir currnode;
    currnode.pos = {x, y};
    currnode.dirs = start_dir;
    currnode.dist = 0;

    std::vector<pos_dist_dir> unsure_region = {currnode};
    auto cmp = [](pos_dist_dir a, pos_dist_dir b) { return a.dist > b.dist; };
    std::make_heap(unsure_region.begin(), unsure_region.end(), cmp);
    std::vector<pos_dist_dir> known_best;

    std::array<std::array<int, 2>, 4> moves; 
    moves[0] = {-1, 0};
    moves[1] = {1, 0};
    moves[2] = {0, -1};
    moves[3] = {0, 1};

    while (unsure_region.size() > 0) {
        std::pop_heap(unsure_region.begin(), unsure_region.end(), cmp);
        currnode = unsure_region.back();
        unsure_region.pop_back();
        if (grid[currnode.pos[0]][currnode.pos[1]] == 'E')
            return currnode.dist;
        for (int i=0; i<4; i++) {
            pos_dist_dir newpos;
            newpos.pos = add_vecs(currnode.pos, moves[i]);
            bool fail = false;
            for (auto pos : known_best) {
                if (newpos.pos[0] == pos.pos[0] && newpos.pos[1] == pos.pos[1]) {
                    fail = true;
                    break;
                }
            }
            newpos.dirs = i;
            if (grid[newpos.pos[0]][newpos.pos[1]] == '#' || fail) {
 //               std::cout << "failure\n";
                continue;
            }
            if (currnode.dirs == i)
                newpos.dist = currnode.dist + 1;
            else
                newpos.dist = currnode.dist + 1001; // turn and move

            bool insert = true;
            int prev_size = unsure_region.size();
            for (int i = 0; i < prev_size; i++) {
                if ((unsure_region[i].pos[0] == newpos.pos[0] && unsure_region[i].pos[1] == newpos.pos[1])) {
                    insert = false;
                    if (newpos.dist < unsure_region[i].dist) {
                        unsure_region[i].dirs = newpos.dirs;
                        unsure_region[i].dist = newpos.dist;
                        std::make_heap(unsure_region.begin(), unsure_region.end(), cmp);
                        break;
                    } else {
                        break;
                    }
                }
            }
            if (insert) {
                unsure_region.push_back(newpos);
                std::push_heap(unsure_region.begin(), unsure_region.end(), cmp);
            }
        }
        known_best.push_back(currnode);
    }

    
//    print_grid(grid);

    return -1;
}


int main()
{
    std::vector<std::string> grid;
    std::string line;
    std::ifstream in("input.txt");
    while (getline(in, line))
        grid.push_back(line);

    int x = -1, y = -1;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            if (grid[i][j] == 'S') {
                x = i;
                y = j;
                break;
            }
        }
        if (x != -1)
            break;
    }

    std::cout << "p1: " << dijkstra_search(grid, x, y, RIGHT) << '\n';
}

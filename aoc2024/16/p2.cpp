#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

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
    std::vector<node*> prev = {NULL};
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

void dfs_fill(std::vector<std::string> &grid, node* start_node)
{
    grid[start_node->pos[0]][start_node->pos[1]] = 'O';
    for (node* prev : start_node->prev) {
        if (prev != NULL)
            dfs_fill(grid, prev);
    }
}

int dijkstra_search(std::vector<std::string> grid, int x, int y, char start_dir)
{
    std::vector<std::vector<std::array<node, 4>>> all_nodes;
    for (int i=0; i<grid.size(); i++) {
        all_nodes.push_back(std::vector<std::array<node, 4>>(grid[0].size()));
    }
    std::vector<node*> heap;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            if (grid[i][j] != '#') {
                for (int k=0; k<4; k++) {
                    node temp;
                    temp.pos = {i, j};
                    temp.dir = k;
                    all_nodes[i][j][k] = temp;
                    heap.push_back(&all_nodes[i][j][k]);
                }
            }
        }
    }

    all_nodes[x][y][start_dir].dist = 0;

    auto cmp = [](node* a, node* b) { return a->dist > b->dist; };

    std::make_heap(heap.begin(), heap.end(), cmp);

    std::array<std::array<int, 2>, 4> moves = {{-1, 0}};
    moves[1] = {0, 1}; moves[2] = {1, 0}; moves[3] = {0, -1};

    node* curr_node;

    while (heap.size() > 0) {
        std::pop_heap(heap.begin(), heap.end());
        curr_node = heap.back();
        if (grid[curr_node->pos[0]][curr_node->pos[1]] == 'E')
            break;
        heap.pop_back();
        std::array<int, 2> continuing_pos = add_vecs(curr_node->pos, moves[curr_node->dir]);
        if (all_nodes[continuing_pos[0]][continuing_pos[1]][curr_node->dir].dist > curr_node->dist + 1) {
            all_nodes[continuing_pos[0]][continuing_pos[1]][curr_node->dir].prev = {curr_node};
            all_nodes[continuing_pos[0]][continuing_pos[1]][curr_node->dir].dist = curr_node->dist + 1;
        } else if (all_nodes[continuing_pos[0]][continuing_pos[1]][curr_node->dir].dist == curr_node->dist + 1) {
            all_nodes[continuing_pos[0]][continuing_pos[1]][curr_node->dir].prev.push_back(curr_node);
        }

        int left = (curr_node->dir - 1 + 4) % 4;
        if (all_nodes[curr_node->pos[0]][curr_node->pos[1]][left].dist > curr_node->dist + 1000) {
            all_nodes[curr_node->pos[0]][curr_node->pos[1]][left].dist = curr_node->dist + 1000;
            all_nodes[curr_node->pos[0]][curr_node->pos[1]][left].prev = {curr_node};
        } else if (all_nodes[curr_node->pos[0]][curr_node->pos[1]][left].dist == curr_node->dist + 1000) {
            all_nodes[curr_node->pos[0]][curr_node->pos[1]][left].prev.push_back(curr_node);
        }

        int right = (curr_node->dir + 1) % 4;
        if (all_nodes[curr_node->pos[0]][curr_node->pos[1]][right].dist > curr_node->dist + 1000) {
            all_nodes[curr_node->pos[0]][curr_node->pos[1]][right].dist = curr_node->dist + 1000;
            all_nodes[curr_node->pos[0]][curr_node->pos[1]][right].prev = {curr_node};
        } else if (all_nodes[curr_node->pos[0]][curr_node->pos[1]][right].dist == curr_node->dist + 1000) {
            all_nodes[curr_node->pos[0]][curr_node->pos[1]][right].prev.push_back(curr_node);
        }

        std::make_heap(heap.begin(), heap.end(), cmp);
    }

    dfs_fill(grid, curr_node);

    int out = 0;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid.size(); j++) {
            if (grid[i][j] == 'O')
                out++;
        }
    }
    return out;
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

    std::cout << "p2: " << dijkstra_search(grid, x, y, RIGHT) << '\n';
}

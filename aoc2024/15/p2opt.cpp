#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <set>

enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct pos_and_type {
    std::array<int,2> pos;
    char type;
    bool operator<(const pos_and_type other) const
    {
        return (pos[0] < other.pos[0]) || (pos[1] < other.pos[1] && pos[0] == other.pos[0]);
    }
};

std::set<pos_and_type> touching_in_dir_vertical(std::vector<std::string> &grid, int row, int col, int dir, bool &movable) 
{
    std::set<pos_and_type> this_box_posns;
    if (grid[row][col] == '[') {
        pos_and_type temp;
        temp.pos = {row, col};
        temp.type = grid[row][col];
        this_box_posns.insert(temp);
        temp.pos = {row, col + 1};
        temp.type = grid[row][col + 1];
        this_box_posns.insert(temp); // must be to the right
    } else if (grid[row][col] == ']') {
        pos_and_type temp;
        temp.pos = {row, col};
        temp.type = grid[row][col];
        this_box_posns.insert(temp);
        temp.pos = {row, col - 1};
        temp.type = grid[row][col - 1];
        this_box_posns.insert(temp);
    } else { 
        if (grid[row][col] == '#')
            movable = false;
        return {};
    }
    std::set<pos_and_type> temp, total_posns;
    for (auto pos : this_box_posns) {
        if (dir == UP)
            temp = touching_in_dir_vertical(grid, pos.pos[0] - 1, pos.pos[1], dir, movable);
        if (dir == DOWN)
            temp = touching_in_dir_vertical(grid, pos.pos[0] + 1, pos.pos[1], dir, movable);
        total_posns.insert(temp.begin(), temp.end());
    }
    total_posns.insert(this_box_posns.begin(), this_box_posns.end());
    return total_posns;
}

std::set<pos_and_type> touching_in_dir_horizontal(std::vector<std::string> &grid, int row, int col, int dir, bool &movable)
{
    std::vector<pos_and_type> this_box_posns;
    pos_and_type temp;
    if (dir == LEFT) {
        for (int i=col - 1; i >= 0; i--) {
            if (grid[row][i] != '[' && grid[row][i] != ']') {
                if (grid[row][i] == '#')
                    movable = false;
                break;
            }
            temp.pos = {row, i};
            temp.type = grid[row][i];
            this_box_posns.push_back(temp);
        }
    } else if (dir == RIGHT) {
        for (int i=col + 1; i < grid[0].size(); i++) {
            if (grid[row][i] != '[' && grid[row][i] != ']') {
                if (grid[row][i] == '#')
                    movable = false;
                break;
            }
            temp.pos = {row, i};
            temp.type = grid[row][i];
            this_box_posns.push_back(temp);
        }
    }
    return std::set<pos_and_type>(this_box_posns.begin(), this_box_posns.end());
}

void move(std::vector<std::string> &grid, int &row, int &col, int dir) 
{
    bool movable = true;
    int origrow = row, origcol = col;
    std::set<pos_and_type> box_posns;
    if (dir == UP) {
        box_posns = touching_in_dir_vertical(grid, row - 1, col, dir, movable);
    } else if (dir == DOWN) {
        box_posns = touching_in_dir_vertical(grid, row + 1, col, dir, movable);
    } else if (dir == LEFT) {
        box_posns = touching_in_dir_horizontal(grid, row, col, dir, movable);
    } else if (dir == RIGHT) {
        box_posns = touching_in_dir_horizontal(grid, row, col, dir, movable);
    }

    grid[row][col] = '.';

    if (movable) {
        if (dir == UP)
            row--;
        if (dir == DOWN)
            row++;
        if (dir == LEFT)
            col--;
        if (dir == RIGHT)
            col++;
    }

    if (movable && box_posns.size() != 0) {
        for (pos_and_type pos : box_posns) {
            if (dir == LEFT || dir == RIGHT) {
                int diff = (dir == LEFT) ? -1 : 1;
                grid[pos.pos[0]][pos.pos[1]] = '.';
            } else if (dir == UP || dir == DOWN) {
                int diff = (dir == UP) ? -1 : 1;
                grid[pos.pos[0]][pos.pos[1]] = '.';
            }
        }
        for (pos_and_type pos : box_posns) {
//            std::cout << pos.type << '\n';
            if (dir == LEFT || dir == RIGHT) {
                int diff = (dir == LEFT) ? -1 : 1;
                grid[pos.pos[0]][pos.pos[1] + diff] = pos.type;
            } else if (dir == UP || dir == DOWN) {
                int diff = (dir == UP) ? -1 : 1;
                grid[pos.pos[0] + diff][pos.pos[1]] = pos.type;
            }
        }
    }
    grid[row][col] = '@';
}

void print_grid(std::vector<std::string> grid)
{
    for (std::string line : grid)
        std::cout << line << '\n';
    std::cout << '\n';
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;

    std::vector<std::string> grid;
    std::string moves;
    bool reached_moves=false;
    
    while (getline(in, line)) {
        if (line == "") {
            reached_moves = true;
            continue;
        }

        std::string warehouse_line;
        if (!reached_moves) {
            for (char pos : line) {
                if (pos == '#')
                    warehouse_line += "##";
                else if (pos == '.')
                    warehouse_line += "..";
                else if (pos == 'O')
                    warehouse_line += "[]";
                else if (pos == '@')
                    warehouse_line += "@.";
            }
            grid.push_back(warehouse_line);
        } else {
            moves += line;
        }
    }
    int start_rows = -1, start_cols = -1;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            if (grid[i][j] == '@') {
                start_rows = i;
                start_cols = j;
                break;
            }
        }
        if (start_rows != -1)
            break;
    }

    for (char dir : moves) {
//        print_grid(grid);
        if (dir == '<')
            move(grid, start_rows, start_cols, LEFT);
        if (dir == '>')
            move(grid, start_rows, start_cols, RIGHT);
        if (dir == '^')
            move(grid, start_rows, start_cols, UP);
        if (dir == 'v')
            move(grid, start_rows, start_cols, DOWN);
    }
    long long p2 = 0;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            if (grid[i][j] == '[') {
                p2 += 100 * i + j;
            }
        }
    }
    std::cout << "p2: " << p2 << '\n';
}

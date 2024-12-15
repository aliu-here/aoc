#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

void move(std::vector<std::string> &grid, int &row, int &col, int dir) {
    bool movable = false;
    int origrow = row, origcol = col;
    std::array<int, 2> segment_start, segment_end;
    if (dir == UP) {
        segment_start = {row - 1, col};
        for (int i=row - 1; i >= 0; i--) {
            if (grid[i][col] != 'O') {
                if (grid[i][col] == '.') {
                    movable = true;
                    row -= 1;
                }
                segment_end = {i, col};
                break;
            }
        }
    } else if (dir == DOWN) {
        segment_start = {row + 1, col};
        for (int i=row + 1; i < grid.size(); i++) {
            if (grid[i][col] != 'O') {
                if (grid[i][col] == '.')  {
                    movable = true;
                    row += 1;
                }
                segment_end = {i, col};
                break;
            }
        }
    } else if (dir == LEFT) {
        segment_start = {row, col - 1};
        for (int i=col - 1; i >= 0; i--) {
            if (grid[row][i] != 'O') {
                if (grid[row][i] == '.') {
                    movable = true;
                    col -= 1;
                }
                segment_end = {row, i};
                break;
            }
        }
    } else if (dir == RIGHT) {
        segment_start = {row, col + 1};
        for (int i=col + 1; i < grid[0].size(); i++) {
            if (grid[row][i] != 'O') {
                if (grid[row][i] == '.') {
                    movable = true;
                    col += 1;
                }
                segment_end = {row, i};
                break;
            }
        }
    }

    if (movable && ((segment_start[0] != segment_end[0]) || (segment_start[1] != segment_end[1]))) {
        grid[origrow][origcol] = '.';
        grid[segment_start[0]][segment_start[1]] = '@';
        grid[segment_end[0]][segment_end[1]] = 'O';
    } else if (movable) {
        grid[origrow][origcol] = '.';
        grid[segment_end[0]][segment_end[1]] = '@';
    }
}

void print_grid(std::vector<std::string> grid) {
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

        if (!reached_moves)
            grid.push_back(line);
        else
            moves += line;
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
        if (dir == '<')
            move(grid, start_rows, start_cols, LEFT);
        if (dir == '>')
            move(grid, start_rows, start_cols, RIGHT);
        if (dir == '^')
            move(grid, start_rows, start_cols, UP);
        if (dir == 'v')
            move(grid, start_rows, start_cols, DOWN);
    }
    long long p1 = 0;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            if (grid[i][j] == 'O') {
                p1 += 100 * i + j;
            }
        }
    }
    std::cout << "p1: " << p1 << '\n';
}

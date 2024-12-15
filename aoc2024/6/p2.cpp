#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <thread> //cant be bothered to figure out a faster solution
#include <atomic>

enum directions {
    UP,
    RIGHT,
    DOWN,
    LEFT
};


void move(std::vector<std::string> grid, int *x, int *y, int *dir) {
    for (int i=0; i<4; i++) {
        if (*dir == UP)
            (*x)--;
        if (*dir == DOWN)
            (*x)++;
        if (*dir == LEFT)
            (*y)--;
        if (*dir == RIGHT)
            (*y)++;
        if ((*x < 0 || *x >= grid.size()) || (*y < 0 || *y >= grid[*x].size())) {
            throw std::runtime_error("this is stupid");
        }
        if (grid[*x][*y] == '#') {
            if (*dir == UP) //backtrack
                (*x)++;
            if (*dir == DOWN)
                (*x)--;
            if (*dir == LEFT)
                (*y)++;
            if (*dir == RIGHT)
                (*y)--;
            *dir = (*dir + 1) % 4; //stupidish way to do 90 deg rotation
            continue;
        } else {
            break;
        }
    }
}

bool check_if_loop(std::vector<std::string> &grid, int x, int y, int dir)
{
    std::vector<std::vector<int>> prev_visited = {};
    for (int i=0; i<grid.size(); i++) {
        std::vector<int> temp(grid[0].size());
        prev_visited.push_back(temp);
    }
    int count_prev = 0, count_curr = 1, xcopy=x, ycopy = y;
    while (prev_visited[xcopy][ycopy] != count_curr){
        prev_visited[xcopy][ycopy] = count_curr;
        int prevx = xcopy, prevy = ycopy;
        try {
            move(grid, &xcopy, &ycopy, &dir);
        } catch (std::runtime_error){
            return 0;
        }
        if (xcopy == prevx && ycopy == prevy) {
            return 1;
        }
        if (grid[xcopy][ycopy] != 'X') {
            grid[xcopy][ycopy] = 'X';
            count_curr++;
        }
    }
    return 1;
}

void check_row(std::vector<std::string> grid, int x, int y, int row_num, int dir, std::atomic_int &out, std::atomic_int &counter) {
    int calc_val = 0;
    for (int i=0; i<grid[row_num].size(); i++) {
        std::vector<std::string> copy = grid;
        copy[row_num][i] = '#';
        calc_val += check_if_loop(copy, x, y, dir);
        if (row_num == 0) {
            std::cout << "check done\n";
        }
    }

    out.fetch_add(calc_val);
    counter.fetch_add(1);
}

int main()
{
    std::ifstream in("input.txt");
    std::vector<std::string> grid;
    std::string line;
    while (getline(in, line)) {
        grid.push_back(line);
    }

    for (std::string row : grid) {
        std::cout << row.size() << '\n';
    }

    int dir = -1, x, y;
    std::atomic_int p2=0, counter=0;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[i].size(); j++) {
            if (grid[i][j] == '^')
                dir = UP;
            if (grid[i][j] == '<')
                dir = LEFT;
            if (grid[i][j] == 'V')
                dir = DOWN;
            if (grid[i][j] == '>')
                dir = RIGHT;
            if (dir != -1) {
                x = i;
                y = j;
                grid[i][j] = 'X';
                break;
            }
        }
        if (dir != -1)
            break;
    }
 
    for (int i=0; i<grid.size(); i++) {
        std::cout << i << ',' << grid.size() << '\n';
        std::thread temp(check_row, grid, x, y, i, dir, std::ref(p2), std::ref(counter));
        temp.detach();
    }

    while (counter < grid.size()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << counter << '\n';
    }

    std::cout << "p2: " << p2 << '\n';
}

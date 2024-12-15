#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum directions {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

int main()
{
    std::ifstream in("input.txt");
    std::vector<std::string> grid;
    std::string line;
    while (getline(in, line)) {
        grid.push_back(line);
    }

    int p1=1, time_since_last_new=0, dir = -1, x, y;
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
    while (time_since_last_new < p1){
        time_since_last_new++;
        if (dir == UP)
            x--;
        if (dir == DOWN)
            x++;
        if (dir == LEFT)
            y--;
        if (dir == RIGHT)
            y++;
        if (x >= grid.size() || y >= grid[0].size())
            break;
        if (grid[x][y] == '#') {
            if (dir == UP) //oh sh*t go back
                x++;
            if (dir == DOWN)
                x--;
            if (dir == LEFT)
                y++;
            if (dir == RIGHT)
                y--;
            dir = (dir + 1) % 4; //stupidish way to do 90 deg rotation
        }
        if (grid[x][y] != 'X') {
            grid[x][y] = 'X';
            p1++;
            time_since_last_new = 0;
        }
    }
    std::cout << "p1: " << p1 << '\n';
}


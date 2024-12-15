#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

#include <thread> //cant be bothered to figure out a faster solution
#include <atomic>

enum directions {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

bool check_if_loop(std::vector<std::string> &grid, int x, int y, int dir)
{
    std::vector<std::vector<int>> visited_count;
    for (int i=0; i<grid.size(); i++) {
        std::vector<int> temp(grid[0].size());
        visited_count.push_back(temp);
    }
    while (visited_count[x][y] < 5){ // you can visit each square 4x
        if (dir == UP)
            (x)--;
        if (dir == DOWN)
            (x)++;
        if (dir == LEFT)
            (y)--;
        if (dir == RIGHT)
            (y)++;
        if ((x < 0 || x >= grid.size()) || (y < 0 || y >= grid[x].size())) {
            return 0;
        }
        if (grid[x][y] == '#') {
            if (dir == UP) //backtrack
                (x)++;
            if (dir == DOWN)
                (x)--;
            if (dir == LEFT)
                (y)++;
            if (dir == RIGHT)
                (y)--;
            dir = (dir + 1) % 4; //stupidish way to do 90 deg rotation
            continue;
        }
        visited_count[x][y]++;
    }
    return 1;
}

void check_posns(std::vector<std::string> grid, int x, int y, std::vector<std::vector<int>> &posns, int dir, std::atomic_int &out, std::atomic_int &counter) {
    int calc_val = 0;

    for (std::vector<int> pos : posns) {
        grid[pos[0]][pos[1]] = '#'; // this is fine bc it's a copy fed into the function
        calc_val += check_if_loop(grid, x, y, dir);
        grid[pos[0]][pos[1]] = '.';
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

/*    for (std::string row : grid) {
        std::cout << row.size() << '\n';
    }*/

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

    int xcopy = x, ycopy = y, origdir = dir;
    
    std::set<std::vector<int>> posns;
    while (true){ // you can only visit each square twice
        if (dir == UP)
            (x)--;
        if (dir == DOWN)
            (x)++;
        if (dir == LEFT)
            (y)--;
        if (dir == RIGHT)
            (y)++;
        if ((x < 0 || x >= grid.size()) || (y < 0 || y >= grid[x].size())) {
            break;
        }
        if (grid[x][y] == '#') {
            if (dir == UP) //backtrack
                (x)++;
            if (dir == DOWN)
                (x)--;
            if (dir == LEFT)
                (y)++;
            if (dir == RIGHT)
                (y)--;
            dir = (dir + 1) % 4; //stupidish way to do 90 deg rotation
            continue;
        }
        posns.insert({x, y});
    }

    const int thread_count = 16;
    std::vector<std::vector<std::vector<int>>> dist_work(thread_count);

    int i=0;
    for (std::vector<int> pos : posns) {
        dist_work[i%thread_count].push_back(pos);
        i++;
    }
    

    for (int i=0; i<thread_count; i++) {
        std::thread temp(check_posns, grid, xcopy, ycopy, std::ref(dist_work[i]), origdir, std::ref(p2), std::ref(counter));
        temp.detach();
    }

    while (counter < thread_count) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    std::cout << "p2: " << p2 << '\n';
}


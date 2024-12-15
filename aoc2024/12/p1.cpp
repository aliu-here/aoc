#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

typedef std::array<int, 2> pos;

std::array<int, 2> floodfill(std::vector<std::string>& grid, int x, int y, char type)
{
    if (!(0 <= x && x < grid.size()) || !(0 <= y && y < grid[x].size()))
        return {0, 1};
    if (grid[x][y] == type - 64) 
        return {0, 0};
    if (grid[x][y] != type) {
//        std::cout << "x: " << x << ", y: " << y << '\n';
//        std::cout << grid[x][y] << '\n';
        return {0, 1}; //special return for borders
    }
    grid[x][y] = type - 64;
    std::array<int, 2> out = {1, 0}, temp;
    temp = floodfill(grid, x-1, y, type);
    out[0] += temp[0]; out[1] += temp[1];
    temp = floodfill(grid, x+1, y, type);
    out[0] += temp[0]; out[1] += temp[1];
    temp = floodfill(grid, x, y-1, type);
    out[0] += temp[0]; out[1] += temp[1];
    temp = floodfill(grid, x, y+1, type);
    out[0] += temp[0]; out[1] += temp[1];
    return out;
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    std::vector<std::string> grid;
    while (getline(in, line))
        grid.push_back(line);

    long long p1 = 0;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[i].size(); j++) {
            if (grid[i][j] >= 64) {
                std::cout << grid[i][j] << '\n';
                std::array<int, 2> temp = floodfill(grid, i, j, grid[i][j]);
                p1 += temp[0] * temp[1];
                std::cout << "area: " << temp[0] << '\n';
                std::cout << "perimeter: " << temp[1] << '\n';
            }
        }
    }
    std::cout << "p1: " << p1 << '\n';
}

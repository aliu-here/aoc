#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <fstream>

//dijkstra's
enum dirs {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

std::array<int, 2> add_vecs(std::array<int, 2> v1, std::array<int, 2> v2)
{
    return {v1[0] + v2[0], v1[1] + v2[1]};
}

void print_grid(std::vector<std::vector<char>> grid)
{
    for (std::vector<char> line : grid) {
        for (char ch : line)
            std::cout << ch;
        std::cout << '\n';
    }
    std::cout << '\n';
}

void floodfill(std::vector<std::vector<char>> &grid, int x, int y)
{
    if (x < 0 || x >= grid.size() || y < 0 || y >= grid.size())
        return;
    if (grid[x][y] != '.')
        return;
    grid[x][y] = 'O';
    std::vector<std::array<int, 2>> moves = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    for (int i=0; i<4; i++) {
        std::array<int, 2> moved = add_vecs(moves[i], {x, y});
        floodfill(grid, moved[0], moved[1]);
    }
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

std::vector<std::vector<char>> gengrid(std::vector<std::vector<int>> bytes, int upto) {
    std::vector<std::vector<char>> grid;
    for (int i=0; i<71; i++) {
        grid.push_back(std::vector<char>(71, '.'));
    }
    for (int i=0; i<upto; i++) {
        grid[bytes[i][0]][bytes[i][1]] = '#'; 
    }
    return grid;
}

int main()
{
    std::string line;
    std::vector<std::vector<char>> grid;
    for (int i=0; i<71; i++) {
        grid.push_back(std::vector<char>(71, '.'));
    }
    std::ifstream in("input.txt");
    int lines_read = 0;
    std::vector<std::vector<int>> bytes;
    while (getline(in, line)){
        std::vector<std::string> pos = split(line, ",");
        bytes.push_back({std::stoi(pos[0]), std::stoi(pos[1])});
    }


    int left = 0, right = bytes.size(), mid = (left + right) / 2;
    while (std::abs(right - left) > 1) {
        auto grid = gengrid(bytes, mid);
        floodfill(grid, 0, 0);

        print_grid(grid);
        bool unreachable = grid[70][70] != 'O';
//        std::cout << unreachable << '\n';
        if (unreachable)
            right = mid;
        else
            left = mid;
        std::cout << "left: " << left << ", right: " << right << '\n';
        mid = (right + left) / 2;
    }
    std::cout << left << '\n';
    std::cout << "p2: " << bytes[left][0] << ',' << bytes[left][1] << '\n';

}

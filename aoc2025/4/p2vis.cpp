#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <chrono>

std::vector<std::vector<int>> pic;
int framecount = 0;

void draw(std::vector<std::vector<int>> pic) {
    std::ofstream out("render/" + std::to_string(framecount) + ".ppm");
    out.write("P6\n", 3);

    std::string dims = std::to_string(pic.size()) + ' ' + std::to_string(pic[0].size()) + '\n';
    out.write(dims.c_str(), dims.size());

    out.write("255\n", 4);

    for (auto row : pic) {
        for (int pix : row) {
            unsigned char pixel_data[3];
            switch (pix) {
                case 0:
                    pixel_data[0] = 0;
                    pixel_data[1] = 0;
                    pixel_data[2] = 0;
                    break;
                case 1:
                    pixel_data[0] = 255;
                    pixel_data[1] = 255;
                    pixel_data[2] = 255;
                    break;
                default: {
                             pixel_data[0] = 0;
                             pixel_data[1] = 255 - 2*(pix - 2);
                             pixel_data[2] = 0;
                         }
            }
            out.write((char*)pixel_data, 3);
        }
    }

    out.close();

    framecount++;
}

void remove(std::vector<std::string>& lines, std::vector<std::vector<int>>& grid, std::array<int, 2> loc, std::vector<std::vector<int>>& original, int depth = 0) {
    if (lines[loc[0]][loc[1]] == 'X') {
        return;
    }
    if (depth == 0) {
        pic[loc[0]][loc[1]] = 2;
        original[loc[0]][loc[1]] = 0;
        draw(pic);
    }

    lines[loc[0]][loc[1]] = 'X';
    grid[loc[0]][loc[1]] = 0;
    original[loc[0]][loc[1]] = 0;

    std::vector<std::array<int, 2>> to_remove;

    for (int i=std::max(0, loc[0]-1); i<std::min((int)grid.size(), loc[0] + 2); i++) {
        for (int j=std::max(0, loc[1]-1); j<std::min((int)grid[i].size(), loc[1] + 2); j++) {
            if (i == loc[0] && j == loc[1] || grid[i][j] == 0) {
                continue;
            }
            grid[i][j]--;
            if (grid[i][j] <= 4) {
                to_remove.push_back({i, j});
                pic[i][j] = depth + 3;
            }
        }
    }

    draw(pic);
    for (auto pos : to_remove) {
        remove(lines, grid, pos, original, depth + 1);
    }
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    std::vector<std::string> lines;
    while (getline(in, line)) {
        lines.push_back(line);
    }

    auto start = std::chrono::steady_clock::now();

    long long out = 0;


    std::vector<std::vector<int>> original;

    std::vector<std::array<int, 2>> to_check;
    std::vector<std::vector<int>> adj_count;

    for (int i=0; i<lines.size(); i++) {
        adj_count.push_back(std::vector<int>(lines[i].size(), 0));
        original.push_back(std::vector<int>(lines[i].size(), 0));
    }

    for (int i=0; i<lines.size(); i++) {
        for (int j=0; j<lines[i].size(); j++) {
            if (lines[i][j] != '@') {
                continue;
            }
            original[i][j] = 1;

            int count = 0;
            for (int rows=std::max(0, i-1); rows < std::min((int)lines.size(), i+2); rows++) {
                for (int cols = std::max(0, j-1); cols < std::min((int)lines[i].size(), j+2); cols++) {
                    if (lines[rows][cols] == '@') {
                        count++;
                    }
                }
            }

            adj_count[i][j] = count;

            if (count <= 4) {
                to_check.push_back({i, j});
            }
        }
    }


    for (auto pos : to_check) {
        pic = original;
        remove(lines, adj_count, pos, original);
    }

    draw(original);

    for (auto line : lines) {
        for (char ch : line) {
            if (ch == 'X') {
                out++;
            }
        }
    }


    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';

    std::cout << out << '\n';}

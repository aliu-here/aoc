#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>
#include <unordered_set>
#include <array>

struct pos {
    pos(int inrow, int incol) {
        row = inrow;
        col = incol;
    }
    int row, col;
};

int framecount = 0;

int tile_w = 3, tile_h = 6;

std::vector<std::vector<bool>> splitter = {{0, 1, 0},
                                           {0, 1, 0},
                                           {0, 1, 0},
                                           {1, 1, 1},
                                           {1, 1, 1},
                                           {1, 1, 1}};

std::vector<std::vector<bool>> split = {{1, 0, 0},
                                        {1, 0, 0},
                                        {1, 1, 0},
                                        {1, 1, 0},
                                        {1, 1, 1},
                                        {1, 1, 1}};
std::vector<std::vector<bool>> src = {{1, 1, 1},
                                      {1, 1, 1},
                                      {1, 1, 1},
                                      {1, 1, 1},
                                      {1, 1, 1},
                                      {1, 0, 1},
                                      {0, 0, 0}};

void draw(std::vector<std::vector<std::array<unsigned char, 3>>> framebuf) {
    std::ofstream out("render/" + std::to_string(framecount) + ".ppm");
    out.write("P6\n", 3);

    std::string dims = std::to_string(framebuf.size()) + ' ' + std::to_string(framebuf[0].size() * tile_w) + '\n';
    out.write(dims.c_str(), dims.size());

    out.write("255\n", 4);

    for (std::vector<std::array<unsigned char, 3>> row : framebuf) {
        for (int col = 0; col < row.size(); col++) {
            unsigned char pixel_data[3];
            for (int i=0; i<3; i++) {
                pixel_data[i] = row[col][i];
            }
            out.write((char*)pixel_data, 3);
        }
    }
}


std::vector<std::vector<std::array<unsigned char, 3>>> init_framebuf(std::vector<std::string> grid) {
    std::vector<std::vector<std::array<unsigned char, 3>>> framebuf;
    framebuf.resize(grid.size());
    for (auto row : framebuf) {
        row.resize(grid[0].size());
    }

    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            if (grid[i][j] == 'S') {
                int offset_vert = tile_h * i;
                int offset_horiz = tile_w * j;
                for (int tile_x = 0; tile_x < tile_h; tile_x++) {
                    for (int tile_y = 0; tile_y < tile_w; tile_y++) {
                        if (src[tile_x][tile_y]) {
                            framebuf[offset_vert + tile_x][offset_horiz + tile_y] = {128, 128, 128};
                        } else {
                            framebuf[offset_vert + tile_x][offset_horiz + tile_y] = {25, 240, 25};
                        }
                    }
                }
            }
            if (grid[i][j] == '^') {
                int offset_vert = tile_h * i;
                int offset_horiz = tile_w * j;
                for (int tile_x = 0; tile_x < tile_h; tile_x++) {
                    for (int tile_y = 0; tile_y < tile_w; tile_y++) {
                        if (src[tile_x][tile_y]) {
                            framebuf[offset_vert + tile_x][offset_horiz + tile_y] = {200, 200, 25};
                        } else {
                            framebuf[offset_vert + tile_x][offset_horiz + tile_y] = {0, 0, 0};
                        }
                    }
                }
            }
        }
    }

    draw(framebuf);
    return framebuf;

}

std::vector<std::vector<std::array<unsigned char, 3>>> render_step(std::vector<std::string> grid, std::vector<pos> startposns, std::vector<std::vector<std::array<unsigned char, 3>>>& previous_frame) {
    std::vector<std::vector<std::array<unsigned char, 3>>> framebuf;
    {
        return previous_frame;
    }
}

int main()
{
    std::vector<std::string> grid;
    std::ifstream in("input.txt");
    std::string line;
    while (getline(in, line)) {
        grid.push_back(line);
    }

    init_framebuf(grid);
/*
    auto start = std::chrono::steady_clock::now();

    std::vector<pos> beamstarts;
    for (int i=0; i<grid[0].size(); i++) {
        if (grid[0][i] == 'S') {
            beamstarts.push_back(pos(0, i));
            break;
        }
    }

    int out = 0;
    while (beamstarts.size() > 0) {
        std::unordered_set<long long> new_beamstarts;
        for (pos startpos : beamstarts) {
            for (int row = startpos.row; row < grid.size(); row++) {
                if (grid[row][startpos.col] == '|') {
                    break;
                }
                if (grid[row][startpos.col] == '^') {
                    out++;
                    if (startpos.col > 0) {
                        long long tmp = ((long long)(row) << 32) + (long long)(startpos.col - 1);
                        new_beamstarts.insert(tmp);
                    }
                    if (startpos.col < grid.size() - 1) {
                        long long tmp = ((long long)(row) << 32) + (long long)(startpos.col + 1);
                        new_beamstarts.insert(tmp);
                    }
                    break;
                }
                grid[row][startpos.col] = '|';
            }
        }

        beamstarts.clear();

        for (long long val : new_beamstarts) {
            int row = val >> 32;
            int col = (int)val;
            beamstarts.push_back(pos(row, col));
        }
    }


    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';
    std::cout << out << '\n';
    */
}

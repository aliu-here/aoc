#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>
#include <unordered_set>
#include <array>

#include "tiles.hpp"

struct pos {
    pos(int inrow, int incol) {
        row = inrow;
        col = incol;
    }
    int row, col;
};

int framecount = 0;

int tile_w = 3, tile_h = 6;


void draw(std::vector<std::vector<std::array<unsigned char, 3>>> framebuf) {
    std::ofstream out("render/" + std::to_string(framecount) + ".ppm");
    out.write("P6\n", 3);

    std::string dims = std::to_string(framebuf[0].size()) + ' ' + std::to_string(framebuf.size()) + '\n';
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

    framecount++;
}


std::vector<std::vector<std::array<unsigned char, 3>>> init_framebuf(std::vector<std::string> grid) {
    std::vector<std::vector<std::array<unsigned char, 3>>> framebuf;
    framebuf.resize(grid.size() * tile_h);
    for (std::vector<std::array<unsigned char, 3>>& row : framebuf) {
        row.resize(grid[0].size() * tile_w);
    }

    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            if (grid[i][j] == 'S') {
                int offset_vert = tile_h * i;
                int offset_horiz = tile_w * j;
                for (int tile_x = 0; tile_x < tile_h; tile_x++) {
                    for (int tile_y = 0; tile_y < tile_w; tile_y++) {
                        if (src[tile_x][tile_y]) {
                            framebuf[offset_vert + tile_x][offset_horiz + tile_y][0] = 128; 
                            framebuf[offset_vert + tile_x][offset_horiz + tile_y][1] = 128;
                            framebuf[offset_vert + tile_x][offset_horiz + tile_y][2] = 128;
                        } else {
                            framebuf[offset_vert + tile_x][offset_horiz + tile_y][0] = 25; 
                            framebuf[offset_vert + tile_x][offset_horiz + tile_y][1] = 240;
                            framebuf[offset_vert + tile_x][offset_horiz + tile_y][2] = 25;
                        }
                    }
                }
            }
            if (grid[i][j] == '^') {
                int offset_vert = tile_h * i;
                int offset_horiz = tile_w * j;
                for (int tile_x = 0; tile_x < tile_h; tile_x++) {
                    for (int tile_y = 0; tile_y < tile_w; tile_y++) {
                        if (splitter[tile_x][tile_y]) {
                            framebuf[offset_vert + tile_x][offset_horiz + tile_y][0] = 200; 
                            framebuf[offset_vert + tile_x][offset_horiz + tile_y][1] = 200;
                            framebuf[offset_vert + tile_x][offset_horiz + tile_y][2] = 25;
                        }
                    }
                }
            }
        }
    }

    return framebuf;
}

void render(std::vector<std::string>& grid, std::vector<std::vector<int>> metadata) {
    std::vector<std::vector<std::array<unsigned char, 3>>> framebuf = init_framebuf(grid);
    int curr_row = 1;
    for (int vert_level = tile_h; vert_level < grid.size() * tile_h; vert_level++) {
        curr_row = vert_level / tile_h;
        for (int tile_idx = 0; tile_idx < grid[0].size(); tile_idx++) {
            int h_offset = tile_idx * tile_w;
            if (grid[curr_row][tile_idx] == '|') {
                std::vector<std::vector<bool>> pattern;
                if (metadata[curr_row][tile_idx] & 0b100) {
                     pattern = square;
                }
                if (metadata[curr_row][tile_idx] & 0b10) {
                    pattern = split_r;
                }
                if (metadata[curr_row][tile_idx] & 0b01) {
                    pattern = split_l;
                }

                if (metadata[curr_row][tile_idx] & 0b10 && metadata[curr_row][tile_idx] & 0b1) {
                    pattern = split_both;
                }

                for (int i=0; i<tile_w; i++) {
                    if (pattern[vert_level % tile_h][i]) {
                        framebuf[vert_level][h_offset + i][0] = 25;
                        framebuf[vert_level][h_offset + i][1] = 240;
                        framebuf[vert_level][h_offset + i][2] = 25;
                    }
                }
            }
            if (grid[curr_row][tile_idx] == '^' && grid[curr_row-1][tile_idx] == '|') {
                if (vert_level % tile_h == 0) {
                    for (int i=0; i<tile_w; i++) {
                        if (!splitter[vert_level % tile_h][i]) {
                            framebuf[vert_level][h_offset + i][0] = 25;
                            framebuf[vert_level][h_offset + i][1] = 240;
                            framebuf[vert_level][h_offset + i][2] = 25;
                        }
                    }
                }
            }
        }
    }
    draw(framebuf);
}

int main()
{
    std::vector<std::string> grid;
    std::ifstream in("input.txt");
    std::string line;
    while (getline(in, line)) {
        grid.push_back(line);
    }

    auto start = std::chrono::steady_clock::now();

    std::vector<std::vector<int>> metadata;
    metadata.resize(grid.size());
    for (std::vector<int>& row: metadata) {
        row.resize(grid[0].size(), 0);
    }

    std::vector<pos> beamstarts; pos orig_pos(0, 0);
    for (int i=0; i<grid[0].size(); i++) {
        if (grid[0][i] == 'S') {
            orig_pos = pos(0, i);
            beamstarts.push_back(pos(1, i));
            break;
        }
    }


    int out = 0;
    while (beamstarts.size() > 0) {
        std::unordered_set<long long> new_beamstarts;
        for (pos startpos : beamstarts) {
            for (int row = startpos.row; row < grid.size(); row++) {
                if (grid[row][startpos.col] == '|') {
                    metadata[row][startpos.col] = 0b100;
                    break;
                }
                if (grid[row][startpos.col] == '^') {
                    out++;
                    if (startpos.col > 0) {
                        long long tmp = ((long long)(row) << 32) + (long long)(startpos.col - 1);
                        new_beamstarts.insert(tmp);
                        metadata[row][startpos.col - 1] |= 0b10;
                    }
                    if (startpos.col < grid.size() - 1) {
                        long long tmp = ((long long)(row) << 32) + (long long)(startpos.col + 1);
                        new_beamstarts.insert(tmp);
                        metadata[row][startpos.col + 1] |= 0b01;
                    }
                    break;
                }
                grid[row][startpos.col] = '|';
                metadata[row][startpos.col] |= 0b100;
            }
        }

        render(grid, metadata);

        beamstarts.clear();

        for (long long val : new_beamstarts) {
            int row = val >> 32;
            int col = (int)val;
            beamstarts.push_back(pos(row, col));
        }
    }

    for (auto row : metadata){
        for (int val : row) {
            std::cout << val << '\t';
        }
        std::cout << '\n';
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';
    std::cout << out << '\n';
}

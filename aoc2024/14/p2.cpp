#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <set>

//stolen from stackoverflow
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

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    const int cols=101, rows=103;
    std::vector<std::vector<int>> pos_and_vel;

    while (getline(in, line)) {
        std::vector<std::string> temp_split = split(line, " ");
        std::vector<std::string> start_pos = split(temp_split[0].substr(2, temp_split[0].size()), ",");
        std::vector<std::string> displacement = split(temp_split[1].substr(2, temp_split[1].size()), ",");

        pos_and_vel.push_back({std::stoi(start_pos[0]), std::stoi(start_pos[1]), std::stoi(displacement[0]), std::stoi(displacement[1])});
    }
    int iters = 7700;
    std::set<std::string> seen_img;
    while (true) {
        std::vector<std::vector<int>> count_grid;
        for (int i=0; i<rows; i++) {
            count_grid.push_back(std::vector<int>(cols));
        }
        for (std::vector<int> robot_data : pos_and_vel) {
            int final_cols = robot_data[2] * iters + robot_data[0], final_rows = robot_data[3] * iters + robot_data[1];
            while (final_cols < 0)
                final_cols += cols;
            while (final_rows < 0)
                final_rows += rows;
            count_grid[final_rows % rows][final_cols % cols]++;
        }
        std::string image;
        for (int i=0; i<rows; i++) {
            for (int j=0; j<cols; j++) {
                if (count_grid[i][j] != 0)
                    image += 'X';
                else
                    image += ' ';
            }
            image += '\n';
        }
        std::cout << image;
        std::cout << "iteration: " << iters << '\n';
        if (seen_img.find(image) != seen_img.end())
            std::cout << "image seen before";
        seen_img.insert(image);
        iters++;
        getchar();
    }
}

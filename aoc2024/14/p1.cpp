#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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
    std::vector<std::vector<int>> count_grid;
    for (int i=0; i<rows; i++) {
        count_grid.push_back(std::vector<int>(cols));
    }

    while (getline(in, line)) {
        std::vector<std::string> temp_split = split(line, " ");
        std::vector<std::string> start_pos = split(temp_split[0].substr(2, temp_split[0].size()), ",");
        std::vector<std::string> displacement = split(temp_split[1].substr(2, temp_split[1].size()), ",");

        int final_cols = std::stoi(displacement[0]) * 100 + std::stoi(start_pos[0]), final_rows = std::stoi(displacement[1]) * 100 + std::stoi(start_pos[1]);
        while (final_cols < 0)
            final_cols += cols;
        while (final_rows < 0)
            final_rows += rows;
        count_grid[final_rows % rows][final_cols % cols]++;
    }

    long long q1count = 0, q2count = 0;
    for (int i=0; i<rows/2; i++) {
        for (int j=0; j<cols/2; j++) {
            q1count += count_grid[i][j];
            std::cout << count_grid[i][j] << ' ';
        }
        std::cout << "   ";
        for (int j=cols/2 + 1; j < cols; j++) {
            q2count += count_grid[i][j];
            std::cout << count_grid[i][j] << ' ';
        }
        std::cout << '\n';
    }
    
    std::cout << '\n';

    long long q3count = 0, q4count = 0;
    for (int i=rows/2 + 1; i<rows; i++) {
        for (int j=0; j<cols/2; j++) {
            q3count += count_grid[i][j];
            std::cout << count_grid[i][j] << ' ';
        }
        std::cout << "   ";
        for (int j=cols/2 + 1; j < cols; j++) {
            q4count += count_grid[i][j];
            std::cout << count_grid[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "q1count: " << q1count << '\n';
    std::cout << "q2count: " << q2count << '\n';
    std::cout << "q3count: " << q3count << '\n';
    std::cout << "q4count: " << q4count << '\n';

    std::cout << "p1: " << q1count * q2count * q3count * q4count << '\n';
}

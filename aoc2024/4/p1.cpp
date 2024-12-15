#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool check_dir(std::vector<std::string> grid, int i, int j, int istep, int jstep)
{
    std::string seg;

    for (int k=0; k<4; k++) {
        if ((i + k*istep >= 140) || (j + k*jstep >= 140) || \
                (i + k*istep < 0) || (j + k*jstep < 0))
            return 0;
        seg += grid[i+k*istep][j+k*jstep];
    }
    if (seg == "XMAS")
        return 1;
    return 0;
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    std::vector<std::string> grid;
    int p1 = 0;
    while (getline(in, line)) {
        grid.push_back(line);
    }


    for (int i=0; i<140; i++) {
        for (int j=0; j<140; j++) {
            for (int istep=-1; istep<=1; istep++) {
                for (int jstep=-1; jstep<=1; jstep++){
                    p1 += check_dir(grid, i, j, istep, jstep);
                }
            }
        }
    }
    std::cout << "part 1: " << p1 << '\n';
}

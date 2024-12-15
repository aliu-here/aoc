#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool check_dir(std::vector<std::string> grid, int i, int j, int istep, int jstep)
{
    std::string seg;

    for (int k=0; k<3; k++) {
        if ((i + k*istep >= 140) || (j + k*jstep >= 140) || \
                (i + k*istep < 0) || (j + k*jstep < 0))
            return 0;
        seg += grid[i+k*istep][j+k*jstep];
    }
    if (seg == "MAS")
        return 1;
    return 0;
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    std::vector<std::string> grid;
    int p2 = 0;
    while (getline(in, line)) {
        grid.push_back(line);
    }


    for (int i=1; i<139; i++) {
        for (int j=1; j<139; j++) {
            if ((check_dir(grid, i+1, j+1, -1, -1) || check_dir(grid, i-1, j-1, 1, 1)) &&
                (check_dir(grid, i-1, j+1, 1, -1) || check_dir(grid, i+1, j-1, -1, 1)))
                p2++;
        }
    }
    std::cout << "part 2: " << p2 << '\n';
}

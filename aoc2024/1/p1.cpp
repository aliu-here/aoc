#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

int main()
{
    std::vector<int> a, b;

    std::ifstream in("input.txt");

    std::string line;
    std::stringstream linestream;

    for (;getline(in, line);) {
        linestream = std::stringstream(line);
        int temp1, temp2;
        linestream >> temp1 >> temp2;
        a.push_back(temp1);
        b.push_back(temp2);
    }

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    int sum_diff = 0;
    for (int i=0; i<a.size(); i++) {
        sum_diff += std::abs(a[i] - b[i]);
    }
    std::cout << "part 1: " << sum_diff << '\n';
}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

int main()
{
    std::vector<int> a, b(100000); //it's only five digits so we can just allocate 100k

    std::ifstream in("input.txt");

    std::string line;
    std::stringstream linestream;

    for (;getline(in, line);) {
        linestream = std::stringstream(line);
        int temp1, temp2;
        linestream >> temp1 >> temp2;
        a.push_back(temp1);
        b[temp2]++;
    }

    std::sort(a.begin(), a.end());

    int sum_diff = 0;
    for (int i=0; i<a.size(); i++) {
        sum_diff += a[i] * b[a[i]];
    }
    std::cout << "part 2: " << sum_diff << '\n';
}

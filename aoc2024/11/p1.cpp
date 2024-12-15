#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

void print_vec(std::vector<long long> vec) {
    for (long long num : vec)
        std::cout << num << ' ';
    std::cout << '\n';
}

int main()
{
    std::ifstream in("input.txt");
    int val;
    std::vector<long long> stones, newstones;
    while (in >> val)
        stones.push_back(val);
    for (int i=0; i<25; i++) {
        newstones.clear();
        for (long long num : stones) {
            if (num == 0) {
                newstones.push_back(1);
            } else if ((int)std::log10(num) % 2 == 1) { //even digits means odd exp
                int exp = std::ceil(std::log10(num) / 2);
                long long firsthalf = num / std::pow(10, exp), sechalf = num - firsthalf * std::pow(10, exp);
                newstones.push_back(firsthalf);
                newstones.push_back(sechalf);
            } else {
                newstones.push_back(2024 * num);
            }
        }
        stones = newstones;
        print_vec(stones);
    }
    std::cout << "p1: " << stones.size() << '\n';
}

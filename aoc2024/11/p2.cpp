#include <iostream>
#include <fstream>
#include <cmath>
#include <unordered_map>

int main()
{
    std::ifstream in("input.txt");
    int val;
    std::unordered_map<long long, long long> vals, newvals;
    while (in >> val)
        vals[val]++;
    for (int i=0; i<75; i++) {
        newvals.clear();
        for (auto &[num, temp] : vals) {
            if (num == 0) {
                newvals[1] += vals[num];
            } else if ((int)std::log10(num) % 2 == 1) { //even digits means odd exp
                int exp = std::ceil(std::log10(num) / 2);
                long long firsthalf = num / std::pow(10, exp), sechalf = num - firsthalf * std::pow(10, exp);
                newvals[firsthalf] += vals[num];
                newvals[sechalf] += vals[num];
            } else {
                newvals[num * 2024] += vals[num];
            }
        }
        vals = newvals;
    }
    unsigned long long p2 = 0;
    for (auto &[temp, count] : vals) {
        p2 += count;
    }
    std::cout << "p2: " << p2 << '\n';
}

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cmath>

long long simulate(long long num, int iters);

std::unordered_map<long long, std::unordered_map<int, long long>> cache;

long long call_simulate(long long num, int iters)
{
    if (cache.find(num) != cache.end())
        if (cache[num].find(iters) != cache[num].end())
            return cache[num][iters];
    long long temp = simulate(num, iters);
    cache[num][iters] = temp;
    return temp;
}

long long simulate(long long num, int iters)
{
    if (iters == 75)
        return 1;
    if (num == 0) {
        return call_simulate(1, iters + 1);
    } else if ((int)std::log10(num) % 2 == 1) { //even digits means odd exp
        int exp = std::ceil(std::log10(num) / 2);
        long long firsthalf = num / std::pow(10, exp), sechalf = num - firsthalf * std::pow(10, exp);
        return call_simulate(firsthalf, iters + 1) + call_simulate(sechalf, iters + 1);
    } else {
        return call_simulate(num * 2024, iters + 1);
    }
}

int main()
{
    std::ifstream in("input.txt");
    long long p2 = 0;
    long long val;
    while (in >> val)
        p2 += simulate(val, 0);
    std::cout << "p2: " << p2 << '\n';
}

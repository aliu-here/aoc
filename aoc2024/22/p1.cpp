#include <iostream>
#include <fstream>

int main()
{
    std::ifstream in("input.txt");
    long long out = 0;
    long long num = 0;
    while (in >> num) {
        long long curr_sec = num;
        for (int i = 0; i < 2000; i++) {
            curr_sec ^= (curr_sec * 64);
            curr_sec %= 16777216;

            curr_sec ^= (curr_sec / 32);
            curr_sec %= 16777216;

            curr_sec ^= (curr_sec * 2048);
            curr_sec %= 16777216;

        }
        out += curr_sec;
    }
    std::cout << "p1: " << out << '\n';
}

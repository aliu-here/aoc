#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

long long to_long(std::string line, std::vector<bool> in)
{
    std::string concat = "";
    for (int i=0; i<line.size(); i++) {
        if (in[i]) {
            concat += line[i];
        }
    }
    return std::stol(concat);
}

std::vector<bool> solve(std::string line, int depth) {
    if (depth == 0) {
        return std::vector<bool>(line.size(), 0);
    }

    std::vector<bool> included = solve(line, depth - 1);

    long long max = 0;
    std::vector<bool> best = included;
    for (int i=0; i<line.size(); i++) {
        if (included[i]) {
            continue;
        }
        included[i] = true;
        long long tmp = to_long(line, included);
        if (tmp > max) {
            best = included;
            max = tmp;
        }

        included[i] = false;
    }
    return best;
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    std::vector<std::string> lines;
    while (getline(in, line)) {
        lines.push_back(line);
    }

    auto start = std::chrono::steady_clock::now();


    long long out = 0;
    for (std::string line : lines) {
        auto best = solve(line, 12);
        out += to_long(line, best);
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';

    std::cout << out << '\n';}

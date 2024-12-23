#include <iostream>
#include <fstream>
#include <vector>
#include <array>

int main()
{
    std::ifstream in("input.txt");
    long long out = 0;
    long long num = 0;

    std::vector<std::vector<std::vector<std::vector<int>>>> poss_outputs = std::vector<std::vector<std::vector<std::vector<int>>>>(20, std::vector<std::vector<std::vector<int>>>(20, std::vector<std::vector<int>>(20, std::vector<int>(20, 0))));
    while (in >> num) {
        std::vector<std::vector<std::vector<std::vector<bool>>>> seen_here = std::vector<std::vector<std::vector<std::vector<bool>>>>(20, std::vector<std::vector<std::vector<bool>>>(20, std::vector<std::vector<bool>>(20, std::vector<bool>(20, false))));
        std::vector<int> curr_monkey_diffs;
        std::vector<int> curr_costs;
        long long curr_sec = num, prev_sec = curr_sec;
        for (int i = 0; i < 2000; i++) {
            curr_sec ^= (curr_sec * 64);
            curr_sec %= 16777216;

            curr_sec ^= (curr_sec / 32);
            curr_sec %= 16777216;

            curr_sec ^= (curr_sec * 2048);
            curr_sec %= 16777216;

            curr_monkey_diffs.push_back((curr_sec % 10) - (prev_sec % 10));
            curr_costs.push_back(curr_sec % 10);
            prev_sec = curr_sec;
        }
        for (int i=0; i<2000 - 4; i++) {
            std::array<int, 4> check_loc = {curr_monkey_diffs[i] + 10, curr_monkey_diffs[i+1] + 10, curr_monkey_diffs[i+2] + 10, curr_monkey_diffs[i+3] + 10};
            if (!seen_here[check_loc[0]][check_loc[1]][check_loc[2]][check_loc[3]]) {
                poss_outputs[check_loc[0]][check_loc[1]][check_loc[2]][check_loc[3]] += curr_costs[i + 3];
                seen_here[check_loc[0]][check_loc[1]][check_loc[2]][check_loc[3]] = true;
            }
        }
    }

    int best = 0;
    for (int i=0; i<20; i++) {
        for (int j=0; j<20; j++) {
            for (int k=0; k<20; k++) {
                for (int l=0; l<20; l++) {
                    best = std::max(best, poss_outputs[i][j][k][l]);
                }
            }
        }
    }

    std::cout << "p2: " << best << '\n';
}

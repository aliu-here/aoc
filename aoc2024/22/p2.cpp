#include <iostream>
#include <fstream>
#include <vector>
#include <array>

int main()
{
    std::ifstream in("input.txt");
    long long out = 0;
    long long num = 0;
    std::vector<std::vector<int>> diffs;
    std::vector<std::vector<int>> costs;
    while (in >> num) {
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
        diffs.push_back(curr_monkey_diffs);
        costs.push_back(curr_costs);
    }
    //what is this
    std::vector<std::vector<std::vector<std::vector<int>>>> poss_outputs = std::vector<std::vector<std::vector<std::vector<int>>>>(20, std::vector<std::vector<std::vector<int>>>(20, std::vector<std::vector<int>>(20, std::vector<int>(20, -1))));
   
    long long curr_best = 0;
    for (std::vector<int> monkey : diffs) {
        for (int i=0; i<2000 - 4; i++) {
            std::array<int, 4> signal = {monkey[i], monkey[i+1], monkey[i+2], monkey[i+3]};
            std::cout << "i: " << i << '\n';
            std::cout << "signal: " << signal[0] << ',' << signal[1] << ',' << signal[2] << ',' << signal[3] << "\n"; 
            if (poss_outputs[signal[0] + 10][signal[1] + 10][signal[2] + 10][signal[3] + 10] != -1)
                continue;
            long long result_for_signal = 0;
            for (int k=0; k<diffs.size(); k++) {
                for (int j=0; j<2000 - 4; j++) {
                    std::array<int, 4> poss_signal = {diffs[k][j], diffs[k][j+1], diffs[k][j+2], diffs[k][j+3]};
                    if (poss_signal == signal) { 
                        result_for_signal += costs[k][j+3];
                        break;
                    }
                }
            }
            curr_best = std::max(curr_best, result_for_signal);
            poss_outputs[signal[0] + 10][signal[1] + 10][signal[2] + 10][signal[3] + 10] = result_for_signal;
        }
    }

    std::cout << "p2: " << curr_best << '\n';
}

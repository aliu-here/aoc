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
    std::vector<std::vector<std::vector<std::vector<bool>>>> seen_here = std::vector<std::vector<std::vector<std::vector<bool>>>>(20, std::vector<std::vector<std::vector<bool>>>(20, std::vector<std::vector<bool>>(20, std::vector<bool>(20, false))));
    std::vector<int> costs(2000);
    std::vector<int> diffs(2000);
    while (in >> num) {
        long long curr_sec = num, prev_sec = curr_sec;
        for (int i = 0; i < 2000; i++) {
            curr_sec ^= (curr_sec << 6);
            curr_sec %= 16777216;

            curr_sec ^= (curr_sec >> 5);
            curr_sec %= 16777216;

            curr_sec ^= (curr_sec << 11);
            curr_sec %= 16777216;

            diffs[i] = ((curr_sec % 10) - (prev_sec % 10));
            costs[i] = (curr_sec % 10);
            prev_sec = curr_sec;
        }
        for (int i=0; i<20; i++) {
            for (int j=0; j<20; j++) {
                for (int k=0; k<20; k++) {
                    for (int l=0; l<20; l++) {
                        seen_here[i][j][k][l] = false;
                    }
                }
            }
        }
        for (int i=0; i<2000 - 4; i++) {
            std::array<int, 4> check_loc = {diffs[i] + 10, diffs[i+1] + 10, diffs[i+2] + 10, diffs[i+3] + 10};
            if (!seen_here[check_loc[0]][check_loc[1]][check_loc[2]][check_loc[3]]) {
                poss_outputs[check_loc[0]][check_loc[1]][check_loc[2]][check_loc[3]] += costs[i + 3];
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

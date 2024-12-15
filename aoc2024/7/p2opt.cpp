#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#define ull unsigned long long

ull fastlogexp(ull num)
{
    ull val = 10;
    while (num >= val) {
        val *= 10;
    }
    return val;
}

ull deconcat(ull a, ull b)
{
    return (a - b) / fastlogexp(b);
}

bool can_concat(ull a, ull b)
{
    ull temp = a - b;
    ull temp_pow = fastlogexp(b);
    return temp % temp_pow == 0;
}

//dfs it out
bool num_works(ull calibration_val, std::vector<ull> vals)
{
    if (vals.size() == 1)
        return calibration_val == vals[0];
    ull last_ele = vals[vals.size() - 1];
    bool out = false;
    vals.pop_back();
    if (can_concat(calibration_val, last_ele))
        out |= num_works(deconcat(calibration_val, last_ele), vals);
    if (calibration_val % last_ele == 0)
        out |= num_works(calibration_val / last_ele, vals);
    if (calibration_val >= last_ele)
        out |= num_works(calibration_val - last_ele, vals);
    return out;
}


int main()
{
    std::ifstream in("input.txt");
    std::string line;

    ull p2 = 0;
    while (getline(in, line)) {
        std::stringstream linestream(line);
        std::string calibration_val_str;
        linestream >> calibration_val_str;
        calibration_val_str = calibration_val_str.substr(0, calibration_val_str.size()-1);
        ull calibration_val = std::stol(calibration_val_str);

        ull temp;
        std::vector<ull> vals;
        while (linestream >> temp) {
            vals.push_back(temp);
        }
        p2 += num_works(calibration_val, vals) * calibration_val;
    }

    std::cout << "p2: " << p2 << '\n';
}

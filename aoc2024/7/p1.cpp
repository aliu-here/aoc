#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

//dfs it out
bool num_works(long long calibration_val, std::vector<long long> vals)
{
    if (vals[0] > calibration_val)
        return 0;
    if (vals.size() == 1)
        return calibration_val == vals[0];
    bool mul, add;
    std::vector<long long> newvec(vals.begin()+1, vals.end());
    newvec[0] = vals[0]*vals[1];
    mul = num_works(calibration_val, newvec);
    newvec[0] = vals[0]+vals[1];
    add = num_works(calibration_val, newvec);
    return mul | add;
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;

    long long p1 = 0;
    while (getline(in, line)) {
        std::stringstream linestream(line);
        std::string calibration_val_str;
        linestream >> calibration_val_str;
        calibration_val_str = calibration_val_str.substr(0, calibration_val_str.size()-1);
        long long calibration_val = std::stol(calibration_val_str);

        long long temp;
        std::vector<long long> vals;
        while (linestream >> temp) {
            vals.push_back(temp);
        }
        p1 += calibration_val * num_works(calibration_val, vals);
    }
    std::cout << "p1: " << p1 << '\n';
}

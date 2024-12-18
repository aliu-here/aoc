#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

enum instructions {
    ADV,
    BXL,
    BST,
    JNZ,
    BXC,
    OUT,
    BDV,
    CDV
};

std::vector<int> run_machine(std::vector<int> program, long long aval, long long bval, long long cval) {
    long long reg_a = aval, reg_b = bval, reg_c = cval;
    int ip = 0;
    std::vector<int> out;
    while (ip < program.size()) {
//        std::cout << "ip: " << ip << '\n';
//        std::cout << "op: " << program[ip] << '\n';
        int operand = program[ip + 1];
        long long interp_op;
        if (operand >= 0 && operand < 4) {
            interp_op = operand;
        } else {
            if (operand == 4)
                interp_op = reg_a;
            if (operand == 5)
                interp_op = reg_b;
            if (operand == 6)
                interp_op = reg_c;
        }

        if (program[ip] == ADV) {
            std::cout << "reg_a: " << reg_a << '\n';
            reg_a  = reg_a >> interp_op;
        } else if (program[ip] == BXL) {
            reg_b ^= interp_op;
        } else if (program[ip] == BST) {
            reg_b = interp_op % 8;
        } else if (program[ip] == JNZ) {
            if (reg_a) {
                ip = operand;
                continue;
            }
        } else if (program[ip] == BXC) {
            reg_b = reg_b ^ reg_c;
        } else if (program[ip] == OUT) {
            out.push_back(interp_op % 8);
        } else if (program[ip] == BDV) {
            long long denom = std::pow(2, interp_op);
            reg_b = reg_a >> interp_op;
        } else if (program[ip] == CDV) {
            long long denom = std::pow(2, interp_op);
            reg_c = reg_a >> interp_op;
        }
        ip += 2;
    }
    return out;
}

long long dfs_search(std::vector<int> program, int from_back = 0, long long test_num = 0)
{
    if (from_back == program.size())
        return test_num;
    std::vector<long long> poss_quines = {test_num};
    for (long long poss_quine : poss_quines) {
        std::vector<long long> new_poss_quines;
        for (int i=0; i<8; i++) {
            long long test_val = poss_quine * 8 + i;
            std::vector<int> out = run_machine(program, test_val, 0, 0);
            if (out[0] == program[program.size() - 1 - test_num])
                new_poss_quines.push_back(test_val);
        }
        poss_quines = new_poss_quines;
    }

    if (poss_quines.size() == 0)
        return 2UL << 60;
    
    long long min = 2UL << 60;
    for (long long num : poss_quines) {
        min = std::min(dfs_search(program, num, test_num + 1), min);
    }
    
    return min;
}

int main()
{
    std::ifstream in("input.txt");
    std::string throwaway;
    long long a, b, c;
    in >> throwaway >> throwaway >> a;
    in >> throwaway >> throwaway >> b;
    in >> throwaway >> throwaway >> c;
    in >> throwaway >> throwaway;
    std::vector<int> program;
    for (int i=0; i<throwaway.size(); i+=2) {
        program.push_back(throwaway[i] - 48);
    }

   std::cout << dfs_search(program)<< '\n';
}

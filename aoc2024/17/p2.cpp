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

inline int out_char(long long in) {
    long long temp = (in % 8) ^ 2;
    return ((temp) ^ (in >> temp) ^ 1) % 8;
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

    std::vector<int> program_copy = program;

    std::vector<long long> poss_quines = {0};
    std::reverse(program.begin(), program.end());
    for (int idx=0; idx<program.size(); idx++) {
        std::cout << "curr instruction: " << program[idx] << '\n';
        std::vector<long long> new_poss_quines;
        for (long long test : poss_quines) {
            for (int i=0; i<8; i++) {
                long long test_aval = test * 8 + i;
                std::vector<int> output = run_machine(program_copy, test_aval, 0, 0);
                std::cout << "run done\n";
                if (output[0] == program[idx]) {
                    std::cout << test_aval << '\n';
                    new_poss_quines.push_back(test_aval);
                }
            }
        }
        poss_quines = new_poss_quines;
    }

    long long min_quine = 2UL << 60;
    for (long long num : poss_quines)
        min_quine = std::min(min_quine, num);

    std::cout << min_quine << '\n';
}

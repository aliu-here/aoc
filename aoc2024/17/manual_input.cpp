#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

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
            long long denom = std::pow(2, interp_op);
//            std::cout << "denom: " << denom << '\n';
            reg_a /= denom;
        } else if (program[ip] == BXL) {
            reg_b ^= interp_op;
        } else if (program[ip] == BST) {
            reg_b = interp_op % 8;
        } else if (program[ip] == JNZ) {
//            std::cout << "reg_a: " << reg_a << '\n';
            if (reg_a) {
                ip = operand;
                continue;
            }
        } else if (program[ip] == BXC) {
            reg_b = reg_b ^ reg_c;
        } else if (program[ip] == OUT) {
            std::cout << interp_op % 8 << ',';
        } else if (program[ip] == BDV) {
            long long denom = std::pow(2, interp_op);
            reg_b = reg_a / denom;
        } else if (program[ip] == CDV) {
            long long denom = std::pow(2, interp_op);
            reg_c = reg_a / denom;
        }
        ip += 2;
    }
    return out;
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

    while (true) {
        long long in;
        std::cin >> in;
        run_machine(program, in, 0, 0);
    }

    for (int i=0; i<8*8*8*8*8; i++) {
        std::cout << "i: " << i << '\n';
        run_machine(program, i, 0, 0);
        std::cout << '\n';
    }
}

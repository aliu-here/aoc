#include <vector>
#include <queue>
#include <array>

enum opcodes {
    ADD = 1,
    MUL = 2,
    IN = 3,
    OUT = 4,
    JMPT = 5,
    JMPF = 6,
    LT = 7,
    EQ = 8,
    FIN = 99
};

std::array<int, 100> params_per_op;


std::array<int, 4> calc_param_modes(int opcode) {
    int op = opcode % 100;
    int param1mode = (opcode % 1000) / 100;
    int param2mode = (opcode % 10000) / 1000;
    int param3mode = (opcode % 100000) / 10000;
    std::array<int, 4> out = {op, param1mode, param2mode, param3mode};
    return out;
}

void run_program(std::vector<int> &prog, std::queue<int> in, std::queue<int> &out)
{
    std::fill(params_per_op.begin(), params_per_op.end(), -1);
    params_per_op[ADD] = 3;
    params_per_op[MUL] = 3;
    params_per_op[IN] = 1;
    params_per_op[OUT] = 1;
    params_per_op[JMPT] = 2;
    params_per_op[JMPF] = 2;
    params_per_op[LT] = 3;
    params_per_op[EQ] = 3;

    int ip = 0;
    while (true) {
        std::array<int, 4> op_data = calc_param_modes(prog[ip]);
        int op = op_data[0];
        int interpreted_params[3];
        for (int i=0; i<3; i++) {
            if (params_per_op[op] > i) {
                if (op_data[i + 1])
                    interpreted_params[i] = prog[ip + i + 1]; // shift by 1
                else
                    interpreted_params[i] = prog[prog[ip + i + 1]];
            }
        }

        if (op == ADD) {
            prog[prog[ip + 3]] = interpreted_params[0] + interpreted_params[1];
        } else if (op == MUL) {
            prog[prog[ip + 3]] = interpreted_params[0] * interpreted_params[1];
        } else if (op == IN) {
            prog[prog[ip + 1]] = in.front();
            in.pop();
        } else if (op == OUT) {
            out.push(prog[prog[ip + 1]]);
        } else if (op == JMPT || op == JMPF) {
            if (interpreted_params[0] && op == JMPT || !interpreted_params[0] && op == JMPF) {
                ip = interpreted_params[1];
                continue;
            }
        } else if (op == LT || op == EQ) {
            prog[prog[ip + 3]] = (op == LT) ? interpreted_params[0] < interpreted_params[1] :\
                                 interpreted_params[0] == interpreted_params[1];
        } else if (op == FIN)
            break;
        ip += 1 + params_per_op[op];
    }
}

#include <iostream>
#include <fstream>

std::vector<std::string> split(const std::string& s, const std::string& delimiter) 
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}


int main()
{
    std::ifstream in("input.txt");
    std::string line;
    getline(in, line);
    std::vector<int> program;
    for (std::string num : split(line, ",")) {
        program.push_back(std::stoi(num));
    }
    std::queue<int> input;
    input.push(5);
    std::queue<int> output;
    run_program(program, input, output);
    std::cout << "p1: " << output.back() << '\n';
}

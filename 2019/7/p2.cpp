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

int run_program(std::vector<long long> &prog, std::queue<long long> &in, std::queue<long long> &out, int init_ip=0)
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

    int ip = init_ip;
    while (true) {
        std::array<int, 4> op_data = calc_param_modes(prog[ip]);
        int op = op_data[0];
        long long interpreted_params[3];
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
            if (in.size() == 0)
                return ip;
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
            return -1;
        ip += 1 + params_per_op[op];
    }
}

#include <fstream>
#include <iostream>
#include <string>

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
    std::ifstream in_file("input.txt");
    std::string line;
    getline(in_file, line);
    std::vector<long long> program;
    for (std::string num : split(line, ","))
        program.push_back(std::stol(num));

    long long max_signal = 0;
    for (int a=5; a<10; a++) {
        for (int b=5; b<10; b++) {
            if (a == b)
                continue;
            for (int c=5; c<10; c++) {
                if (b == c || a == c)
                    continue;
                for (int d=5; d<10; d++) {
                    if (c == d || b == d || a == d)
                        continue;
                    for (int e=5; e<10; e++) {
                        if (d == e || c == e || b == e || a == e)
                            continue;
                        int break_points[5] = {0, 0, 0, 0, 0};
                        std::queue<long long> prev_outs[5];
                        std::vector<std::vector<long long>> state_dumps = {program, program, program, program, program};
                        prev_outs[0].push(a);
                        prev_outs[0].push(0);
                        prev_outs[1].push(b);
                        prev_outs[2].push(c);
                        prev_outs[3].push(d);
                        prev_outs[4].push(e);
                        bool exit = false;
                        long long last_from_e;
                        while (true) {
                            for (int i=0; i<5; i++) {
                                std::queue<long long> outputs;
                                if (break_points[i] == -1) {
                                    std::cout << "break #: " << i << '\n';
                                    exit = true;
                                    break;
                                }
                                break_points[i] = run_program(state_dumps[i], prev_outs[i], outputs, break_points[i]);

                                std::cout << outputs.back() << '\n';
                                std::cout << outputs.size() << '\n';
                                std::cout << '\n';
                                while (outputs.size() != 0) {
                                    prev_outs[(i + 1) % 5].push(outputs.front());
                                    outputs.pop();
                                }
                                last_from_e = outputs.back();
                            }
                            if (exit)
                                break;
                        }
                        std::cout << a << ',' << b << ',' << c << ',' << d << ',' << e << '\n';
                        std::cout << '\n';
                        max_signal = std::max(max_signal, last_from_e);
                    }
                }
            }
        }
    }
    std::cout << "p2: " << max_signal << '\n';
}

#include <queue>
#include <array>
#include <unordered_map>

enum opcodes {
    ADD = 1,
    MUL = 2,
    IN = 3,
    OUT = 4,
    JMPT = 5,
    JMPF = 6,
    LT = 7,
    EQ = 8,
    ADJREL = 9,
    FIN = 99
};

std::array<int, 100> params_per_op;


std::array<int, 4> calc_param_modes(long long opcode) {
    int op = opcode % 100;
    int param1mode = (opcode % 1000) / 100;
    int param2mode = (opcode % 10000) / 1000;
    int param3mode = (opcode % 100000) / 10000;
    std::array<int, 4> out = {op, param1mode, param2mode, param3mode};
    return out;
}

int run_program(std::unordered_map<long long, long long> &mem, std::queue<long long> &in, std::queue<long long> &out, int init_ip=0)
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
    params_per_op[ADJREL] = 1;

    int ip = init_ip;
    long long base_offset = 0;
    while (true) {
        std::array<int, 4> op_data = calc_param_modes(mem[ip]);
        long long op = op_data[0];
        long long interpreted_params[3];
        long long interpreted_addrs[3];
        for (int i=0; i<3; i++) {
            if (params_per_op[op] > i) {
                if (op_data[i + 1] == 1) {
                    interpreted_params[i] = mem[ip + i + 1]; // shift by 1
                } else if (op_data[i + 1] == 2) {
                    interpreted_params[i] = mem[mem[ip + i + 1] + base_offset];
                    interpreted_addrs[i] = mem[ip + i + 1] + base_offset;
                } else {
                    interpreted_params[i] = mem[mem[ip + i + 1]];
                    interpreted_addrs[i] = mem[ip + i + 1];
                }
            }
        }

        if (op == ADD) {
            mem[interpreted_addrs[2]] = interpreted_params[0] + interpreted_params[1];
        } else if (op == MUL) {
            mem[interpreted_addrs[2]] = interpreted_params[0] * interpreted_params[1];
        } else if (op == IN) {
            if (in.size() == 0)
                return ip;
            mem[interpreted_addrs[0]] = in.front();
            in.pop();
        } else if (op == OUT) {
            out.push(interpreted_params[0]);
        } else if (op == JMPT || op == JMPF) {
            if (interpreted_params[0] && op == JMPT || !interpreted_params[0] && op == JMPF) {
                ip = interpreted_params[1];
                continue;
            }
        } else if (op == LT || op == EQ) {
            mem[interpreted_addrs[2]] = (op == LT) ? interpreted_params[0] < interpreted_params[1] :\
                                 interpreted_params[0] == interpreted_params[1];
        } else if (op == ADJREL) {
            base_offset += interpreted_params[0];
        } else if (op == FIN)
            return -1;
        ip += 1 + params_per_op[op];
    }
}

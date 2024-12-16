#include <vector>

enum opcodes {
    ADD = 1,
    MUL = 2,
    FIN=99
};

void run_program(std::vector<int> &prog)
{
    int ip = 0;
    while (true) {
        if (prog[ip] == ADD) {
            prog[prog[ip + 3]] = prog[prog[ip + 1]] + prog[prog[ip + 2]];
        } else if (prog[ip] == MUL) {
            prog[prog[ip + 3]] = prog[prog[ip + 1]] * prog[prog[ip + 2]];
        } else if (prog[ip] == FIN)
            break;
        ip += 4;
    }
}

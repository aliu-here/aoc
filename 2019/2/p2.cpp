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
    std::ifstream in("input.txt");
    std::string line;

    getline(in, line);
    std::vector<int> program;
    for (std::string val : split(line, ",")) {
        program.push_back(std::stoi(val));
    }
    for (int i=0; i<100; i++) {
        for (int j=0; j<100; j++) {
            std::vector<int> program_copy = program;
            program_copy[1] = i;
            program_copy[2] = j;
            run_program(program_copy);
            if (program_copy[0] == 19690720) {
                std::cout << "p2: " << 100*i + j << '\n';
            }
        }
    }
}

#include <vector>
#include <queue>
#include <array>
#include <unordered_map>


#include <iostream>

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

std::array<long long, 2> run_program(std::unordered_map<long long, long long> &mem, std::queue<long long> &in, std::queue<long long> &out, int init_ip=0, long long init_base_offset=0)
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
    long long base_offset = init_base_offset;
    while (true) {
        std::array<int, 4> op_data = calc_param_modes(mem[ip]);
        long long op = op_data[0];
//        std::cout << "op: " << op << '\n';
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
                return {ip, base_offset};
            mem[interpreted_addrs[0]] = in.front();
            in.pop();
        } else if (op == OUT) {
//            std::cout << interpreted_params[0] << '\n';
//            std::cout << ip << '\n';
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
            return {-1, -1};
        ip += 1 + params_per_op[op];
    }
}

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

void clear( std::queue<int> &q )
{
   std::queue<int> empty;
   std::swap( q, empty );
}

void print_game_grid(std::vector<std::vector<char>> &grid, std::vector<std::array<int, 3>> prog_out)
{
    for (auto pos : prog_out) {
        char write_char = '.';
        if (pos[2] == 1)
            write_char = 'W';
        else if (pos[2] == 2)
            write_char = 'B';
        else if (pos[2] == 3)
            write_char = '-';
        else if (pos[2] == 4)
            write_char = 'O';
        if (pos[0] == -1) {
            std::cout << "score: " << pos[2] << '\n';
            continue;
        }
        grid[pos[1]][pos[0]] = write_char;
    }

    for (auto line : grid) {
        for (char ch : line)
            std::cout << ch;
        std::cout << '\n';
    }
}

int main()
{
    std::ifstream in_file("input.txt");
    std::string line;
    getline(in_file, line);
    std::unordered_map<long long, long long> program;
    int instruction = 0;
    for (std::string num : split(line, ",")) {
        program[instruction] = std::stol(num);
        instruction++;
    }

    program[0] = 2;

    int int_ip = 0, int_base_offset = 0;
    std::queue<long long> in, out;

    std::vector<std::vector<char>> grid;
    for (int i=0; i<30; i++) {
        grid.push_back(std::vector<char>(50, '.'));
    }

    for (int i=1523; i<=1560; i++) {
        program[i] = 3;
    }

    int prev_ball_loc = 0, curr_ball_loc = 0, nums_until_auto = 3;
    bool auto_move = true;
    while (true) {
        std::cout << "\n\n";
//        getchar();
        int num = 0;

        in.push(num);
        std::array<long long, 2> int_vals = run_program(program, in, out, int_ip, int_base_offset);
        int_ip = int_vals[0];
        int_base_offset = int_vals[1];
        std::vector<std::array<int, 3>> output;
        while (out.size() > 0) {
            int x = out.front();
            out.pop();
            int y = out.front();
            out.pop();
            int val = out.front();
            out.pop();
//            std::cout << "x: " << x << ", y: " << y << ", val: " << val << '\n';
            if (val == 4) {
                prev_ball_loc = curr_ball_loc;
                curr_ball_loc = x;
            }
            output.push_back({x, y, val});
        }



        std::cout << '\n';

        print_game_grid(grid, output);
    }

}

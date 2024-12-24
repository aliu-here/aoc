#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

enum bool_op {
    AND,
    XOR,
    OR 
};

struct gate {
    std::string in1, in2, out;
    int op;
};

struct wire {
    std::string name;
    bool value;
};

std::vector<std::string> split(const std::string &s, const std::string& delimiter) 
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    int last_pos = 0;
    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(s.substr (pos_start));
    return res;
}


int main()
{
    std::ifstream in("input.txt");
    std::string line;
    std::vector<gate> unevaluated_gates;
    std::unordered_map<std::string, wire> wire_values;
    bool reached_gates = false;
    while (getline(in, line)) {
        if (line == "") {
            reached_gates = true;
            continue;
        }

        std::vector<std::string> temp = split(line, " ");
        if (!reached_gates) {
            wire temp_wire;
            temp_wire.value = std::stoi(temp[1]);
            temp_wire.name = temp[0].substr(0, temp[0].size() - 1);
            wire_values[temp_wire.name] = temp_wire;
        } else {
            gate temp_gate;
            if (temp[1] == "AND")
                temp_gate.op = AND;
            if (temp[1] == "XOR")
                temp_gate.op = XOR;
            if (temp[1] == "OR")
                temp_gate.op = OR;
            temp_gate.in1 = temp[0];
            temp_gate.in2 = temp[2];
            temp_gate.out = temp[4];
            unevaluated_gates.push_back(temp_gate);
        }
    }
    
    while (unevaluated_gates.size() > 0) {
        for (int i=0; i<unevaluated_gates.size(); i++) {
            if (wire_values.find(unevaluated_gates[i].in1) == wire_values.end())
                continue;
            if (wire_values.find(unevaluated_gates[i].in2) == wire_values.end())
                continue;
            wire temp_wire;
            if (unevaluated_gates[i].op == AND)
                temp_wire.value = wire_values[unevaluated_gates[i].in1].value && wire_values[unevaluated_gates[i].in2].value;
            else if (unevaluated_gates[i].op == XOR)
                temp_wire.value = wire_values[unevaluated_gates[i].in1].value ^ wire_values[unevaluated_gates[i].in2].value;
            else if (unevaluated_gates[i].op == OR)
                temp_wire.value = wire_values[unevaluated_gates[i].in1].value || wire_values[unevaluated_gates[i].in2].value;
            temp_wire.name = unevaluated_gates[i].out;
            wire_values[temp_wire.name] = temp_wire;
            unevaluated_gates.erase(std::next(unevaluated_gates.begin(), i));
            break;
        }
    }

    std::string out_bin;
    std::vector<wire> out_wires;
    for (auto pair : wire_values) {
        if (pair.second.name[0] == 'z')
            out_wires.push_back(pair.second);
    }

    auto cmp = [](wire a, wire b) { return a.name > b.name; };
    std::sort(out_wires.begin(), out_wires.end(), cmp);
    for (wire wire : out_wires)
        out_bin += std::to_string(wire.value);

    std::cout << out_bin << '\n';

    std::cout << "p1: " << std::stol(out_bin, 0, 2) << '\n';
}

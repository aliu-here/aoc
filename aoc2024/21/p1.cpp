#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <fstream>

std::array<int, 2> add_vecs(std::array<int, 2> v1, std::array<int, 2> v2)
{
    return {v1[0] + v2[0], v1[1] + v2[1]};
}

std::array<int, 2> sub_vecs(std::array<int, 2> v1, std::array<int, 2> v2)
{
    return {v1[0] - v2[0], v1[1] - v2[1]};
}

int manhattan_dist(std::array<int, 2> v1, std::array<int, 2> v2)
{
    return std::abs(sub_vecs(v1, v2)[0]) + std::abs(sub_vecs(v1, v2)[1]);
}

std::array<int, 2> scalar_mult(std::array<int, 2> v, int val)
{
    return {v[0] * val, v[1] * val};
}

void print_vec(std::array<int, 2> v)
{
    std::cout << "x: " << v[0] << ", y: " << v[1] << '\n';
}

enum dirs {
    LEFT,
    DOWN,
    RIGHT,
    UP
};

std::vector<std::array<int, 2>> keypad_1_positions = {{1,0}, {0, 1}, {1, 1}, {2, 1}, {0, 2}, {1, 2}, {2, 2}, {0, 3}, {1, 3}, {2, 3}, {2, 0}};
std::vector<std::array<int, 2>> dir_keypad_positions = {{0, 0}, {1, 0}, {2, 0}, {1, 1}, {2, 1}};
std::vector<std::array<int, 2>> moves = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

std::string create_keypad_moves(std::string lower_level_moves) {
    std::string out;
    int curr_pos = 4;
    for (char move : lower_level_moves) {
        int next_pos;
        if (move  == 'v')
            next_pos = DOWN;
        else if (move == '<')
            next_pos = LEFT;
        else if (move == '>')
            next_pos = RIGHT;
        else if (move == '^')
            next_pos = UP;
        else if (move == 'A')
            next_pos = 4;
        std::array<int, 2> to_move = sub_vecs(dir_keypad_positions[next_pos], dir_keypad_positions[curr_pos]);
        int x_diff = to_move[0], y_diff = to_move[1];
        int x_move = -1, y_move = -1;
        if (x_diff != 0)
            x_move = (x_diff < 0) ? LEFT : RIGHT;
        if (y_diff != 0)
            y_move = (y_diff > 0) ? UP : DOWN;       
        

        x_diff = std::abs(x_diff);
        y_diff = std::abs(y_diff);
        bool x_first = (y_move == -1); // if true, then x_first must be true
        if (!x_first) {
            if (x_move != -1 &&
                manhattan_dist(dir_keypad_positions[4], dir_keypad_positions[x_move]) > manhattan_dist(dir_keypad_positions[4], dir_keypad_positions[y_move]) && //next layer down;
                std::find(dir_keypad_positions.begin(), dir_keypad_positions.end(), add_vecs(dir_keypad_positions[curr_pos], scalar_mult(moves[x_move], x_diff))) != dir_keypad_positions.end()) //and also make sure it doesn't go into illegal areas
                x_first = true;
            if (x_move != -1 &&
                std::find(dir_keypad_positions.begin(), dir_keypad_positions.end(), add_vecs(dir_keypad_positions[curr_pos], scalar_mult(moves[y_move], y_diff))) == dir_keypad_positions.end()) //if it doesn't exist
                x_first = true;
        }

        if (x_first) {
            for (int i=0; i<x_diff; i++) {
                if (x_move == LEFT)
                    out += '<';
                if (x_move == RIGHT)
                    out += '>';
            }
            for (int i=0; i<y_diff; i++) {
                if (y_move == UP)
                    out += '^';
                if (y_move == DOWN)
                    out += 'v';
            }
        } else {
            for (int i=0; i<y_diff; i++) {
                if (y_move == UP)
                    out += '^';
                if (y_move == DOWN)
                    out += 'v';
            }
            for (int i=0; i<x_diff; i++) {
                if (x_move == LEFT)
                    out += '<';
                if (x_move == RIGHT)
                    out += '>';
            }
        }
        out += 'A';
        curr_pos = next_pos;
    }
    return out;
}

int solve(std::string to_get)
{
    int curr_kp_1_pos = 10; // A maps to 10 here
    std::string kp_2;
    for (char curr_pos : to_get) {
        int next_kp_1_pos;
        if (curr_pos == 'A')
            next_kp_1_pos = 10;
        else
            next_kp_1_pos = curr_pos - 48;
        std::array<int, 2> to_move = sub_vecs(keypad_1_positions[next_kp_1_pos], keypad_1_positions[curr_kp_1_pos]);
        int x_diff = to_move[0], y_diff = to_move[1];
        int x_move = -1, y_move = -1;
        if (x_diff != 0)
            x_move = (x_diff < 0) ? LEFT : RIGHT;
        if (y_diff != 0)
            y_move = (y_diff > 0) ? UP : DOWN;


        x_diff = std::abs(x_diff);
        y_diff = std::abs(y_diff);

        bool x_first = (y_move == -1); // if true, then x_first must be true
        if (!x_first) {
            if (x_move != -1 && 
                manhattan_dist(dir_keypad_positions[4], dir_keypad_positions[x_move]) > manhattan_dist(dir_keypad_positions[4], dir_keypad_positions[y_move]) && //next layer down;
                std::find(keypad_1_positions.begin(), keypad_1_positions.end(), add_vecs(keypad_1_positions[curr_kp_1_pos], scalar_mult(moves[x_move], x_diff))) != keypad_1_positions.end()) { //and also make sure it doesn't go into illegal areas
                x_first = true;
            } if (x_move != -1 && 
                std::find(keypad_1_positions.begin(), keypad_1_positions.end(), add_vecs(keypad_1_positions[curr_kp_1_pos], scalar_mult(moves[y_move], y_diff))) == keypad_1_positions.end()) { //if it doesn't exist
                x_first = true;
            }
        }


        if (x_first) {
            for (int i=0; i<x_diff; i++) {
                if (x_move == LEFT)
                    kp_2 += '<';
                if (x_move == RIGHT)
                    kp_2 += '>';
            }
            for (int i=0; i<y_diff; i++) {
                if (y_move == UP)
                    kp_2 += '^';
                if (y_move == DOWN)
                    kp_2 += 'v';
            }
        } else {
            for (int i=0; i<y_diff; i++) {
                if (y_move == UP)
                    kp_2 += '^';
                if (y_move == DOWN)
                    kp_2 += 'v';
            }
            for (int i=0; i<x_diff; i++) {
                if (x_move == LEFT)
                    kp_2 += '<';
                if (x_move == RIGHT)
                    kp_2 += '>';
            }
        }
        kp_2 += 'A';
        curr_kp_1_pos = next_kp_1_pos;
    }
    std::string kp_3 = create_keypad_moves(kp_2);
    std::string kp_4 = create_keypad_moves(kp_3);
    return std::stoi(to_get.substr(0, to_get.size() - 1)) * kp_4.size();
}

int main()
{
    long long out = 0;
    std::ifstream in("input.txt");
    std::string line;
    while (getline(in, line))
        out += solve(line);

    std::cout << "p1: " << out << '\n';
}

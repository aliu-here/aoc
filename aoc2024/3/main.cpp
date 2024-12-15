#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//stolen from stackoverflow
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

int calc_operands(std::string in_func) 
{
    int comma_count = 0;
    for (char c : in_func) {
        bool works = false;
        if (c == ',')
            comma_count++;
        for (char allowedchars : "0123456789,") {
            if (c == allowedchars)
                works = true;
        }
        if (!works)
            return 0;
    }
    if (comma_count != 1)
        return 0;
    std::vector<std::string> segments = split(in_func, ",");
    if (segments[0] == "" || segments[1] == "")
        return 0;

    if (segments[0].size() > 3 || segments[1].size() > 3)
        return 0;
    return std::stoi(segments[0]) * std::stoi(segments[1]);
}

int calc_lines(std::string line) 
{
   int out = 0;
   std::vector<std::string> split_by_open_paren = split(line, "(");
   std::vector<std::string> split_by_parens;
   for (std::string segment : split_by_open_paren) {
       std::vector<std::string> temp = split(segment, ")");
       split_by_parens.insert(split_by_parens.end(), temp.begin(), temp.end());
   }

   int index = -1;
   for (int i=0; i<split_by_parens.size() - 1; i++) {

       index += split_by_parens[i].size() + 1;

       //check for do/don't
       if (split_by_parens[i].size() >=  3 &&
           split_by_parens[i].substr(split_by_parens[i].size() - 3, 3) == "mul" &&
           line[index + split_by_parens[i+1].size() + 1] == ')') { //add 1 to compensate for the opening paren
           int mult_val = calc_operands(split_by_parens[i+1]);
           out += mult_val;
       }
    }
   return out;
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    long long p1 = 0, p2 = 0;
    std::string input;
    while (getline(in, line)) {
        input += line;
    }
    std::string cut_lines;
    std::string last_7;
    bool add = true;
    for (int i=0; i<input.size() - 7; i++) { // i have no idea why this works and
                                             // not adding the value if the flag is false doesn't, but oh well
        last_7 = input.substr(i, 7);
        if (last_7.substr(3, 4) == "do()")
            add = true;
        if (last_7 == "don't()")
            add = false;
        if (add)
            cut_lines += input[i];
    }
    if (add)
        cut_lines += last_7.substr(1, 6);
    std::cout << "part 1: " << calc_lines(input) << '\n';
    std::cout << "part 2: " << calc_lines(cut_lines) << '\n';
}

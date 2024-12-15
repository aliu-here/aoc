#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
    int a_xdiff, a_ydiff, b_xdiff, b_ydiff, target_x, target_y;
    std::ifstream in("input.txt");
    std::string line;
    long long p1 = 0;
    while (getline(in, line)) {
        std::vector<std::string> aparts = split(line, " ");
        std::string a_xdiff_str = aparts[2].substr(0, aparts[2].size() - 1);
        a_xdiff = std::stoi(split(a_xdiff_str, "+")[1]);
        a_ydiff = std::stoi(split(aparts[3], "+")[1]);

        getline(in, line);
        std::vector<std::string> bparts = split(line, " ");
        std::string b_xdiff_str = bparts[2].substr(0, bparts[2].size() - 1);
        b_xdiff = std::stoi(split(b_xdiff_str, "+")[1]);
        b_ydiff = std::stoi(split(bparts[3], "+")[1]);
        
        getline(in, line);
        std::vector<std::string> target = split(line, " ");
        std::string target_x_str = target[1].substr(0, target[1].size() - 1);
        target_x = std::stoi(split(target_x_str, "=")[1]);
        target_y = std::stoi(split(target[2], "=")[1]);

        int min_sofar = 1000; //more than 3*100 + 100
        int a=100, b=100;
        for (int i=0; i<100; i++) {
            if ((target_x - a_xdiff * i) % b_xdiff != 0)
                continue;
            if ((target_y - a_ydiff * i) % b_ydiff != 0)
                continue;
            for (int j=0; j<100; j++) {
                if (target_x == a_xdiff * i + b_xdiff * j && \
                    target_y == a_ydiff * i + b_ydiff * j) {
                    min_sofar = std::min(min_sofar, 3*i + j);
                    a = i;
                    b = j;
                }
            }
        }
        if (min_sofar != 1000) {
            std::cout << "soln x: " << a << ", soln y: " << b << '\n';
            p1 += min_sofar;
        }

        getline(in, line); // random newlines
    }
    std::cout << "p1: " << p1 << '\n';
}

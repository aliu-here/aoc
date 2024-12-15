#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

bool list_safe(std::vector<int> list) {
    int prev, curr, diff;
    bool inc;


    prev = list[0];
    curr = list[1];

    diff = std::abs(prev - curr);

    if (curr > prev)
        inc = 1;
    else
        inc = 0;

    if (diff > 3 || diff < 1)
        return false;
       
    for (int i=2; i < list.size(); i++) {
        prev = curr;
        curr = list[i];
        if ( (curr < prev && inc) || (curr > prev && !inc) )
            return false;
        diff = std::abs(prev - curr);
        if (diff > 3 || diff < 1)
            return false;
    }

    return true;
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    std::stringstream linestream;

    int working_count = 0;

    while (getline(in, line)) {
        linestream = std::stringstream(line);
        int space_count = 0;
        for (char c : line) {
            if (c == ' ')
                space_count++;
        }
        std::vector<int> list;
        for (int i=0; i <= space_count; i++) {
            int temp;
            linestream >> temp;
            list.push_back(temp);
        }

        if (list_safe(list)) {
            working_count++;
            continue;
        }

        for (int i=0; i<list.size(); i++) {
            std::vector<int> copy = list;
            copy.erase(copy.begin() + i);
            if (list_safe(copy)) {
                working_count++;
                break;
            }
        }
    }

    std::cout << "part 2: " << working_count << '\n';
}

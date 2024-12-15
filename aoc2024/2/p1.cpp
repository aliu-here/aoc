#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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
        int prev, curr, diff;
        bool inc, works = true;
        linestream >> prev >> curr;

        diff = std::abs(prev - curr);

        if (curr > prev)
            inc = 1;
        else
            inc = 0;

        if (diff > 3 || diff < 1)
            works = false;

        for (int i=0; i <= space_count - 2; i++) {
            prev = curr;
            linestream >> curr;
            if ( (curr < prev && inc) || (curr > prev && !inc) )
                works = false;
            diff = std::abs(prev - curr);
            if (diff > 3 || diff < 1)
                works = false;
        }

        if (works)
            working_count++;
    }

    std::cout << "part 1: " << working_count << '\n';
}

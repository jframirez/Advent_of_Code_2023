#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>

struct input_data {
    std::list<int64_t> input_numbers;
    std::list<long> delta;
};

int64_t recursive_cals(input_data in) {
    // std::cout << "NUMBER STORED: \n";
    int64_t delta_total = 0;

    auto it = in.input_numbers.begin();
    int64_t delta_n_one = *it;
    ++it;
    for (; it != in.input_numbers.end(); ++it) {
        int64_t delta_n_two = *it;
        int64_t delta = ((delta_n_two - delta_n_one) * (-1));
        in.delta.push_back(delta);
        delta_total += delta;
        delta_n_one = *it;
    }

    /* //Debug print as in examples
    for (const auto & number : in.input_numbers) {
        std::cout << number << "   ";
    }
    std::cout << std::endl;
    std::cout << "   ";
    for (const auto & number : in.delta) {
        std::cout << number << "   ";
    }

    // std::cout << "\nDelta total: " << delta_total;
    std::cout << std::endl;
    */

    // delta_total exit base case;
    if (delta_total != 0) {
        input_data output;
        for (const auto & number : in.delta) {
            output.input_numbers.push_back(number);
        }
        int64_t out = recursive_cals(output);
        return (in.delta.back() - out);
    }

    return 0;
}

int main(void) {
    std::cout << "Advent of Code day 9, part 2" << std::endl;

    std::fstream code_sheet;

    std::list<input_data> input;

    code_sheet.open("./input.txt", std::ios::in);

    if (!code_sheet.is_open()) {
        std::cout << "could not find input.txt";
        return -1;
    }

    std::string line;
    while (std::getline(code_sheet, line)) {
        // std::cout << "LINE: " << line << std::endl;
        if (line.empty()) {
        }

        input.push_back({});

        std::string sub;
        std::istringstream line_in(line);

        while (std::getline(line_in, sub, ' ')) {
            std::istringstream iss(sub);

            int64_t number;

            while (iss >> number) {
                // std::cout << "NUMBER INPUT : " << number << std::endl;
                input.back().input_numbers.push_back(number);
            }
        }
    }

    int64_t total_score = 0;

    for (auto & in : input) {
        in.input_numbers.reverse();
        //std::cout << "CALCULATING LINE:" << std::endl;
        int64_t in_output = in.input_numbers.back() - recursive_cals(in);
        //std::cout << "OUTPUT: " << in_output << std::endl;
        total_score += in_output;
    }

    std::cout << "TOTALED SCORE: " << total_score << std::endl;
}
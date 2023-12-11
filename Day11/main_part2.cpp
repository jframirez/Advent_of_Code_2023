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

struct coord {
    int64_t x;
    int64_t y;
};

void reOffset(std::vector<int64_t> & column_offset) {
    int64_t offset_count_column = 0;
    for (auto & offset : column_offset) {
        if (offset == 0) {
            offset = offset_count_column;
            offset_count_column += (1000000 - 1); // Was (2 - 1) in part 1
        } else {                                  //(offset > 0)
            offset = offset_count_column;
        }
    }
}

void print64_tOffset(std::vector<int64_t> & row_offset) {
    for (const auto & offset : row_offset) {
        std::cout << offset << " : ";
    }
    std::cout << std::endl;
}

int main(void) {
    std::cout << "Advent of Code day 11, part 2" << std::endl;

    std::fstream code_sheet;

    std::vector<std::vector<int64_t>> input_grid;
    std::vector<coord> galaxies;

    code_sheet.open("./input.txt", std::ios::in);

    if (!code_sheet.is_open()) {
        std::cout << "could not find input.txt";
        return -1;
    }

    std::string line;

    int64_t row_count = 0;
    int64_t column_count = 0;

    std::vector<int64_t> row_offset;
    std::vector<int64_t> column_offset;
    while (std::getline(code_sheet, line)) {
        row_offset.push_back(0);
        std::cout << line << std::endl;
        input_grid.push_back({});
        const char * c = line.c_str();
        if (column_offset.size() != line.size()) {
            column_offset = std::vector<int64_t>(line.size(), 0);
        }
        while (*c != '\0') {
            input_grid.back().push_back(*c);
            if (*c == '#') {
                column_offset[column_count] += 1;
                row_offset[row_count] += 1;
                galaxies.push_back({ row_count, column_count });
            }
            ++column_count;
            ++c;
        }
        column_count = 0;
        ++row_count;
    }

    // std::cout << "GALAXIES:" << std::endl;
    // int64_t count = 0;
    // for (const auto & galaxie : galaxies) {
    //     std::cout << count << ": " << galaxie.x << ":" << galaxie.y
    //               << std::endl;
    //     ++count;
    // }

    reOffset(column_offset);
    reOffset(row_offset);

    // print64_tOffset(row_offset);
    // print64_tOffset(column_offset);

    int64_t counter_stepover = 0;

    int64_t total_distance = 0;
    // count = 0;
    for (int64_t i = 0; i < galaxies.size(); ++i) {
        for (int64_t j = 0; j < galaxies.size(); ++j) {
            auto g1 = galaxies[i];
            auto g2 = galaxies[j];

            auto distance =
                (abs((g1.x + row_offset[g1.x]) - (g2.x + row_offset[g2.x])) +
                 abs((g1.y + column_offset[g1.y]) -
                     (g2.y + column_offset[g2.y])));
            if (distance == 0) {
                break;
            }

            total_distance += distance;
            // ++count;
        }
    }

    std::cout << "TOTAL DISTANCE: " << total_distance << std::endl;
}
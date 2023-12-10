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

std::map<std::string, int> coord_lut = { { "north", 0 },
                                         { "east", 1 },
                                         { "south", 2 },
                                         { "west", 3 } };

enum direction_names { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };

std::pair<std::pair<int, int>, std::string> walk(
    const std::pair<int, int> & coord,
    std::string input_direction,
    char symbol,
    const std::vector<std::vector<char>> & input_grid) {

    // std::cout << "\tSYMBOL: " << symbol << " DIR: " << input_direction
    //           << std::endl;

    // INVERT DIRECTION TO GET FROM IN CURRENT CHAR
    auto from_direction = (coord_lut[input_direction] + 2) % 4;
    std::string next_direction;

    std::pair<int, int> new_coord = { coord.first, coord.second };

    // std::cout << "W:ROW: " << new_coord.first << " COLUMN: " << new_coord.second
    //           << " CHAR: " << input_grid[new_coord.first][new_coord.second]
    //           << std::endl;

    if (symbol == '|') {
        // std::cout << "\t\t|: " << std::endl;
        // next direction is:
        if (from_direction == SOUTH) {
            next_direction = "north";
            new_coord.first -= 1;

        } else {
            next_direction = "south";
            new_coord.first += 1;
        }
    } else if (symbol == '-') {
        // std::cout << "\t\t-: " << std::endl;
        // next direction is:
        if (from_direction == EAST) {
            // std::cout << "\t\t\t W" << std::endl;
            next_direction = "west";
            new_coord.second -= 1;
        } else {
            // std::cout << "\t\t\t E" << std::endl;
            next_direction = "east";
            new_coord.second += 1;
        }
    } else if (symbol == 'L') {
        // std::cout << "\t\tL: " << std::endl;
        // next direction is:
        if (from_direction == EAST) {
            // std::cout << "\t\t\t N" << std::endl;
            next_direction = "north";
            new_coord.first -= 1; // ROW up
        } else {
            // std::cout << "\t\t\t E" << std::endl;
            next_direction = "east";
            new_coord.second += 1; // COLUMN LEFT
        }
    } else if (symbol == 'J') {
        // std::cout << "\t\tJ: " << std::endl;
        // next direction is:
        if (from_direction == WEST) {
            next_direction = "north";
            new_coord.first -= 1;
        } else {
            next_direction = "west";
            new_coord.second -= 1;
        }
    } else if (symbol == '7') {
        // std::cout << "\t\t7: " << std::endl;
        // next direction is:
        if (from_direction == SOUTH) {
            next_direction = "west";
            new_coord.second -= 1;
        } else {
            next_direction = "south";
            new_coord.first += 1;
        }
    } else if (symbol == 'F') {
        // std::cout << "\t\tF: " << std::endl;
        // next direction is:
        if (from_direction == SOUTH) {
            next_direction = "east";
            new_coord.second += 1;
        } else {
            next_direction = "south";
            new_coord.first += 1;
        }
    } else {
        // SHOULD NOT HAPPEN
        std::cout << "WENT WRONG ON PATH";
        exit(-1);
    }
    // std::cout << "W:ROW: " << new_coord.first << " COLUMN: " << new_coord.second
    //           << " CHAR: " << input_grid[new_coord.first][new_coord.second]
    //           << std::endl;

    return std::pair<std::pair<int, int>, std::string>{ new_coord,
                                                        next_direction };

    /*
    | is a vertical pipe connecting north and south.
    - is a horizontal pipe connecting east and west.
    L is a 90-degree bend connecting north and east.
    J is a 90-degree bend connecting north and west.
    7 is a 90-degree bend connecting south and west.
    F is a 90-degree bend connecting south and east.
    . is ground; there is no pipe in this tile.
    S is the starting position of the animal; there is a pipe on this tile, but
    your sketch doesn't show what shape the pipe has.
    */
}

int main(void) {
    std::cout << "Advent of Code day 10, part 1" << std::endl;

    std::fstream code_sheet;

    std::vector<std::vector<char>> input_grid;

    code_sheet.open("./input.txt", std::ios::in);

    if (!code_sheet.is_open()) {
        std::cout << "could not find input.txt";
        return -1;
    }

    std::string line;

    std::pair<int, int> coord;
    int row_count = 0;
    int column_count = 0;
    while (std::getline(code_sheet, line)) {
        input_grid.push_back({});
        const char * c = line.c_str();
        while (*c != '\0') {
            input_grid.back().push_back(*c);
            if (*c == 'S') {
                coord.first = row_count;
                coord.second = column_count;
            }
            ++column_count;
            ++c;
        }
        column_count = 0;
        ++row_count;
    }

    std::cout << "ROW: " << coord.first << " COLUMN: " << coord.second
              << " CHAR: " << input_grid[coord.first][coord.second]
              << std::endl;

    // PIPE LOGIC?
    // WALK FROM BOTH SIDES
    // GET INPUT PIPE
    // HARD CODED, S is - so walk left and right

    auto left_walk = walk(coord, "west", '-', input_grid);

    auto right_walk = walk(coord, "east", '-', input_grid);

    // std::cout << "L:ROW: " << left_walk.first.first
    //           << " COLUMN: " << left_walk.first.second << " CHAR: "
    //           << input_grid[left_walk.first.first][left_walk.first.second]
    //           << std::endl;

    // std::cout << "R:ROW: " << right_walk.first.first
    //           << " COLUMN: " << right_walk.first.second << " CHAR: "
    //           << input_grid[right_walk.first.first][right_walk.first.second]
    //           << std::endl;

    int64_t walking_count = 1;

    while (input_grid[left_walk.first.first][left_walk.first.second] != 'S') {
        left_walk =
            walk(left_walk.first,
                 left_walk.second,
                 input_grid[left_walk.first.first][left_walk.first.second],
                 input_grid);

        // right_walk =
        //    walk(right_walk.first,
        //        right_walk.second,
        //       input_grid[right_walk.first.first][right_walk.first.second],
        //       input_grid);

        ++walking_count;
    }

    std::cout << "WALKED TO HALF WAY POINT : " << walking_count << " : "
              << (walking_count + 1) / 2 << std::endl;
}
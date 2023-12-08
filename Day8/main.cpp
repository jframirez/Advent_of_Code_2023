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

int main(void) {
    std::cout << "Advent of Code day 8, part 1" << std::endl;

    std::map<std::string, std::pair<std::string, std::string>> network;

    std::fstream code_sheet;

    code_sheet.open("./input.txt", std::ios::in);

    if (!code_sheet.is_open()) {
        std::cout << "could not find input.txt";
        return -1;
    }

    std::string line;

    std::getline(code_sheet, line);

    // First line is RL
    const char * c = line.c_str();

    std::vector<int> instructions;

    while (*c != '\0') {
        if (*c == 'L') {
            instructions.push_back(0);
        }

        if (*c == 'R') {
            instructions.push_back(1);
        }
        ++c;
    }

    std::string sub;
    std::string state;

    std::string first_entry = "";

    int count = 0;

    while (std::getline(code_sheet, line)) {
        if (line.empty()) {

        } else {
            std::string subline = "";
            std::string entry = "";
            std::string pos1 = "";
            std::string pos2 = "";
            const char * sub_char = line.c_str();
            int counter = 0;
            int index_counter = 0;
            while (*sub_char != '\0') {
                if ((*sub_char >= 'A') && (*sub_char <= 'Z')) {
                    subline += *sub_char;
                    ++counter;
                }

                if (counter == 3) {
                    if (index_counter == 0) {
                        // Add new to map
                        entry = subline;
                        if (first_entry == "") {
                            first_entry = entry;
                        }
                        ++index_counter;

                    } else if (index_counter == 1) {
                        pos1 = subline;
                        ++index_counter;

                    } else if (index_counter == 2) {
                        pos2 = subline;
                        std::pair<std::string, std::string> current_pair = {
                            pos1, pos2
                        };
                        network.insert({ entry, current_pair });
                        index_counter = 0;
                    }
                    subline = "";
                    counter = 0;
                }
                ++sub_char;
            }
        }
    }

    int instruction_count = 0;

    first_entry = "AAA";
    auto current_element = network[first_entry];

    bool found = false;
    while (!found) {
        for (int i = 0; i < instructions.size(); ++i) {
            ++instruction_count;
            if (instructions[i] == 0) { // LEFT
                if ((current_element.first.compare("ZZZ") == 0)) {
                    found = true;
                    break;
                }
                current_element = network[current_element.first];
            }

            if (instructions[i] == 1) { // RIGHT
                if ((current_element.second.compare("ZZZ") == 0)) {
                    found = true;
                    break;
                }
                current_element = network[current_element.second];
            }
        }
    }

    std::cout << "INSTRUCTION COUNT: " << instruction_count << std::endl;
}

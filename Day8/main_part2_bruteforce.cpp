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
    std::cout << "Advent of Code day 8" << std::endl;

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

    std::cout << instructions.size() << std::endl;

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
                if (((*sub_char >= '0') && (*sub_char <= '9')) ||
                    ((*sub_char >= 'A') && (*sub_char <= 'Z')) ||
                    ((*sub_char >= 'a') && (*sub_char <= 'z'))) {
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

    for (const auto & graph_entry : network) {
        std::cout << "G: " << graph_entry.first
                  << ": L: " << graph_entry.second.first
                  << " , R: " << graph_entry.second.second << std::endl;
    }

    int instruction_count = 0;

    std::list<std::pair<std::string, std::string>> node_list;

    std::list<std::string> node_starting_points;

    for (const auto & node : network) {
        if (*(node.first.end() - 1) == 'A') {
            node_starting_points.push_back(node.first);
        }
    }

    std::cout << "NODE STARTING POINTS: " << node_starting_points.size()
              << std::endl;

    bool found = false;

    while (!found) {
        for (int i = 0; i < instructions.size(); ++i) {
            if (found) {
                break;
            }

            //   EXIT CONDITION
            int count_z_end_match = 0;
            for (const auto & node_string : node_starting_points) {
                if (*(node_string.end() - 1) == 'Z') {
                    ++count_z_end_match;
                }
            }

            if (count_z_end_match == node_starting_points.size()) {
                std::cout << "FOUND MAZE EXIT AT: " << instruction_count
                          << std::endl;
                found = true;
                break;
            }

            for (auto & node : node_starting_points) {
                auto current_element = network[node];
                //  UPDATE ALL NODES
                if (instructions[i] == 0) { // LEFT
                    node = current_element.first;
                }

                if (instructions[i] == 1) { // RIGHT
                    node = current_element.second;
                }
            }

            ++instruction_count;
        }
        std::cout << instruction_count << std::endl;
    }

    std::cout << "INSTRUCTION COUNT: " << instruction_count << std::endl;
}

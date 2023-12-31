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

int64_t greatest_common_divider(int64_t a, int64_t b) {
    while (b) {
        auto temp_b = b;
        b = a % b;
        a = temp_b;
    }
    return a;
}

int64_t lowest_common_multiple(int64_t a, int64_t b) {
    std::cout << "\t\t\tLCM: " << a << " : " << b << std::endl;
    return (std::abs(a * b) / greatest_common_divider(a, b));
}

struct metaData {
    std::string node_string;
    int64_t first_z = 0;
    int64_t second_z = 0;
};

int main(void) {
    std::cout << "Advent of Code day 8, part 2" << std::endl;

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
                if (((*sub_char >= '0') && (*sub_char <= '9')) ||
                    ((*sub_char >= 'A') && (*sub_char <= 'Z')) ||
                    ((*sub_char >= 'a') && (*sub_char <= 'z'))) {
                    subline += *sub_char;
                    ++counter;
                }

                if (counter == 3) {
                    if (index_counter == 0) {
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

    // for (const auto & graph_entry : network) {
    //     std::cout << "G: " << graph_entry.first
    //               << ": L: " << graph_entry.second.first
    //               << " , R: " << graph_entry.second.second << std::endl;
    // }

    int instruction_count = 0;

    std::list<std::pair<std::string, std::string>> node_list;

    std::list<metaData> node_starting_points;

    for (const auto & node : network) {
        if (*(node.first.end() - 1) == 'A') {
            node_starting_points.push_back({ node.first });
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
            for (auto & node_string : node_starting_points) {
                if ((node_string.first_z > 0) && (node_string.second_z > 0)) {
                    ++count_z_end_match;
                } else if (*(node_string.node_string.end() - 1) == 'Z') {
                    if (node_string.first_z == 0) {
                        node_string.first_z = instruction_count;
                    } else {
                        node_string.second_z = instruction_count;
                    }
                }
            }

            if (count_z_end_match == node_starting_points.size()) {
                std::cout << "FOUND MAZE EXIT AT: " << instruction_count
                          << std::endl;
                found = true;
                break;
            }

            for (auto & node : node_starting_points) {
                auto current_element = network[node.node_string];
                if (instructions[i] == 0) { // LEFT
                    node.node_string = current_element.first;
                }

                if (instructions[i] == 1) { // RIGHT
                    node.node_string = current_element.second;
                }
            }

            ++instruction_count;
        }
        // std::cout << instruction_count << std::endl;
    }

    std::cout << "INSTRUCTION COUNT: " << instruction_count << std::endl;

    for (const auto & node : node_starting_points) {
        std::cout << node.node_string << " : " << node.first_z << " : "
                  << node.second_z << " : " << (node.second_z - node.first_z)
                  << std::endl;
    }

    auto it = node_starting_points.begin();
    ++it;
    auto prev_value = lowest_common_multiple(
        node_starting_points.begin()->first_z, it->first_z);
    std::cout << "\t\t" << prev_value << std::endl;

    for (; it != node_starting_points.end(); ++it) {
        prev_value = lowest_common_multiple(prev_value, it->first_z);
        std::cout << "\t\t" << prev_value << std::endl;
    }

    std::cout << "INSTRUCTION COUNT: " << prev_value << std::endl;
    // All loops are aligned at the start ( loop size == loop start ), so no
    // need to mitigate first alignment
}

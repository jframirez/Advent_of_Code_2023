#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <stdint.h>
#include <algorithm>

struct hand{
    int64_t time;
    int64_t distance;
};

int main(void){
    std::cout << "Advent of Code day 7" << std::endl;

    std::vector<hand> hands;

    std::fstream code_sheet;

    code_sheet.open("./sample.txt", std::ios::in);

    if(!code_sheet.is_open()){
        std::cout << "could not find input.txt";
        return -1;
    }

    std::string line;

    //int input_state = -1;

    std::string sub;

    std::string state;

    int count = 0;

    while(std::getline(code_sheet, line)){
        std::cout << line << std::endl;
    }
}
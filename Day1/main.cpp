#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

int named_numbers_lenght = 9;

std::string named_numbers[] = { "one", 
                                "two",
                                "three",
                                "four",
                                "five",
                                "six",
                                "seven",
                                "eight",
                                "nine"};

int named_numbers_lut[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

bool convert_named_nubers = true; //False = Part 1 , True = Part 2

int main(void){
    std::cout << "Advent of Code day 1" << std::endl;

    std::fstream code_sheet;

    code_sheet.open("./input.txt", std::ios::in);

    if(!code_sheet.is_open()){
        std::cout << "could not find input.txt";
        return -1;
    }

    std::string line;
    int total = 0;
    while(std::getline (code_sheet, line)){
        const char * x = line.c_str();
        char num_1 = 'a';
        char num_2 = 'a';
        while (*x != '\0') {
            if ((*x >= '0') && (*x <= '9')){
                if (num_1 == 'a') {
                    num_1 = *x;
                }else{
                    num_2 = *x;
                }
                //++x;
            }else{
                //Check for named numbers
                if(convert_named_nubers){
                    for(int i = 0; i < named_numbers_lenght; ++i){
                        std::string named_number = named_numbers[i];
                        const char * y = named_number.c_str();
                        int count = 0;
                        bool match = false;
                        const char * copy_x = x;
                        while (*y != '\0'){
                            if (*copy_x == *y) {
                                if(*(y+1) == '\0'){
                                    //Matched
                                    if (num_1 == 'a') {
                                        num_1 = named_numbers_lut[i];
                                    }else{
                                        num_2 = named_numbers_lut[i];
                                    }
                                    //x += count; -> re-search from every character to find overlap -> eighthree = 8 -> 3
                                    match = true;
                                    break;
                                }
                                ++count;
                                ++y;
                                ++copy_x;
                            }else{
                                break;
                            }
                        }
                        if (match == true){
                            break;
                        }
                    }
                }
            }    
            ++x;
        }

        int to_add = 0;
        if (num_1 != 'a') {
        to_add = (num_1-48) * 10 + (num_1-48);
        if (num_2 != 'a') {
            to_add = (num_1-48) * 10 + (num_2-48);
        }
    }
        total += to_add;
    }

    std::cout << "Total: " << total << std::endl;

    return 0;
}
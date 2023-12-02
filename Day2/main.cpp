#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

int available_cubes[3][2] = {{0, 12},
                            {1, 13},
                            {2, 14}};

int available_cubes_2[] = {12, 13, 14};

char cubes_lut[] = {'r', 'g', 'b'};

int main(void){
    std::cout << "Advent of Code day 2" << std::endl;

    std::fstream code_sheet;

    code_sheet.open("./input.txt", std::ios::in);

    if(!code_sheet.is_open()){
        std::cout << "could not find input.txt";
        return -1;
    }

    std::string line;
    int total_game_id = 0;
    while(std::getline (code_sheet, line)){
        //std::cout << line << std::endl;
        const char * x = line.c_str();
        int game_id = 0;
        bool possible = true;
        while (*x != '\0') {
            //Start of line, game id
            while (*x != ':') {
                if ((*x >= '0') && (*x <= '9')){
                    game_id = game_id * 10 + (*x-48);
                }
                ++x;
            }
            std::cout << "GAME ID: " << game_id << " : " << *x << *(x+1) << "|" << std::endl;

            int number_complete = -1;
            int number = 0;
            while (*x != '\0'){
                if ((*x >= '0') && (*x <= '9')){
                    number = number * 10 + (*x-48);
                    number_complete = 0;
                }else if (number_complete == 0){
                    number_complete = 1;
                }

                ++x;

                if (number_complete == 1){
                    std::cout << "FOUND NUMBER: " << number << " : " << *(x) <<  std::endl;
                    if (*(x) == 'r') {
                        std::cout << "RED" << std::endl;
                        if(number > available_cubes_2[0]){
                            std::cout << "TOO BIG" << std::endl;
                            possible = false;
                            break;
                        }
                    }
                    else if (*(x) == 'g'){
                        if(number > available_cubes_2[1]){
                            possible = false;
                            break;
                        }
                    }
                    else if (*(x) == 'b'){
                        if(number > available_cubes_2[2]){
                            possible = false;
                            break;
                        }
                    }

                    //Reset
                    number_complete = -1;
                    number = 0;
                    
                }
            }

            if (!possible){
                break;
            }else{
                std::cout << line << std::endl;
                total_game_id += game_id;
            }
            

        }
    }
    std::cout << total_game_id << std::endl;
}
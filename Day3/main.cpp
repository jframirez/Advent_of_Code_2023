#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

std::string symbols = "!#$%&'()*+,-/:;<=>?@[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

bool char_in_triple(char c0, char c1, char c2){
    //std::cout << "CHECK SYMBOL: " << c0 << c1 << c2 << std::endl;
    int count = 0;
    if(symbols.find(c0) == std::string::npos){
        ++count;
    }

    if(symbols.find(c1) == std::string::npos){
        ++count;
    }

    if(symbols.find(c2) == std::string::npos){
        ++count;
    }

    if(count == 3){
        return false;
    }
    return true;
}

int main(void){
    std::cout << "Advent of Code day 3" << std::endl;

    std::fstream code_sheet;

    code_sheet.open("./input.txt", std::ios::in);

    if(!code_sheet.is_open()){
        std::cout << "could not find input.txt";
        return -1;
    }

    std::string line;
    int total_game_id = 0;

    std::string line_0;
    std::getline(code_sheet, line_0);

    std::string line_1;
    std::getline(code_sheet, line_1);

    std::string line_2;
    while(std::getline (code_sheet, line_2)){
        std::cout << "LINE BLOCK: " << std::endl;

        std::cout << line_0 << "\n" << line_1 << "\n" << line_2 << "\nEND BLOCK" << std::endl;
        
        const char * x = line_1.c_str();
        int number_complete = -1;
        int number = 0;
        int count = 0;
        //Start of number, game id
        bool is_part = false;
        while (*x != '\0')
        {
            if ((*x >= '0') && (*x <= '9')){
                number = number * 10 + (*x-48);
                number_complete += 1;
            }else if (number_complete >= 0){
                //Chekc vertical and reset
                
                
                //std::cout <<"AFTER SYMBOL CHECK" << std::endl;
                bool char_is_symbol = char_in_triple(   line_0.c_str()[count], 
                                                        line_1.c_str()[count], 
                                                        line_2.c_str()[count]);
                
                //++x;
                //++count;
                if(char_is_symbol){
                    is_part = true;
                }
                
                std::cout << "NUMBER: " << number << " : " << is_part << std::endl;
                if(is_part){
                    total_game_id += number;
                }
                
                is_part = false;
                number = 0;
                number_complete = -1;
            }
            
            if(number_complete != -1){
                
                //Check adjcent symbols
                if(number_complete == 0){
                    if(count == 0){
                    //skip before check
                    //std::cout << "SKIP BEFORE" << std::endl;
                    }else{
                        //std::cout <<"BEFORE CHECK" << std::endl;
                        bool char_is_symbol = char_in_triple(   line_0.c_str()[count -1], 
                                                                line_1.c_str()[count -1], 
                                                                line_2.c_str()[count -1]);

                        
                        if(char_is_symbol){
                            is_part = true;
                        }
                    }
                }
                
                if(number_complete >= 0){
                    //std::cout <<"VERTICAL ON SYMBOL CHECK" << std::endl;
                    bool char_is_symbol = char_in_triple(   line_0.c_str()[count], 
                                                            line_1.c_str()[count],
                                                            line_2.c_str()[count]);

                    
                    if(char_is_symbol){
                        is_part = true;
                    }
                }
                
            }
            ++x;
            ++count;
            //Edge case on last symbol
            if(*x == '\0'){
                std::cout << "NUMBER: " << number << " : " << is_part << std::endl;
                if(is_part){
                    total_game_id += number;
                }
            }
        }

        line_0 = line_1;
        line_1 = line_2;
    }

    std::cout << "TOTAL: " << total_game_id << std::endl;
}
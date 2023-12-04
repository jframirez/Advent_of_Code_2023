#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

std::string symbols = "!#$%&'()*+,-/:;<=>?@[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

struct data_point{
    int line;
    int char_count;
    int number;
};

struct data_sublist{
    int line;
    int char_count;
};


std::list<data_point> gear_list;

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

    int line_count = 1;

    while(std::getline (code_sheet, line_2)){
        std::cout << "LINE BLOCK: " << std::endl;

        std::cout << line_0 << "\n" << line_1 << "\n" << line_2 << "\nEND BLOCK" << std::endl;
        
        const char * x = line_1.c_str();
        int number_complete = -1;
        int number = 0;
        int count = 0;
        //Start of number, game id
        bool is_part = false;
        int char_count = 0;
        std::list<data_sublist> per_number_list;
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
                    if(line_0.c_str()[count] == '*'){
                        data_sublist point = {line_count-1, char_count};
                        per_number_list.push_back(point);
                    }
                    if(line_1.c_str()[count] == '*'){
                        data_sublist point = {line_count, char_count};
                        per_number_list.push_back(point);
                    }
                    if(line_2.c_str()[count] == '*'){
                        data_sublist point = {line_count+1, char_count}; //Last line is always empty and should not hit
                        per_number_list.push_back(point);
                    }

                }
                
                std::cout << "NUMBER: " << number << " : " << is_part << std::endl;
                if(is_part){
                    total_game_id += number;
                    for(auto it = per_number_list.begin(); it != per_number_list.end(); ++it){
                        data_point point = {it->char_count, it->line, number};
                        gear_list.push_back(point);
                    }
                    per_number_list.clear();
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
                            if(line_0.c_str()[count - 1] == '*'){
                                data_sublist point = {line_count-1, char_count - 1};
                                per_number_list.push_back(point);
                            }
                            if(line_1.c_str()[count - 1] == '*'){
                                data_sublist point = {line_count, char_count - 1};
                                per_number_list.push_back(point);
                            }
                            if(line_2.c_str()[count - 1] == '*'){
                                data_sublist point = {line_count+1, char_count - 1}; //Last line is always empty and should not hit
                                per_number_list.push_back(point);
                            }
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
                        if(line_0.c_str()[count] == '*'){
                        data_sublist point = {line_count-1, char_count};
                        per_number_list.push_back(point);
                        }
                        if(line_1.c_str()[count] == '*'){
                            data_sublist point = {line_count, char_count};
                            per_number_list.push_back(point);
                        }
                        if(line_2.c_str()[count] == '*'){
                            data_sublist point = {line_count+1, char_count}; //Last line is always empty and should not hit
                            per_number_list.push_back(point);
                        }
                    }
                }
                
            }
            ++x;
            ++count;
            ++char_count;
            //Edge case on last symbol
            if(*x == '\0'){
                std::cout << "NUMBER: " << number << " : " << is_part << std::endl;
                if(is_part){
                    total_game_id += number;
                    for(auto it = per_number_list.begin(); it != per_number_list.end(); ++it){
                        data_point point = {it->char_count, it->line, number};
                        gear_list.push_back(point);
                    }
                }
                per_number_list.clear();
            }
        }

        line_0 = line_1;
        line_1 = line_2;
        ++line_count;
    }

    std::cout << "TOTAL: " << total_game_id << std::endl;
    int total_gear_ratio = 0;
    for(auto it = gear_list.begin(); it != gear_list.end(); ++it){
        //std::cout << it->char_count << " : " << it->line << " : "  << it->number << std::endl;
        auto it_next_iterator = it;
        ++it_next_iterator;
        for(auto it_next = it_next_iterator; it_next != gear_list.end(); ++it_next){
            //std::cout << "\t" << it_next->char_count << " : " << it_next->line << " : "  << it_next->number << std::endl;
            if (it->char_count == it_next->char_count){
                if(it->line == it_next->line){
                    total_gear_ratio += it->number * it_next->number;
                    //std::cout << "VAL_1: " << it->number << std::endl;
                    //std::cout << "VAL_2: " << it_next->number << std::endl;
                    //std::cout << "VAL: " << (it->number * it_next->number) << std::endl;
                }
            }
            
        }
        
    }

    std::cout << "TOTAL GEAR RATIO: " << total_gear_ratio << std::endl;
}
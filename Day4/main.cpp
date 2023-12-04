#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

struct SC{
    int card_number;
    std::list<int> sc_numbers;
    std::list<int> sc_get;
    int card_count = 1;
};

enum class parseState{
    SC_NUMBER,
    SC_GET_NUMBERS,
    SC_GOT_NUMBERS
};

std::list<SC> scratch_cards;

int main(void){
    std::cout << "Advent of Code day 4" << std::endl;

    std::fstream code_sheet;

    code_sheet.open("./input.txt", std::ios::in);

    if(!code_sheet.is_open()){
        std::cout << "could not find input.txt";
        return -1;
    }

    std::string line;
    int total_game_id = 0;

    int line_count = 1;

    while(std::getline (code_sheet, line)){
        std::cout << line << std::endl;
        const char * x = line.c_str();
        int number_complete = -1;
        int number = 0;
        SC current_card;
        parseState state = parseState::SC_NUMBER;
        
        while (*x != '\0'){
            if ((*x >= '0') && (*x <= '9')){
                number = number * 10 + (*x-48);
                number_complete += 1;
            }else if (number_complete >= 0){
                if(state == parseState::SC_NUMBER){ 
                    current_card.card_number = number;
                }else if(state == parseState::SC_GET_NUMBERS){
                    current_card.sc_numbers.push_back(number);
                }else if(state == parseState::SC_GOT_NUMBERS){
                    current_card.sc_get.push_back(number);
                }
                number = 0;
                number_complete = -1;
            }
            if(*x == ':'){
                state = parseState::SC_GET_NUMBERS;
            }

            if(*x == '|'){
                state = parseState::SC_GOT_NUMBERS;
            }

            ++x;

            if ((*x == '\0') && (number_complete >= 0)){
                //std::cout << number << std::endl;
                if(state == parseState::SC_NUMBER){
                    current_card.card_number = number;
                }else if(state == parseState::SC_GET_NUMBERS){
                    current_card.sc_numbers.push_back(number);
                }else if(state == parseState::SC_GOT_NUMBERS){
                    current_card.sc_get.push_back(number);
                }
                number = 0;
                number_complete = -1;
            }
        }
        scratch_cards.push_back(current_card);
    }

    std::cout << "PASRSING SC" << std::endl;
    int total_score = 0;
    for(auto it = scratch_cards.begin(); it != scratch_cards.end(); ++it){
        int card_score = 0;
        for(auto it_numbers_1 = it->sc_numbers.begin(); it_numbers_1 != it->sc_numbers.end(); ++it_numbers_1){
            for (auto it_got_numbers = it->sc_get.begin(); it_got_numbers != it->sc_get.end(); ++it_got_numbers){
                if(*it_numbers_1 == *it_got_numbers){
                    if(card_score == 0){
                        card_score = 1;
                    }else{
                        card_score = card_score * 2;
                    }
                }
            }
        }
        total_score += card_score;
    }

    std::cout << total_score << std::endl;

    std::cout << "PART2" << std::endl;

    int total_score_p2 = 0;
    for(auto it = scratch_cards.begin(); it != scratch_cards.end(); ++it){
        std::cout << it->card_number << std::endl;
        for(int i = 0; i < it->card_count; ++i){
            int card_matches = 0;
            for(auto it_numbers_1 = it->sc_numbers.begin(); it_numbers_1 != it->sc_numbers.end(); ++it_numbers_1){
                for (auto it_got_numbers = it->sc_get.begin(); it_got_numbers != it->sc_get.end(); ++it_got_numbers){
                    if(*it_numbers_1 == *it_got_numbers){
                        ++card_matches;
                    }
                }
            }
            auto it_next = it;
            ++it_next;
            for(int i = 0; i < card_matches; ++i){
                if(it_next == scratch_cards.end()){
                    break;
                }
                it_next->card_count += 1;
                ++it_next;
            }
        }
    }

    std::cout << "PART2 SCORE: " << total_score_p2 << std::endl;

    int total = 0;
    for(auto it = scratch_cards.begin(); it != scratch_cards.end(); ++it){
        std::cout << "\t" << it->card_number << " : " << it->card_count << std::endl;
        total += it->card_count;
    }

    std::cout << total << std::endl;
}
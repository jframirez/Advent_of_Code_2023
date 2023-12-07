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

enum class handType{
    FIVEOFAKIND = 0,
    FOUROFAKIND,
    FULLHOUSE,
    THREEOFAKIND,
    TWOPAIR,
    ONEPAIR,
    HIGHCARD
};

//SORT in order
//2AK33
//233KA -> Char value sort
//iterate and count, add multiple of score

//2 = 0
//3 -> 3 = 2 * 2 = 4
//K = 0
//A = 0

//Total = 4 = one pair

//2233A
// 2 * 2 + 2 * 2 = 8 = two pair

//333A1
// 3 * 3 = 9 = three of a kind

//22233
// 3 * 3 + 2 * 2 = 13 = full house

//23333
// 4 * 4 = 16 = four of a kind

//33333
// 5 * 5 = 25 = five of a kind

//A1234
// 0 = high card

//A + 1
//K + 10
//Q + 100
//J + 1000
//T + 10000
//9 + 100000
//8 + 1000000
//7 + 10000000
//6 + 100000000
//5 + 1000000000
//4 + 10000000000
//3 + 100000000000
//2 + 1000000000000
//1 + 10 000 000 000 000
int64_t max_num_conv = 10000000000000;
//HIGH CARD SCORE ( i == 0 -> score + 10000)
// sorted
// A1234
// A = 

// AA123
//Tailed decrease in importance
//i0 score + A * 10000
//i1 score + A * 1000
//i2 score + A * 100
//i3 score + A * 10
//i4 score + A * 1


struct hand{
    std::string hand_string;
    std::list<char> hand_orderd_char_list;
    int64_t hand_sort_score = 0;
    int64_t bet_size;
    handType type;
};



int main(void){
    std::cout << "Advent of Code day 7" << std::endl;

    std::vector<hand> hands;

    std::fstream code_sheet;

    code_sheet.open("./sample.txt", std::ios::in);
    std::cout << INT64_MAX << "\n" << std::to_string(max_num_conv) << std::endl;

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
        std::istringstream iss(line);
        int hand_line_switch = 0;
        hand my_hand;
        while(std::getline(iss, sub, ' ')){
            std::cout << sub << std::endl;
            if (hand_line_switch == 0){
                //Parse hand cards
                my_hand.hand_string = sub;
                ++hand_line_switch;
            }else{
                try{
                    my_hand.bet_size = stoi(sub);
                }catch(const std::exception & e){
                    std::cout << "PARSE ERROR?" << std::endl;
                    exit(1);
                }
                ++hand_line_switch;
            }
            
        }
        hands.push_back(my_hand);
    }

    for(const auto & current_hand: hands){
        std::cout << "HAND: " << current_hand.hand_string << " : BET SIZE: " << current_hand.bet_size << std::endl;
        const char *c = current_hand.hand_string.c_str();
        while(*c != '\0'){
            std::cout << *c << std::endl;
            ++c;
            if(current_hand.hand_orderd_char_list.empty()){
                
                current_hand.hand_orderd_char_list.push_back(*c);
            }
            for(auto it = current_hand.hand_orderd_char_list.begin(); it != current_hand.hand_orderd_char_list.end(); ++it){

            }
        }
    }
}
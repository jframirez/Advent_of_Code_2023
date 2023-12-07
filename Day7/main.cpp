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

enum class handType {
    FIVEOFAKIND = 0,
    FOUROFAKIND = 1,
    FULLHOUSE = 2,
    THREEOFAKIND = 3,
    TWOPAIR = 4,
    ONEPAIR = 5,
    HIGHCARD = 6,
};

// Sorted hand of lenght 5
handType getHandType(std::list<char> hand_string) {
    std::cout << "\n\n";
    // const char * c = NULL;
    char c = hand_string.front();
    int counter = 1;
    int total = 0;
    for (auto it = hand_string.begin(); it != hand_string.end();) {
        c = *it;
        ++it;
        if (it == hand_string.end()) {
            // final scoring on end.
            if (counter > 1) {
                total += (counter * counter);
            }
            break;
        }

        if (c == *it) {
            counter += 1;
        } else {
            if (counter > 1) {
                total += (counter * counter);
            }
            counter = 1;
        }
        std::cout << c << " : " << *it << " : " << counter << std::endl;
    }

    std::cout << "TOTAL IS : " << total << std::endl;

    // SORT in order
    // 2AK33
    // 233KA -> Char value sort
    // iterate and count, add multiple of score

    // 2 = 0
    // 3 -> 3 = 2 * 2 = 4
    // K = 0
    // A = 0

    // Total = 4 = one pair

    // 2233A
    //  2 * 2 + 2 * 2 = 8 = two pair

    // 333A1
    //  3 * 3 = 9 = three of a kind

    // 22233
    //  3 * 3 + 2 * 2 = 13 = full house

    // 23333
    //  4 * 4 = 16 = four of a kind

    // 33333
    //  5 * 5 = 25 = five of a kind

    // A1234
    //  0 = high card

    switch (total) {
        case 0:
            return handType::HIGHCARD;
        case 4:
            return handType::ONEPAIR;
        case 8:
            return handType::TWOPAIR;
        case 9:
            return handType::THREEOFAKIND;
        case 13:
            return handType::FULLHOUSE;
        case 16:
            return handType::FOUROFAKIND;
        case 25:
            return handType::FIVEOFAKIND;
        default:
            std::cout << "CARD COUNT WRONG !!!!!";
            exit(-1);
            break;
    }
}

// Tailed decrease in importance
// i0 score + A * 100000000
// i1 score + A * 1000000
// i2 score + A * 10000
// i3 score + A * 100
// i4 score + A * 1

struct hand {
    std::string hand_string;
    std::list<char> hand_orderd_char_list;
    int64_t hand_sort_score = 0;
    int64_t bet_size;
    handType type;
};

void insertHandToList(hand current_hand, std::list<hand> & list) {
    if (list.empty()) {
        list.push_back(current_hand);
        return;
    }
    for (auto it = list.begin(); it != list.end();) {
        std::cout << "INSERT TO list: " << current_hand.hand_sort_score << " : "
                  << it->hand_sort_score << std::endl;
        if (current_hand.hand_sort_score > it->hand_sort_score) {
            list.insert(it, current_hand);
            return;
        }

        ++it;

        if (it == list.end()) {
            list.push_back(current_hand);
            return;
        }
    }
}

void calcScoreWithOffsets(int64_t & score_counter,
                          int64_t & total_score,
                          std::list<hand> & list) {

    for (auto it = list.begin(); it != list.end(); ++it) {
        ++score_counter;
        total_score += it->bet_size * score_counter;
        std::cout << "CALC SCORE, score_counter: " << score_counter
                  << " TOTAL SCORE : " << total_score << " : " << it->bet_size
                  << " : " << it->hand_string << std::endl;
    }
}

int main(void) {
    std::cout << "Advent of Code day 7, part 1" << std::endl;

    std::map<char, int> lookup_value = { { 'A', 1 },  { 'K', 2 },  { 'Q', 3 },
                                         { 'J', 4 },  { 'T', 5 },  { '9', 6 },
                                         { '8', 7 },  { '7', 8 },  { '6', 9 },
                                         { '5', 10 }, { '4', 11 }, { '3', 12 },
                                         { '2', 13 }, { '1', 14 } };

    std::list<hand> five_of_a_kind;
    std::list<hand> four_of_a_kind;
    std::list<hand> full_house;
    std::list<hand> three_of_a_kind;
    std::list<hand> two_pair;
    std::list<hand> one_pair;
    std::list<hand> high_card;

    std::vector<hand> hands;

    std::fstream code_sheet;

    code_sheet.open("./input.txt", std::ios::in);

    if (!code_sheet.is_open()) {
        std::cout << "could not find input.txt";
        return -1;
    }

    std::string line;

    // int input_state = -1;

    std::string sub;

    std::string state;

    int count = 0;

    while (std::getline(code_sheet, line)) {
        std::cout << line << std::endl;
        std::istringstream iss(line);
        int hand_line_switch = 0;
        hand my_hand;
        while (std::getline(iss, sub, ' ')) {
            std::cout << sub << std::endl;
            if (hand_line_switch == 0) {
                // Parse hand cards
                my_hand.hand_string = sub;
                ++hand_line_switch;
            } else {
                try {
                    my_hand.bet_size = stoi(sub);
                } catch (const std::exception & e) {
                    std::cout << "PARSE ERROR?" << std::endl;
                    exit(1);
                }
                ++hand_line_switch;
            }
        }
        hands.push_back(my_hand);
    }

    for (auto & current_hand : hands) {
        std::cout << "HAND: " << current_hand.hand_string
                  << " : BET SIZE: " << current_hand.bet_size << std::endl;
        const char * c = current_hand.hand_string.c_str();
        //

        int64_t mul_val = 100000000;
        int count;

        int64_t hand_score = 0;
        while (*c != '\0') {
            std::cout << *c << std::endl;

            // Also calculate high card score;
            hand_score += lookup_value[*c] * mul_val;

            mul_val = mul_val / 100;
            ++count;

            if (current_hand.hand_orderd_char_list.empty()) {
                current_hand.hand_orderd_char_list.push_back(*c);
            } else {
                for (auto it = current_hand.hand_orderd_char_list.begin();
                     it != current_hand.hand_orderd_char_list.end();) {
                    std::cout << "IT : " << *c << " : " << *it << std::endl;
                    if (*c <= *it) {
                        current_hand.hand_orderd_char_list.insert(it, *c);
                        break;
                    }

                    ++it;

                    if (it == current_hand.hand_orderd_char_list.end()) {
                        current_hand.hand_orderd_char_list.push_back(*c);
                        break;
                    }
                }
            }

            current_hand.hand_sort_score = hand_score;
            ++c;
        }
    }

    for (const auto & current_hand : hands) {
        std::cout << "HAND: " << current_hand.hand_string
                  << " : BET SIZE: " << current_hand.bet_size
                  << " : ORDERD LIST: ";
        for (auto it = current_hand.hand_orderd_char_list.begin();
             it != current_hand.hand_orderd_char_list.end();
             ++it) {
            std::cout << *it;
        }

        handType my_hand_type = getHandType(current_hand.hand_orderd_char_list);
        std::cout << " : HIGH_CARD_SCORE : " << current_hand.hand_sort_score
                  << " : HAND TYPE: " << int(my_hand_type) << std::endl;

        switch (my_hand_type) {
            case handType::FIVEOFAKIND:
                std::cout << "INSERT FIVE OF A KIND" << std::endl;
                insertHandToList(current_hand, five_of_a_kind);
                break;
            case handType::FOUROFAKIND:
                std::cout << "INSERT FOUR OF A KIND" << std::endl;
                insertHandToList(current_hand, four_of_a_kind);
                break;
            case handType::FULLHOUSE:
                std::cout << "INSERT FULL HOUSE" << std::endl;
                insertHandToList(current_hand, full_house);
                break;
            case handType::HIGHCARD:
                std::cout << "INSERT HIGHCARD" << std::endl;
                insertHandToList(current_hand, high_card);
                break;
            case handType::ONEPAIR:
                std::cout << "INSERT ONEPAIR" << std::endl;
                insertHandToList(current_hand, one_pair);
                break;
            case handType::THREEOFAKIND:
                std::cout << "INSERT THREE OF A KIND" << std::endl;
                insertHandToList(current_hand, three_of_a_kind);
                break;
            case handType::TWOPAIR:
                std::cout << "INSERT TWO PAIR" << std::endl;
                insertHandToList(current_hand, two_pair);
                break;
            default:
                break;
        }
    }

    int64_t score_counter = 0;
    int64_t total_score = 0;

    for (const auto & my_hand : high_card) {
        std::cout << "HIGH CARDS" << my_hand.hand_string << std::endl;
    }

    calcScoreWithOffsets(score_counter, total_score, high_card);

    std::cout << "TOTAL SCORE : " << total_score
              << " : score_counter: " << score_counter << std::endl;

    calcScoreWithOffsets(score_counter, total_score, one_pair);

    std::cout << "TOTAL SCORE : " << total_score
              << " : score_counter: " << score_counter << std::endl;

    calcScoreWithOffsets(score_counter, total_score, two_pair);

    std::cout << "TOTAL SCORE : " << total_score
              << " : score_counter: " << score_counter << std::endl;

    calcScoreWithOffsets(score_counter, total_score, three_of_a_kind);

    std::cout << "TOTAL SCORE : " << total_score
              << " : score_counter: " << score_counter << std::endl;

    calcScoreWithOffsets(score_counter, total_score, full_house);

    std::cout << "TOTAL SCORE : " << total_score
              << " : score_counter: " << score_counter << std::endl;

    calcScoreWithOffsets(score_counter, total_score, four_of_a_kind);

    std::cout << "TOTAL SCORE : " << total_score
              << " : score_counter: " << score_counter << std::endl;

    calcScoreWithOffsets(score_counter, total_score, five_of_a_kind);

    std::cout << "END TOTAL SCORE : " << total_score
              << " : score_counter: " << score_counter << std::endl;
}
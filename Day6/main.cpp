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

struct race{
    int64_t time;
    int64_t distance;
};


int64_t raceWinCombos(std::vector<race> races){
    int64_t score = 1;
    for (const auto & race: races){
        std::cout << "RACE TIME: " << race.time << " , RACE DISTANCE: " << race.distance << std::endl;
        int wins = 0;

        for (int i = 0; i < race.time; i++){
            if((i * (race.time - i)) > race.distance){
                ++wins;
            }
        }
        std::cout << "\tRACE WINS: " << wins << std::endl;
        score = score * wins;
    }

    return score;
}

 

int main(void){
    std::cout << "Advent of Code day 5" << std::endl;

    std::vector<race> races;

    std::fstream code_sheet;

    code_sheet.open("./input.txt", std::ios::in);

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
        std::istringstream one_line(line);
        while(std::getline(one_line, line, ' ')){
            if(line.empty()){
                continue;
            }

            if(line == "Time:"){
                state = "Time:";
                count = 0;
                continue;
            }

            if(line == "Distance:"){
                state = "Distance:";
                count = 0;
                continue;
            }

            std::cout << line << std::endl;

            if(state == "Time:"){
                std::cout << "ADDING TIMES: " << line << std::endl;
                std::istringstream iss(line);
                
                try{
                    races.push_back({std::stoll(line)});
                }catch(const std::exception & e){
                    std::cout << "PARSE ERROR?" << std::endl;
                    continue;
                }
                ++count;
            }
            
            if( state == "Distance:"){
                std::cout << "ADDING DISTANCE: " << line << std::endl;
                std::istringstream iss(line);
                
                try{
                    races[count].distance = std::stoll(line);
                }catch(const std::exception & e){
                    std::cout << "PARSE ERROR 2?" << std::endl;
                    continue;
                }
                ++count;
            }
        }
    }

    std::cout << "TOTAL SCORE PART 1: \n" << raceWinCombos(races) << std::endl;

    std::string kerned_time;
    std::string kerned_distance;

    std::vector<race> kerned_races;

    for(const auto & race : races){
        kerned_time += std::to_string(race.time);
        kerned_distance += std::to_string(race.distance);
    }

    kerned_races.push_back({std::stoll(kerned_time), std::stoll(kerned_distance)});

    std::cout << "TOTAL SCORE PART 2: \n" << raceWinCombos(kerned_races) << std::endl;

}
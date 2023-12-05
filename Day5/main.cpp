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

struct OffsetPair{
    int64_t start;
    int64_t end;
    int64_t offset; //Negative offset?
};

int64_t ConvertWithMap(std::vector<OffsetPair> & offsets, int64_t seed_number){

    //std::cout << "\t\tIN: " << seed_number << std::endl;
    

    for(const auto & offset: offsets){
        if((seed_number >= offset.start) && (seed_number <= offset.end)){
            //std::cout << "\t\t\tOFFSET: " << offset.offset << std::endl;
            //std::cout << "\t\t\t\tOUT: " << seed_number + (offset.offset) << std::endl;
            return (seed_number + (offset.offset));
        }
    }
    //std::cout << "\t\tOUT: " << seed_number << std::endl;
    return seed_number;
}

int64_t convertToLocationFromSeed(int64_t seed, std::map<std::string, std::vector<OffsetPair>> & mappings){
//Check per seed
        //std::cout << "CONVERTING SEED: " << seed << std::endl;
        
        int64_t soil_number = ConvertWithMap(mappings["seed-to-soil"], seed);
        //std::cout << "\tSOIL NUMBER : " << soil_number << std::endl;

        int64_t fert_number = ConvertWithMap(mappings["soil-to-fertilizer"], soil_number);
        //std::cout << "\tFERTILIZER NUMBER : " << fert_number << std::endl;

        int64_t water_number = ConvertWithMap(mappings["fertilizer-to-water"], fert_number);
        //std::cout << "\tWATER NUMBER : " << water_number << std::endl;

        int64_t light_number = ConvertWithMap(mappings["water-to-light"], water_number);
        //std::cout << "\tLIGHT NUMBER : " << light_number << std::endl;

        int64_t temp_number = ConvertWithMap(mappings["light-to-temperature"], light_number);
        //std::cout << "\tTEMP NUMBER : " << temp_number << std::endl;

        int64_t hum_number = ConvertWithMap(mappings["temperature-to-humidity"], temp_number);
        //std::cout << "\tHUMIDITY NUMBER : " << hum_number << std::endl;

        int64_t loc_number = ConvertWithMap(mappings["humidity-to-location"], hum_number);
        //std::cout << "\tLOCATION NUMBER : " << loc_number << std::endl;

        return loc_number;
}

int main(void){
    std::cout << "Advent of Code day 5" << std::endl;

    std::map<std::string, std::vector<OffsetPair>> mappings;

    std::fstream code_sheet;

    code_sheet.open("./input.txt", std::ios::in);

    if(!code_sheet.is_open()){
        std::cout << "could not find input.txt";
        return -1;
    }

    std::string line;

    std::getline (code_sheet, line);
    std::cout << line << std::endl;

    std::vector<int64_t> seeds;
    std::string sub;
    std::istringstream iss(line);
    while(std::getline(iss, sub, ' ')){
        try{
            seeds.push_back(std::stoll(sub));
        }catch(const std::exception & e){
            continue;
        }
            
    }

    //for( auto seed : seeds){
        //std::cout << seed << std::endl;
    //}

    while (true){
        
        if(line.empty()){
            //std::cout << "EMPTY" << std::endl;

            //NEW Block
            if(std::getline(code_sheet, line)){
                std::istringstream iss(line);
                std::getline(iss, sub, ' ');
                std::string map_name = sub;
                //std::cout << "ADDING MAP: " << map_name << std::endl;
                while(std::getline(code_sheet, line)){
                    if(line.empty()){
                        break;
                    }
                    //std::cout << "ADDING MAPPED" << std::endl;
                    std::istringstream iss(line);
                    std::vector<int64_t> mapping_numbers;
                    while(std::getline(iss, sub, ' ')){
                        try{
                            mapping_numbers.push_back(std::stoll(sub));
                            //std::cout << sub << std::endl;
                        }catch(const std::exception & e){
                            continue;
                        }  
                    }

                    if(mapping_numbers.size() == 3){
                        mappings[map_name].push_back({mapping_numbers[1], mapping_numbers[1] + (mapping_numbers[2] - 1), mapping_numbers[0] - mapping_numbers[1]});
                    }
                    for(const auto & number: mapping_numbers){
                        //std::cout << "\t" << number << std::endl;
                    }
                }
            }


        }else{
            if(!(std::getline(code_sheet, line))){
                break;
            }

            //std::cout << line << std::endl;
        }
    }

    //for(const auto& map_values : mappings){
        //std::cout << map_values.first << std::endl;
        //for (const auto & pairings: map_values.second){
            //std::cout << pairings.start << " : " << pairings.end << " : " << pairings.offset << std::endl;
        //}
    //}

    std::vector<int64_t> seed_locations;
    for (const auto & seed: seeds) {
        //Check per seed
        auto loc_number = convertToLocationFromSeed(seed, mappings);

        seed_locations.push_back(loc_number);
    }

    for( const auto & location: seed_locations){
        std::cout << "LOC: " << location << std::endl; 
    }

    auto min = std::min_element(seed_locations.begin(), seed_locations.end());
    if(min != seed_locations.end()){
        std::cout << "MINIMUM LOCATION : " << *min << std::endl;
    }

    //convert seed to seed ranges

    std::vector<int64_t> seed_ranges;
    std::cout << "MAKING NEW SEED NUMBERS: " << std::endl;

    auto loc_lowest = INT64_MAX;
    //int64_t progress = 0;

    for(auto it = seeds.begin(); it != seeds.end(); ++it){
        
        //First it is start of range
        int64_t start_range = *it;
        //++it is range size
        int64_t range_size = *(++it);
        //std::cout << "START: " << start_range << " : " << range_size << std::endl;
        //std::cout << "START: " << *it;
        std::cout << "CHECKING SEED RANGE: "<< start_range << " : " << range_size << std::endl;
        for(int64_t i= 0; i < range_size; ++i){
            //Check per seed
            auto loc_number = convertToLocationFromSeed(start_range + i, mappings);
            if (loc_number < loc_lowest) {
                loc_lowest = loc_number;
                std::cout << "NEW LOWEST: " << loc_lowest << std::endl; 
            }
        }
    }

    std::cout << "SEED RANGE SIZE MIN: " << loc_lowest << std::endl;



}
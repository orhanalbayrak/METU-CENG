#ifndef HW3_HELPER_H
#define HW3_HELPER_H
#include <iostream>
#include <stdlib.h>
#include <math.h>  
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
#include "Transaction.h"

std::vector<std::string> split(const std::string& str,
              char delim = ' ')
{
    std::vector <std::string> cont;
    std::size_t current, previous = 0;
    current = str.find(delim);
    while (current != std::string::npos) {
        cont.push_back(str.substr(previous, current - previous));
        previous = current + 1;
        current = str.find(delim, previous);
    }
    cont.push_back(str.substr(previous, current - previous));
    return cont;
}

void account_helper(std::vector<time_t>&  time_arr, Transaction** tr, int* val, std::string stats_path, std::string dates_path, std::string values_path) {
    
    std::string line;
    
    std::ifstream stats_file(stats_path);
    int counter = 0;
    for(int i = 0;i<12;i++) {
        val[i] = 0;
    }
    counter = 0;

    std::getline(stats_file, line);
    int how_many = std::stoi(line);
    for(int i = 0;i<how_many; i++) {
        std::getline(stats_file, line);
        char coma_delim = ',';
        std::vector<std::string> stat_arr = split(line, coma_delim);

        val[std::stoi(stat_arr[0])] = std::stoi(stat_arr[1]);
        if(val[std::stoi(stat_arr[0])] != 0 ) {
            tr[std::stoi(stat_arr[0])] = new Transaction[std::stoi(stat_arr[1])];
        } else {
            tr[std::stoi(stat_arr[0])] = nullptr;
        }
        
    }
    stats_file.close();
    std::ifstream dates_file(dates_path);
    while (std::getline(dates_file, line))
    {
        char space_delim = ' ';
        std::vector<std::string> date_arr = split(line, space_delim);
        
        
        struct tm temp = {0};
        
        temp.tm_year = std::stoi(date_arr[0]); temp.tm_mon = std::stoi(date_arr[1]); temp.tm_mday = std::stoi(date_arr[2]);
        temp.tm_hour = std::stoi(date_arr[3]); temp.tm_min = std::stoi(date_arr[4]); temp.tm_sec = std::stoi(date_arr[5]);
        time_arr.push_back(mktime(&temp));
    }

    dates_file.close();
    std::ifstream values_file(values_path);
    for(int i=0;i<12;i++) {
        for(int k=0;k<val[i];k++){
            std::getline(values_file, line);
            tr[i][k] = Transaction(std::stoi(line),time_arr[counter]);
            counter++;
        }
    }
    values_file.close();
}

#endif // HW3_HELPER_H
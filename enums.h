#pragma once

#include<iostream>
#include<queue>
#include<mutex>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


#include <condition_variable> // std::condition_variable


using namespace std;
 

typedef struct 
{
    string symbol;
    string trade;
    uint16_t price;
    uint16_t qty;
    uint64_t ts;
    string side;
    uint64_t ts1;
    std::string ToString() const
    {
        stringstream out;

        out << "{ symbol " << symbol << ", trade " << trade << ", price " << price << ", qty " << qty << ", ts1 " << ts1 << "}";
        return out.str();
    }
    
}TradeInformation;


typedef struct 
{
    string symbol;
    string trade;
    uint16_t price;
    uint16_t qty;
    uint64_t ts1;
    int bar_num;

    std::string ToString() const
    {
        stringstream out;

        out << "{ symbol " << symbol << ", trade " << trade << ", price " << price << ", qty " << qty << ", ts1 " << ts1 << ", bar_num " << bar_num << "}";
        return out.str();
    }
}BarGraph;
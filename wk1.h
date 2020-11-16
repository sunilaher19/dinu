
#ifndef _WK1_TRADE_
#define _WK1_TRADE_

#include<iostream>
#include<queue>
#include<mutex>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "enums.h"
#include <boost/algorithm/string.hpp> 
#include <fstream>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <time.h>

#include <condition_variable> // std::condition_variable

class wroker2
{
    public:
        void ProcessQueue(std::string symbol , int interval, queue<TradeInformation>&, bool&);
        mutex mtx;
        void ProcessData(TradeInformation data, std::string &symbol, int interval );
        vector<BarGraph> barGraph;
        bool firstIntervbalTrade =true;
        int bar_graph=1;
        time_t date;
        time_t initTIme;

};

#endif
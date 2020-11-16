#ifndef _WK_TRADE_
#define _WK_TRADE_

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


using namespace std;


class wroker1
{
    public:
        void Init(std::string, queue<TradeInformation>&, bool& doneProcessing);
        mutex mtx;

};



#endif
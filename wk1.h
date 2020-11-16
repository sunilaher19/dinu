
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
    private:
        uint16_t open=0;
        uint16_t close=0;
        uint16_t high=0;
        double volume=0;
        uint16_t low=0;

    public:
        void ProcessQueue(std::string symbol , int interval, queue<TradeInformation>&, bool&);
        mutex mtx;
        void ProcessData(TradeInformation data, std::string &symbol, int interval );
        vector<BarGraph> barGraph;
        void PrintQueue(vector<BarGraph> &);
        bool firstIntervbalTrade =true;
        int bar_graph=1;
        time_t date;
        time_t initTIme;

        inline void SetHigh(uint16_t _high) { high = _high;}
        inline void SetOpen(uint16_t _open) { open = _open;}
        inline void SetClose(uint16_t _close) { close = _close;}
        inline void SetVolume(double _volume) { volume  += _volume;}
        inline void SetLow(uint16_t _low) { low = _low;}

        inline uint16_t GetHigh() { return high;}
        inline uint16_t GetOpen() { return open;}
        inline uint16_t GetClose() { return close;}
        inline double GetVolume() { return volume;}
        inline uint16_t GetLow() { return low;}

        void resetValue()
        {
            close=0;
            open=0;
            high=0;
            low=0;
            volume=0;
        }

};

#endif
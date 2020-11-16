

#include "../include/wk1.h"

using namespace std;
namespace pt = boost::posix_time;
namespace g  = boost::gregorian;
using local_adj = boost::date_time::c_local_adjustor<pt::ptime>;
using namespace boost::property_tree;

void wroker2::ProcessQueue(std::string symbol , int interval, queue<TradeInformation>& tradeData , bool& doneProcessing)
{

    while(true)
    {
        while(!tradeData.empty())
        {
            TradeInformation datavalue = tradeData.front();
            ProcessData(datavalue, symbol, interval);
            std::unique_lock<std::mutex> lck(mtx);
            tradeData.pop();
        }
        if(doneProcessing and tradeData.size() == 0)
                break;
    }
}

void wroker2::ProcessData(TradeInformation data, std::string &symbol, int interval )
{
    if(data.symbol != symbol)
        return ;

    struct tm* now;
    time_t temptime = data.ts1  / 1000000000;
    struct tm* datetime ;

    if(firstIntervbalTrade)
    {
        initTIme = data.ts1  / 1000000000;;
        datetime = gmtime(&initTIme);
        date = mktime(datetime); 
        SetOpen(data.price);
        SetHigh(data.price);
        SetLow(data.price);
    }
    
    now = gmtime(&temptime);
    time_t t = mktime(now);
    auto seconds = difftime(t,date);
    
    
    //cout << "seconds =" << seconds << " mktime(now)= " << t<< " mktime(datetime)=" << date  << " :initTIme=" << initTIme << ": temptime " << temptime <<endl;

    if(seconds <= interval)
    {
        if(data.price > GetHigh())
        {
            SetHigh(data.price);
        }
        else if(data.price < GetLow())
        {
            SetLow(data.price);
        }

        SetVolume(data.qty);
        SetClose(data.price);

        BarGraph bargharstrucr;
        firstIntervbalTrade = false;
        bargharstrucr.symbol = data.symbol;
        bargharstrucr.price = data.price;
        bargharstrucr.qty = data.qty;
        bargharstrucr.ts1 = data.ts1;
        bargharstrucr.bar_num = bar_graph;
        bargharstrucr.open = GetOpen();
        bargharstrucr.close = 0;
        bargharstrucr.high = GetHigh();
        bargharstrucr.volume = GetVolume();
        bargharstrucr.low = GetLow();
        barGraph.push_back(bargharstrucr) ;
        return;
    }

    

    if(seconds > interval)
    {
        PrintQueue(barGraph);
        cout << endl;
        cout << endl;
        firstIntervbalTrade=true;
        ++bar_graph;
        resetValue();
        ProcessData(data, symbol, interval);
    }
    else if(barGraph.size() > 0)
    {
        PrintQueue(barGraph);
        resetValue();
    }

}

void wroker2::PrintQueue(vector<BarGraph> &barGraph)
{
    for(int i=0 ; i< barGraph.size()-1 ; i++)
    {
        auto info = barGraph[i];
        cout << info.ToString() <<endl;
    }
    
    auto info = barGraph[barGraph.size()-1 ];
    info.close = GetClose();
    cout << info.ToString() << endl;
    barGraph.clear();

}

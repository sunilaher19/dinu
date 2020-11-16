

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
    }
    
    now = gmtime(&temptime);
    time_t t = mktime(now);
    auto seconds = difftime(t,date);
    
    
    cout << "seconds =" << seconds << " mktime(now)= " << t<< " mktime(datetime)=" << date  << " :initTIme=" << initTIme << ": temptime " << temptime <<endl;

    if(seconds <= interval)
    {
        BarGraph bargharstrucr;
        firstIntervbalTrade = false;
        bargharstrucr.symbol = data.symbol;
        bargharstrucr.price = data.price;
        bargharstrucr.qty = data.qty;
        bargharstrucr.ts1 = data.ts1;
        bargharstrucr.bar_num = bar_graph;
        barGraph.push_back(bargharstrucr) ;
        cout << bargharstrucr.ToString() << endl; 
    }


    if(seconds > interval)
    {
        cout << endl;
        cout << endl;
        firstIntervbalTrade=true;
        ++bar_graph;
        ProcessData(data, symbol, interval);
    }


}

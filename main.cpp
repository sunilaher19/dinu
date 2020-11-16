

#include <boost/algorithm/string.hpp> 
#include <iostream> 
#include <thread>
#include "../include/enums.h"
#include "../include/wk.h"
#include "../include/wk1.h"


using namespace std; 
using namespace boost::algorithm; 


int main(int argc, char **agrv) 
{ 
    if(argc < 3)
    {
        cout << "Please enter data in form of symbol and interval";
        return 0;
    }

    std::string path= "/Users/sunilaher/dinesh_code/db/trades.json";
    /*
        Worker one will be responsible for Adding data from file to queue (tradeData)
    */
    auto wk1 = new wroker1();
    /*
        Worker two will be responsible for processing data from  queue (tradeData)
    */
    auto wk2 = new wroker2();
    queue<TradeInformation> tradeData;
    bool doneProcessing=false;

    std::thread t1(&wroker1::Init , wk1, path, std::ref(tradeData), std::ref(doneProcessing));

    std::thread t2(&wroker2::ProcessQueue , wk2 , agrv[1], atoi(agrv[2]), std::ref(tradeData), std::ref(doneProcessing));


    t1.join();
    t2.join();
    return 0;

}


#include "../include/wk.h"


using namespace std;
namespace pt = boost::posix_time;
namespace g  = boost::gregorian;
using local_adj = boost::date_time::c_local_adjustor<pt::ptime>;
using namespace boost::property_tree;


void wroker1::Init(std::string path, queue<TradeInformation>& tradeData, bool& doneProcessing)
{
    //cout << "Hello init :: " << path << endl;

    try
    {
        TradeInformation tradeInfo;
        fstream newfile;    
        std::string delimiters("{,}");
        newfile.open(path);
        if(newfile.is_open())
        {
            string line;
            while(getline(newfile, line))
            {
                
                stringstream out;
                out << line;
                ptree strTree;
                try {
                    read_json(out, strTree);
                
                    tradeInfo.symbol = strTree.get<string>("sym");
                    tradeInfo.trade = strTree.get<string>("T");
                    tradeInfo.price = stoll(strTree.get<string>("P"));
                    tradeInfo.qty = stoll(strTree.get<string>("Q"));
                    tradeInfo.ts =  stoll(strTree.get<string>("TS"));
                    tradeInfo.ts1 = stoll(strTree.get<string>("TS2"));
                    std::unique_lock<std::mutex> lck(mtx);
                    tradeData.push(tradeInfo);
                }
                catch (ptree_error & e)
                {
                    return ;
                }
            }
        }
        else
        {
            return;
        }
        
        doneProcessing=true;

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

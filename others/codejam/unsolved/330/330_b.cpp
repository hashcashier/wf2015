#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <cstdio>
#include <cstring>
using namespace std;
string action, name;
double cost, price = 0;
int quantity = 0;
map<string, double> costs;
map<string, double> prices;
map<string, int> quantities;
double profit = 0;
char* b = new char[128];
string header = "INVENTORY REPORT";
string itemname = "Item Name";
string buyat = "Buy At";
string sellat = "Sell At";
string onhand = "On Hand";
string value = "Value";
string hedrformat = "%12-s %7s %12s %12s %12s";
string lineformat = "%12-s %7.2f %12.2f %12i %12.2f";
vector<string> sold_items;
map<string, int> seen_items;
void annull()
{
    memset(b, 0, 128);
}
void report()
{
    annull();
    sprintf(b, "%35s", header.c_str());
    cout << b << endl;
    annull();
    sprintf(b, hedrformat.c_str() ,
            itemname.c_str(),
            buyat.c_str(), sellat.c_str(), onhand.c_str(), value.c_str());
    cout << b << endl;
    cout << "---------     ------      -------      -------        -----" << endl;
    map<string, int>::iterator qi;
    float totalval =  0;

    for(qi = quantities.begin(); qi != quantities.end(); ++qi) {
        string name = (*qi).first;
        cost = costs[name];
        price = prices[name];
        int q = quantities[name];
        annull();
        float val = q * cost;
        totalval += val;
        sprintf(b, lineformat.c_str(), name.c_str(), cost, price, q, val);
        cout << b << endl;
    }

    cout << "------------------------" << endl;
    annull();
    sprintf(b, "Total value of inventory %34.2f", totalval);
    cout << b << endl;
    annull();
    sprintf(b, "Profit since last report %34.2f", profit);
    profit = 0;
    cout << b << endl;
}
int main()
{
    while(true) {
		string prev_action = action;
        cin >> action;

        if (prev_action == "report" && action != "*") {
			cout << endl;
		}
		
        if (action == "*") {
            break;
        } 
        else if(action == "new") {
            cin >> name;
            cin >> cost >> price;
            prices[name] = price;
            costs[name] = cost;
			quantities[name] = 0;
        } else if(action == "buy") {
            cin >> name;
            cin >> quantity;
            quantities[name] += quantity;
        } else if(action == "sell") {
            cin >> name;
            cin >> quantity;
            quantities[name] -= quantity;
            profit += (prices[name] - costs[name]) * quantity;
            sold_items.push_back(name);
        } else if(action == "report") {
            report();
        } else if(action == "delete") {
            cin >> name;
            int q = quantities[name];
            profit -= q * costs[name];
            quantities.erase(name);
            prices.erase(name);
            costs.erase(name);
        }
    }

    return 0;
}

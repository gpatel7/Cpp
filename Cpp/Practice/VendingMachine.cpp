#include <iostream>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <regex>
#include<math>

using namespace std;

class Item
{
public:
    string Name;
    float Price;
    string Code;
    int Count;
};
typedef unordered_map<int, int> CashBoxType;

class Inventory
{
public:
    unordered_map<string, shared_ptr<Item>> items;
    bool AddItem(const string &code)
    {
        auto iter = items.find(code);
        if (iter != items.end())
        {
            iter->second->Count++;
            return true;
        }
        else
        {
            cerr << "Incorrect code. " << endl;
            return false;
        }
    }
    bool RemoveItem(const string &code)
    {
        auto iter = items.find(code);
        if (iter != items.end())
        {
            iter->second->Count--;
            return true;
        }
        {
            cerr << "Invalid operation. " << endl;
        }
    }
    shared_ptr<Item> GetItem(const string &code)
    {
        auto iter = items.find(code);
        if (iter != items.end())
        {
            return iter->second;
        }
        return shared_ptr<Item>(new Item);
    }
    bool LoadInventory()
    {
        try
        {
            ifstream f("/Users/ndoshi200/CodePractice/Cpp/Practice/items.txt");
            vector<string> row;
            string line, cell;
            if (!f.is_open())
            {
                cerr << "Find not found." << endl;
            }

            while (getline(f, line))
            {
                row.clear();

                stringstream s(line);
                while (getline(s, cell, ','))
                {
                    row.push_back(cell);
                }

                shared_ptr<Item> item(new Item());

                item->Name = row[0];
                item->Code = row[1];
                item->Price = regex_match(row[2], regex("[+-]?([0-9]*[.])?[0-9]+")) ? atof(row[2].c_str()) : 0;
                item->Count = 10;

                items.insert(make_pair(item->Code, item));
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
};

class Machine
{
private:
    Inventory _inventory;
    CashBoxType cashbox;
    bool LoadCash()
    {
        cashbox.insert(make_pair(1, 100));
        cashbox.insert(make_pair(5, 100));
        cashbox.insert(make_pair(10, 100));
        cashbox.insert(make_pair(1, 100));
        cashbox.insert(make_pair(100, 100));
    }
public:
    bool IsValid(const string &code, const float userCashTotal)
    {
        shared_ptr<Item> item = _inventory.GetItem(code);
        if (item->Code.empty())
        {
            cerr << "Invalid Code." << endl;
            return false;
        }
        if (userCashTotal >= item->Price)
        {
            //Some function to call hardware function to release an item
           return true;
        }
    }
    int Purchase(const string& code,int& total)
    {
        _inventory.RemoveItem(code);
        total-=_inventory.items[code]->Price;
    }
    int ReturnCash(const int userCash)
    {
        int cashInCents=round(userCash*100);
        int pennCount, nickelCount, dimeCount, quarterCount, dollarCount;
        
        pennCount = cashInCents%100;
        if(cashbox.find(1)->second-pennCount >0)
        {
            cashInCents-= pennCount * 100;
        }
        else
        {
            pennCount=cashbox.find(1)->second;
            cashbox.find(1)->second=0;
        }



    }
};

int main()
{
    string  input,code;
    float total;
    int pennCount, nickelCount, dimeCount, quarterCount, dollarCount;
    CashBoxType userCash;
    Machine m = Machine();
    cout << " Enter Item Code :";
    cin >> code;

    cout << " Enter coins. 1 for Penny, 5 for nickel, 10 for dime,  25 for quarter 100 for 1 dollar ..." << endl;
    cout << "Enter 'd' when done..." << endl;

    while (cin >> input)
    {
        if (input == "d")
            break;

        int coinValue = regex_match(input, regex("\d+")) ? atof(input.c_str()) : 0;
        switch (coinValue)
        {
        case 1:
            pennCount++;
            break;
        case 5:
            nickelCount++;
            break;
        case 10:
            dimeCount++;
            break;
        case 25:
            quarterCount++;
            break;
        case 100:
            dollarCount++;
            break;
        default:
            cerr << "Invalid Entry..Valid optoins are 1,5,10,25,100 or d" << endl;
        }
    }
    userCash.insert(make_pair(1, pennCount));
    userCash.insert(make_pair(5, nickelCount));
    userCash.insert(make_pair(10, dimeCount));
    userCash.insert(make_pair(25, quarterCount));
    userCash.insert(make_pair(100, dollarCount));

    for(const auto& [key,value] : userCash)
    {
        total += (key/100)*value;
    }
    
    if(m.Purchase(code,int& total))
    {
        total -
    }


}
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<map>
#include<regex>

using namespace std;

enum ProductType
{
    PRODUCE = 0,
    HOME,
    ELECTRONICS,
    GARDEN,
    NONE = -99
};
class Item
{
    public:
    string Name;
    ushort Price;
    ProductType Type;
    void ToString() const
    {
        stringstream s;
        s << "[Name:" << Name << "] [price=" << Price << "] [Type:" << Type << "]";
        cout << s.str() << endl;
    }
 //   Item(const string& name, const float price, const ProductType& type):Name(name),Price(price),Type(type){}
};

typedef vector<shared_ptr<Item>> ItemListType;
typedef map<ProductType,ushort> DiscountListType;
class Inventory
{
    private:
    ItemListType _itemList;
    DiscountListType _discountList;
    void LoadInventory()
    {
        ifstream f("/Users/ndoshi200/CodePractice/Cpp/Practice/movies.txt");
        vector<string> row;
        string cell,line;
        if(!f.is_open())
        {
            cerr << "file not found." << endl;
            return;
        }
        while(getline(f,line))
        {
            row.clear();
            stringstream s(line);
            while(getline(s,cell,','))
            {
                row.push_back(cell);
            }
            shared_ptr<Item> m(new Item());
            m->Name=row[0];
            m->Type= regex_match(row[1],regex("[0-9]+"))?(ProductType)atoi(row[7].c_str()):ProductType::NONE;
            m->Price = regex_match(row[7],regex("[0-9].[0-9]+"))?atoi(row[7].c_str()):0;

            _itemList.push_back(m);
        
    }
    float GetTotal(const ProductType& type)
    {
        ushort total=0;
        
        for(ItemListType::iterator iter =_itemList.begin();iter!=_itemList.end(); ++iter)
        {
            auto discount = _discountList.find((*iter)->Type);
            if(discount!=_discountList.end())
            {
                total+= (*iter)->Price - (((*iter)->Price * discount->second)/100);
            }
        }
        return total;
        

}
int main(void)
{
    Inventory inv=Inventory();
    
    return 0;
}
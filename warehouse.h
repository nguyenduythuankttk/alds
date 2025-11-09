#include <string>
#include "vector.h"
#include "map.h"
using namespace std;
class Warehouse{
    int id;
    string name;
    string address;
    Map<string, int> Inventory;
    public:
        Warehouse();
        Warehouse(const int&,const string&,const string&);
        ~Warehouse();
        int Get_ID() const;
        string Get_Name() const;
        string Get_Address() const;
        void readfile(Vector <Warehouse> &v);
        void savefile(const Vector <Warehouse>& v);
        Warehouse& Find_by_id(const int &,const Vector<Warehouse> &);
        void Add_Product(const string& ,const int &);
        void Remove_Product(const string& , const int &);
        int Get_Quantity(const string&) const;
};
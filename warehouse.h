#include <string>
#include "vector.h"
using namespace std;
class Warehouse{
    int id;
    string cat;
    string location;
    public:
        Warehouse();
        Warehouse(const int&,const string&,const string&);
        void New_Warehouse(const int&,const string&,const string&);
        int Get_ID() const;
        string Get_Cat() const;
        string Get_Location() const;
        void Set_ID(const int&);
        void Set_Cat(const string&);
        void Set_Location(const string&);
        void readfile(Vector <Warehouse> &v);
        void savefile(const Vector <Warehouse>& v);
};
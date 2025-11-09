#include "global.cpp"
#include "func.cpp"
void menu(){

}
using namespace std;
int main(){
    // khai báo các vector class sử dụng trong toàn chương trình
    Vector<Warehouse> Warehouse_List; 
    Vector<Product> Product_List;
    Vector<User> User_List;
    Vector<Employee> Employee_List;
    Vector <PurchaseOrder> PurchaseOrder_List; 
    Vector<Product> Find_result;


    // đọc file
    Product p;p.readfile(Product_List);
    Warehouse w;w.readfile(Warehouse_List);
    User u;u.readfile(User_List);
    Employee e;e.readfile(Employee_List);
    PurchaseOrder pu;pu.Readfile(PurchaseOrder_List);
    //menu đăng nhập 
    main_menu();
    // lưu file
    p.savefile(Product_List);
    w.savefile(Warehouse_List);
    u.savefile(User_List);
    e.savefile(Employee_List);
    pu.Savefile(PurchaseOrder_List);
}
#include "library.h"    
#include "warehouse.h"   
#include "product.h"      
#include "user.h"         
#include "employee.h"     
#include "purchaseorder.h"
#include "customerorder.h"
#include "chitietphieunhap.h"
#include "chitiethoadon.h"
using namespace std;

//biến toàn cục 
    Vector<Warehouse> Warehouse_List;
    Vector<Product> Product_List;
    Vector<Product> inWarehouse;
    Vector<User> User_List;
    Vector<Employee> Employee_List;
    Vector<PurchaseOrder> PurchaseOrder_List;
    Vector<CustomerOrder> CustomerOrder_List;
    Vector <ChitietPhieunhap> hoadon_List;
    Vector <CTHD> dshoadon;
    Warehouse a;
    User current_User;
    Employee current_Employee;


int main() {
    // đọc file
    Product p;p.readfile(Product_List);
    Warehouse w;w.readfile(Warehouse_List);
    User u;u.readfile(User_List);
    Employee e;e.readfile(Employee_List);
    ChitietPhieunhap ctp;ctp.ReadFile(hoadon_List);
    PurchaseOrder pu;pu.Readfile(PurchaseOrder_List);
    CustomerOrder c;c.Readfile(CustomerOrder_List); 
    CTHD ct; ct.Readfile(dshoadon);

    // menu dang nhap
    main_menu();

    // lưu file sau khi ket thuc
    p.savefile(Product_List);
    w.savefile(Warehouse_List);
    u.savefile(User_List);
    e.savefile(Employee_List);
    pu.Savefile(PurchaseOrder_List);
    ctp.SaveFile(hoadon_List);
    c.Savefile(CustomerOrder_List);
    ct.Savefile(dshoadon);
}

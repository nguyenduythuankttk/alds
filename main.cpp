#include "library.h"    
#include "warehouse.h"   
#include "product.h"      
#include "user.h"         
#include "employee.h"     
#include "purchaseorder.h"
#include "customerorder.h"

using namespace std;

//biến toàn cục 
    Vector<Warehouse> Warehouse_List;
    Vector<Product> Product_List;
    Vector<Product> inWarehouse;
    Vector<User> User_List;
    Vector<Employee> Employee_List;
    Vector<PurchaseOrder> PurchaseOrder_List;
    Vector<CustomerOrder> CustomerOrder_List;
    Warehouse a;
    User current_User;
    Employee current_Employee;


int main() {
    // đọc file
    Product p;p.readfile(Product_List);
    Warehouse w;w.readfile(Warehouse_List);
    User u;u.readfile(User_List);
    Employee e;e.readfile(Employee_List);
    PurchaseOrder pu;pu.Readfile(PurchaseOrder_List);
    CustomerOrder c;c.readFile(CustomerOrder_List); 
    // menu dang nhap
    main_menu();

    // lưu file sau khi ket thuc
    p.savefile(Product_List);
    w.savefile(Warehouse_List);
    u.savefile(User_List);
    e.savefile(Employee_List);
    pu.Savefile(PurchaseOrder_List);
    c.saveFile(CustomerOrder_List);
}

#include "thongke.h"
#include "library.h"
#include "purchaseorder.h"
#include "customerorder.h"
Thongke::Thongke(){
    this->doanh_thu=0;
    this->sl_donnhap=0;
    this->sl_donxuat=0;
    this->tien_nhap=0;
    this->tien_xuat=0;
}
Thongke::Thongke(const Thongke& other){
    this->doanh_thu=other.doanh_thu;
    this->sl_donnhap=other.sl_donnhap;
    this->sl_donxuat=other.sl_donxuat;
    this->tien_nhap=other.tien_nhap;
    this->tien_xuat=other.tien_xuat;
}
Thongke::Thongke(const Thongke * other){
    this->doanh_thu=other->doanh_thu;
    this->sl_donnhap=other->sl_donnhap;
    this->sl_donxuat=other->sl_donxuat;
    this->tien_nhap=other->tien_nhap;
    this->tien_xuat=other->tien_xuat;
}
int Thongke::GetSLDonNhap() const { return sl_donnhap; }
int Thongke::GetSLDonXuat() const { return sl_donxuat; }
long long Thongke::GetTienNhap() const { return tien_nhap; }
long long Thongke::GetTienXuat() const { return tien_xuat; }
long long Thongke::GetDoanhThu() const { return doanh_thu; }
Thongke Thongke::Tke_doanhthu(const int month,const int year){
    for (int i=0;i<PurchaseOrder_List.getsize();i++){
        int a[3];
        parse_date(PurchaseOrder_List[i].GetDate(),a);
        if (a[1]==month && a[2]==year){
            this->sl_donnhap++;
            this->tien_nhap+=PurchaseOrder_List[i].getsum();
        }
    }
    for (int i=0;i<CustomerOrder_List.getsize();i++){
        int a[3];
        parse_date(CustomerOrder_List[i].GetDate(),a);
        if (a[1]==month && a[2]==year){
            this->sl_donxuat++;
            this->tien_xuat+=CustomerOrder_List[i].getsum();
        }
    }
    this->doanh_thu=this->tien_xuat-this->tien_nhap;
    return *(this);
}

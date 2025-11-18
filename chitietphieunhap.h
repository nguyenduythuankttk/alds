#pragma once
#include "vector.h"
#include <string>
using namespace std;
class ChitietPhieunhap{
    private:
        int id;
        string idProduct;
        int soLuong;
        int donGia;
        int tongTien;
    public:
        ChitietPhieunhap();
        ~ChitietPhieunhap();
        void SaveFile(const Vector <ChitietPhieunhap>&) const;
        void ReadFile(Vector <ChitietPhieunhap>&);
        void SetDetail(const int&, const string&, const int&, const int&);
        int GetID() const;
        string GetProductID() const;
        int GetSoLuong() const;
        int GetDonGia() const;
        int TongTien() const;
        static void show(const Vector<ChitietPhieunhap>&, int orderID);

};

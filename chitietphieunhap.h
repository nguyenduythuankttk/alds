#pragma once
#include "vector.h"
#include "map.h"
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
        int TongTien() const;

};
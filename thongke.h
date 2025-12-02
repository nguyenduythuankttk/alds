class Thongke{
    int sl_donnhap;
    int sl_donxuat;
    long long tien_nhap;
    long long tien_xuat;
    long long doanh_thu;
    public:
        Thongke();
        Thongke(const Thongke & );
        Thongke(const Thongke * );
        Thongke Tke_doanhthu(const int,const int);
        int GetSLDonNhap() const;
        int GetSLDonXuat() const;
        long long GetTienNhap() const;
        long long GetTienXuat() const;
        long long GetDoanhThu() const;
};

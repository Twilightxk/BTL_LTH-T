#ifndef ORDER_H
#define ORDER_H
#include "OrderDetail.h"
#include "Product.h"

class Order{
    protected:
        string maDon;

        vector<OrderDetail> dsChiTiet;

    public:
        Order();

        Order(string maDon);

        string getMaDon() const;

        vector<OrderDetail>& getDsChiTiet();

        void setMaDon(string maDon);

        void themSanPhamVaoDon(OrderDetail chiTiet);

        bool coSanPham(const string& maSp) const;  // kiểm tra sp đã có trong đơn chưa

        void suaSoLuongSanPham(string maSp, int soLuong);

        void xoaSanPhamKhoiDon(string maSp);

        virtual double tinhTongTien(const vector<Product*>& dsSanPham) const = 0;

        virtual void xuatThongTin() const;

        virtual ~Order(){}



};
class RetailOrder : public Order{
    public:
        RetailOrder();

        RetailOrder(string maDon);
        
        double tinhTongTien(const vector<Product*>& dsSanPham) const override;

        void xuatThongTin() const override;


};
class WholesaleOrder : public Order {
    private:
        double mucChietKhau;
    public:
        WholesaleOrder();

        WholesaleOrder(string maDon, double mucChietKhau);

        double getMucChietKhau() const;

        void setMucChietKhau(double mucChietKhau);

        double tinhTongTien(const vector<Product*>& dsSanPham) const override;

        void xuatThongTin() const override;

};

#endif
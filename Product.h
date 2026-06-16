#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;
class Product {
    protected:
        string maSp;
        string tenSp;
        double giaGoc;
    public:
        Product();

        Product(string maSp, string tenSp, double giaGoc);

        string getMaSp() const;

        string getTenSp() const;

        double getGiaGoc() const;

        void setMaSp(string maSp);

        void setTenSp(string tenSp);

        void setGiaGoc(double giaGoc);

        virtual double tinhGiaBan() const = 0;

        virtual void xuatThongTin() const;

        virtual void nhapThongTin();
        
        virtual ~Product(){}
        

};
class NormalProduct: public Product {
    private: 

        double thueVAT;

    public:
        NormalProduct();

        NormalProduct(string maSp, string tenSp, double giaGoc, double thueVAT);

        double getThueVAT() const;

        void setThueVAT(double thueVAT);

        double tinhGiaBan() const override;

        void nhapThongTin() override;

        void xuatThongTin() const override;

        ~NormalProduct();
};
class PromoProduct: public Product{
    private:

        double mucGiamGia;

    public:
        PromoProduct();

        PromoProduct(string maSp, string tenSp, double giaGoc, double mucGiamGia);

        double getMucGiamGia() const;

        void setMucGiamGia(double mucGiamGia);
 
        double tinhGiaBan() const override;
 
        void nhapThongTin() override;

        void xuatThongTin() const override;

        ~PromoProduct();
};






#endif 
#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <vector>
#include <string>
#include <fstream>
#include "Product.h"
#include "Order.h"

using namespace std;


class OrderManager {
private:
    vector<Product*> dsSanPham;
    vector<Order*> dsDonHang;


public:
    OrderManager();
    
    ~OrderManager();


    void themSanPham();

    void suaSanPham();

    void xoaSanPham();

    void taoDonHang();

    void suaDonHang();

    void xoaDonHang();

    void lietKeSanPham() const;

    void lietKeDonHang() const;

};

#endif
#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <vector>
#include <string>
#include <fstream>
#include "Product.h"
#include "Order.h"

using namespace std;

// Lớp quản lý nghiệp vụ trung tâm
class OrderManager {
private:
    vector<Product*> dsSanPham;
    vector<Order*> dsDonHang;

    // void ghiString(std::ofstream& f, const std::string& str) const;
    // std::string docString(std::ifstream& f);

public:
    OrderManager();
    ~OrderManager();

    // Hệ thống menu nghiệp vụ yêu cầu từ đề bài
    void themSanPham();
    void suaSanPham();
    void xoaSanPham();
    void taoDonHang();
    void suaDonHang();
    void xoaDonHang();
    void lietKeSanPham() const;
    void lietKeDonHang() const;

    // Quản lý đồng bộ File nhị phân
    // void ghiFile();
    // void docFile();
};

#endif
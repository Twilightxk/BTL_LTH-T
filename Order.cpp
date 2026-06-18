#include "Order.h"

Order::Order() : maDon("") {}

Order::Order(string maDon) : maDon(maDon) {}

string Order::getMaDon() const { 
    return maDon; 
}
vector<OrderDetail>& Order::getDsChiTiet() { 
    return dsChiTiet; 
}
void Order::setMaDon(string maDon) { 
    this->maDon = maDon; 
}

void Order::themSanPhamVaoDon(OrderDetail chiTiet) {
    dsChiTiet.push_back(chiTiet);
}

//kiểm tra sp đã tồn tại trong đơn
bool Order::coSanPham(const string& maSp) const {
    for (const auto& ct : dsChiTiet) {
        if (ct.getMaSp() == maSp) {
            return true;
        }
    }
    return false;
}

void Order::suaSoLuongSanPham(string maSp, int soLuong) {
    for (auto& ct : dsChiTiet) {
        if (ct.getMaSp() == maSp) {
            ct.setSoLuong(soLuong);
            return;
        }
    }
    cout << "Khong tim thay san pham " << maSp << " trong don hang." << endl;
}

void Order::xoaSanPhamKhoiDon(string maSp) {
    for (auto it = dsChiTiet.begin(); it != dsChiTiet.end(); ++it) {
        if (it->getMaSp() == maSp) {
            dsChiTiet.erase(it);
            return;
        }
    }
    cout << "Khong tim thay san pham " << maSp << " trong don hang." << endl;
}

void Order::xuatThongTin() const {
    cout << "Ma don: " << maDon << endl;
    cout << "Danh sach san pham:" << endl;
    for (auto& ct : dsChiTiet) {
        cout << "  Ma SP: " << ct.getMaSp() << " | So luong: " << ct.getSoLuong() << endl;
    }
}


RetailOrder::RetailOrder() : Order() {}
RetailOrder::RetailOrder(string maDon) : Order(maDon) {}


double RetailOrder::tinhTongTien(const vector<Product*>& dsSanPham) const {
    double tong = 0;
    for (auto& ct : dsChiTiet) {
        for (auto sp : dsSanPham) {
            if (sp->getMaSp() == ct.getMaSp()) {
                tong += sp->tinhGiaBan() * ct.getSoLuong();
                break;
            }
        }
    }
    return tong;
}

void RetailOrder::xuatThongTin() const {
    cout << "[Don ban le] ";
    Order::xuatThongTin();
}


WholesaleOrder::WholesaleOrder() : Order(), mucChietKhau(0) {}
WholesaleOrder::WholesaleOrder(string maDon, double mucChietKhau)
    : Order(maDon), mucChietKhau(mucChietKhau) {}

double WholesaleOrder::getMucChietKhau() const { 
    return mucChietKhau; 
}
void WholesaleOrder::setMucChietKhau(double mucChietKhau) { 
    this->mucChietKhau = mucChietKhau; 
}


double WholesaleOrder::tinhTongTien(const vector<Product*>& dsSanPham) const {
    double tong = 0;
    for (auto& ct : dsChiTiet) {
        for (auto sp : dsSanPham) {
            if (sp->getMaSp() == ct.getMaSp()) {
                tong += sp->tinhGiaBan() * ct.getSoLuong();
                break;
            }
        }
    }
    return tong * (1 - mucChietKhau);
}

void WholesaleOrder::xuatThongTin() const {
    cout << "[Don ban buon] Chiet khau: " << mucChietKhau * 100 << "%" << endl;
    Order::xuatThongTin();
}
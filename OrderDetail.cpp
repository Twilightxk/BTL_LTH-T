#include "OrderDetail.h"

OrderDetail::OrderDetail() : maSp(""), soLuong(0) {}

OrderDetail::OrderDetail(string maSp, int soLuong)
    : maSp(maSp), soLuong(soLuong) {}

string OrderDetail::getMaSp() const { 
    return maSp; 
}
int OrderDetail::getSoLuong() const { 
    return soLuong; 
}

void OrderDetail::setMaSp(string maSp) { 
    this->maSp = maSp; 
}
void OrderDetail::setSoLuong(int soLuong) { 
    this->soLuong = soLuong; }

void OrderDetail::input() {
    cout << "Ma SP: "; 
    cin >> maSp;
    cin.ignore();
    cout << "So luong: "; 
    cin >> soLuong;
    cin.ignore();
}

void OrderDetail::output() {
    cout << "Ma SP: " << maSp << " | So luong: " << soLuong << endl;
}
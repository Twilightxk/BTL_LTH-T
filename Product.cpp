#include "Product.h"

Product::Product() : maSp(""), tenSp(""), giaGoc(0) {}

Product::Product(string maSp, string tenSp, double giaGoc)
    : maSp(maSp), tenSp(tenSp), giaGoc(giaGoc) {}

string Product::getMaSp() const {
    return maSp; 
}
string Product::getTenSp() const {
    return tenSp; 
}
double Product::getGiaGoc() const { 
    return giaGoc; 
}

void Product::setMaSp(string maSp) { 
    this->maSp = maSp; 
}
void Product::setTenSp(string tenSp) { 
    this->tenSp = tenSp; 
}
void Product::setGiaGoc(double giaGoc) { 
    this->giaGoc = giaGoc; 
}

void Product::nhapThongTin() {
    cout << "Ma SP: "; 
    cin >> maSp;
    cin.ignore();
    cout << "Ten SP: "; 
    getline(cin, tenSp);

    while (true) {
        try {
            cout << "Gia goc: ";
            if (!(cin >> giaGoc)) {
                throw "Loi: Gia goc phai la mot so!";
            }
            if (giaGoc < 0) {
                throw "Loi: Gia goc phai la so duong!";
            }
            cin.ignore();
            break;
        } 
        catch (const char* msg) {
            cout << msg << " Vui long thu lai.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

void Product::xuatThongTin() const {
    cout << "Ma SP: " << maSp << endl;
    cout << "Ten SP: " << tenSp << endl;
    cout << "Gia goc: " << giaGoc << endl;
    cout << "Gia ban: " << tinhGiaBan() << endl;
}



NormalProduct::NormalProduct() : Product(), thueVAT(0) {}

NormalProduct::NormalProduct(string maSp, string tenSp, double giaGoc, double thueVAT)
    : Product(maSp, tenSp, giaGoc), thueVAT(thueVAT) {}

double NormalProduct::getThueVAT() const { 
    return thueVAT; 
}
void NormalProduct::setThueVAT(double thueVAT) { 
    this->thueVAT = thueVAT; 
}

double NormalProduct::tinhGiaBan() const {
    return giaGoc * (1 + thueVAT);
}

void NormalProduct::nhapThongTin() {
    Product::nhapThongTin();
    cout << "Thue VAT (0.1 = 10%): ";
    cin >> thueVAT;
    cin.ignore();
    while (thueVAT < 0 || thueVAT > 1) {
        cout << "Thue VAT phai la so trong khoang [0, 1]. Vui long nhap lai: ";
        cin >> thueVAT;
        cin.ignore();
    }
}

void NormalProduct::xuatThongTin() const {
    Product::xuatThongTin();
    cout << "Thue VAT: " << thueVAT * 100 << "%" << endl;
}


PromoProduct::PromoProduct() : Product(), mucGiamGia(0) {}

PromoProduct::PromoProduct(string maSp, string tenSp, double giaGoc, double mucGiamGia)
    : Product(maSp, tenSp, giaGoc), mucGiamGia(mucGiamGia) {}

double PromoProduct::getMucGiamGia() const { 
    return mucGiamGia; 
}
void PromoProduct::setMucGiamGia(double mucGiamGia) { 
    this->mucGiamGia = mucGiamGia; 
}

double PromoProduct::tinhGiaBan() const {
    return giaGoc * (1 - mucGiamGia);
}

void PromoProduct::nhapThongTin() {
    Product::nhapThongTin();
    cout << "Muc giam gia (0.1 = 10%): "; 
    cin >> mucGiamGia;
    cin.ignore();
    while (mucGiamGia < 0 || mucGiamGia > 1) {
        cout << "Muc giam gia phai la so trong khoang [0, 1]. Vui long nhap lai: ";
        cin >> mucGiamGia;
        cin.ignore();
    }
}

void PromoProduct::xuatThongTin() const {
    Product::xuatThongTin();
    cout << "Muc giam gia: " << mucGiamGia * 100 << "%" << endl;
}


NormalProduct::~NormalProduct() {}

PromoProduct::~PromoProduct() {}
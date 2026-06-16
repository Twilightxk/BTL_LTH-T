#include "OrderManager.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

OrderManager::OrderManager() {}

OrderManager::~OrderManager() {
    // Giải phóng bộ nhớ
    for (auto sp : dsSanPham) {
        delete sp;
    }
    for (auto dh : dsDonHang) {
        delete dh;
    }
    dsSanPham.clear();
    dsDonHang.clear();
}

void OrderManager::themSanPham() {
    cout << "====Them san pham moi====" << endl;
    cout << "1. San pham thong thuong (Co thue VAT)" << endl;
    cout << "2. San pham khuyen mai (Co muc giam)" << endl;
    cout<< "Lua chon cua ban: ";
    int loaiSP;
    cin >> loaiSP;
    cin.ignore(); 
    
    Product* p = nullptr;
    if (loaiSP == 1) {

        p = new NormalProduct();

    }
    else if (loaiSP == 2) {

        p = new PromoProduct();

    }
    else {
        cout << "Loai san pham khong hop le!" << endl;
        return;
    }

    p->nhapThongTin();
    //check
    for (const auto& sp : dsSanPham) {
        if (sp->getMaSp() == p->getMaSp()) {
            cout << "Ma san pham da ton tai. Them san pham that bai!" << endl;
            delete p; 
            return;
        }
    }
    dsSanPham.push_back(p);
    cout << "Them san pham thanh cong!" << endl;

}
void OrderManager::suaSanPham() {
    cout << "====Sua thong tin san pham====" << endl;

    cout << "Nhap ma san pham can sua: ";

    string maSp;

    cin >> maSp;
    cin.ignore();

   for (auto p : dsSanPham) {

        if (p->getMaSp() == maSp) {

            string tenMoi; 

            double giaMoi;

            cout << "San Pham tim thay: " << p->getTenSp() << " (Gia goc hien tai: " << p->getGiaGoc() << ")" << endl;

            cout << "Nhap ten moi: "; 
            cin.ignore(); 
            getline(cin, tenMoi);

            cout << "Nhap gia goc moi: "; 
            cin >> giaMoi;
            cin.ignore();
            while (giaMoi < 0) {
                cout << "Gia goc phai la so duong. Vui long nhap lai: ";
                cin >> giaMoi;
                cin.ignore();
            }

            p->setTenSp(tenMoi);

            p->setGiaGoc(giaMoi);

            cout << "Cap nhat san pham thanh cong!" << endl;

            return;
        }
    }
    
    cout << "Khong tim thay san pham voi ma tren!" << endl;

}
void OrderManager::xoaSanPham() {
        cout << "\n====Xoa san pham====" << endl;
    cout << "Nhap ma san pham can xoa: ";
    string ma; 
    getline(cin, ma);
    cin.ignore();
 
    //  Kiểm tra mã sản phẩm này có đang nằm trong bất kỳ đơn hàng nào không
    for (auto sp : dsDonHang) {
        for (auto& dt : sp->getDsChiTiet()) {
            if (dt.getMaSp() == ma) {
                cout << "LOI: Khong the xoa! San pham nay dang ton tai trong Don hang ma: " << sp->getMaDon() << endl;
                return;
            }
        }
    }
 
    // Xóa sản phẩm
    for (auto it = dsSanPham.begin(); it != dsSanPham.end(); ++it) {
        if ((*it)->getMaSp() == ma) {
            delete *it; 
            dsSanPham.erase(it);
            cout << "Xoa san pham khoi kho thanh cong!" << endl;
            return;
        }
    }
    cout << "Khong tim thay san pham!" << endl;
}
void OrderManager::taoDonHang() {
    cout << "====Tao don hang moi====" << endl;
    cout << "1. Don hang Ban Le (Retail Order)" << endl;
    cout << "2. Don hang Dai Ly/Ban Buon (Wholesale Order)" << endl;
    cout << "Lua chon loai don hang: ";
    int loai; 
    cin >> loai;
    cin.ignore();
    Order* dh = nullptr;
    if (loai == 1) {

        dh = new RetailOrder();

    }
    else if (loai == 2) {

        dh = new WholesaleOrder();

    }
    else {
        cout << "Lua chon khong hop le!" << endl;
        return;
    }

    string maDon;
    cout << "Nhap ma don hang moi: "; 
    getline(cin, maDon);
 
    // Check trùng mã đơn
    for (auto dh : dsDonHang) {
        if (dh->getMaDon() == maDon) {
            cout << "Loi: Ma don hang da ton tai!" << endl;
            delete dh;
            return;
        }
    }
    dh->setMaDon(maDon);

    char tiepTuc = 'y';

    while (tiepTuc == 'y' || tiepTuc == 'Y') {

        cout << "Nhap ma san pham muon mua: ";
        string maSP; 
        getline(cin, maSP);
 
        // Kiểm tra mã sản phẩm có tồn tại trong kho không
        bool timThay = false;
        for (auto p : dsSanPham) {
            if (p->getMaSp() == maSP) { 
                timThay = true; 
                break; 
            }
        }
 
        if (!timThay) {
            cout << "San pham khong ton tai trong kho! Vui long chon ma khac." << endl;
        } 
        else {
            int soLuongMua; 
            cout << "Nhap so luong mua: "; 
            cin >> soLuongMua;
            cin.ignore(); 
            if (soLuongMua <= 0) 
            {
                cout << "So luong phai lon hon 0!" << endl;
            }
            else
            {
                dh->themSanPhamVaoDon(OrderDetail(maSP, soLuongMua));
            }
        }
 
        cout << "Tiep tuc them san pham vao don nay? (y/n): ";
        cin >> tiepTuc;
        cin.ignore(); 
    }
 
    dsDonHang.push_back(dh);

    cout << "Tao don hang thanh cong!" << endl;


}
void OrderManager::suaDonHang() {
    cout << "====Sua don hang====" << endl;
    string maDon;
    cout << "Nhap ma don hang can sua: ";
    getline(cin, maDon);
    cin.ignore();

    Order* donHang = nullptr;

    for (auto dh : dsDonHang) {

        if (dh->getMaDon() == maDon) {

            donHang = dh;

            break;
        }
    }
    if (donHang == nullptr) {
        cout << "Khong tim thay don hang voi ma tren!" << endl;
        return;
    }

    int luaChon;
    do {
        cout << "\n--- MENU CHINH SUA DON HANG " << maDon << " ---" << endl;
        cout << "1. Them san pham vao don" << endl;
        cout << "2. Sua so luong san pham trong don" << endl;
        cout << "3. Xoa san pham khoi don" << endl;
        cout << "4. Quay lai Menu chinh" << endl;
        cout << "Nhap lua chon cua ban (1-4): ";
        cin >> luaChon;
        cin.ignore();

        string maSP;
        int soLuongMua;
        switch (luaChon)
        {
            case 1:
                cout << "Nhap ma san pham muon them: ";
                getline(cin, maSP);
                cin.ignore();
                // Kiểm tra mã sản phẩm có tồn tại không
                {
                    bool ok = false;
                        for (auto p : dsSanPham) {
                            if (p->getMaSp() == maSP) {
                                ok = true;
                            }
                        }
                        if (!ok) { cout << "Ma SP khong hop le!" << endl; break; }
                }
                cout << "Nhap so luong: "; 
                cin >> soLuongMua;
                cin.ignore();
                while (soLuongMua <= 0) {

                    cout << "So luong phai lon hon 0! Vui long nhap lai: ";

                    cin >> soLuongMua;

                    cin.ignore();
                }
                donHang->themSanPhamVaoDon(OrderDetail(maSP, soLuongMua));

                cout << "Da cap nhat don hang!" << endl;

                break;
                    
            case 2:
                cout << "Nhap ma san pham can sua so luong: "; 
                getline(cin, maSP);
                cin.ignore();

                cout << "Nhap so luong moi: "; 
                cin >> soLuongMua;
                cin.ignore();
                while (soLuongMua <= 0) {

                    cout << "So luong phai lon hon 0! Vui long nhap lai: ";

                    cin >> soLuongMua;

                    cin.ignore();
                }

                donHang->suaSoLuongSanPham(maSP, soLuongMua);
                
                cout << "Da cap nhat don hang!" << endl;

                break;
            case 3:
                cout << "Nhap ma san pham can xoa khoi don: "; 
                getline(cin, maSP);

                donHang->xoaSanPhamKhoiDon(maSP);

                cout << "Da xoa san pham khoi don!" << endl;

                break;
            case 4:
                cout << "Quay lai menu tong." << endl;

                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }
    } while (luaChon != 4);

}
void OrderManager::xoaDonHang() {
    cout << "\n====XOA DON HANG====" << endl;
    cout << "Nhap ma don hang can xoa: ";
    string ma; 
    getline(cin, ma);
    cin.ignore();
 
    for (auto it = dsDonHang.begin(); it != dsDonHang.end(); ++it) {
        if ((*it)->getMaDon() == ma) {
            delete *it; // Xóa giải phóng bộ nhớ cho đơn hàng

            dsDonHang.erase(it);
            *it = nullptr; 
            cout << "Xoa don hang thanh cong!" << endl;
            return;
        }
    }
    cout << "Khong tim thay ma don hang can xoa!" << endl;
}
 
void OrderManager::lietKeSanPham() const {
    cout << "\n====Danh Sach San Pham====" << endl;
    cout << left << setw(12) << "Ma SP" << setw(25) << "Ten San Pham" << setw(15) << "Gia Goc" << "Gia Ban Cuoi Cung" << endl;
    cout << "--------------------------------------------------------------------" << endl;
    for (auto p : dsSanPham) {
        p->xuatThongTin();
        cout << "--------------------------------------------------------------------" << endl;
    }
    cout << "====================================================================" << endl;
}
 
void OrderManager::lietKeDonHang() const {
    for (auto dh : dsDonHang) {
        dh->xuatThongTin();
        cout << fixed << setprecision(2);

        if (dh->getTypeId() == 1) {

            RetailOrder* ro = (RetailOrder*) dh;  

            cout << "Tong tien: " << ro->tinhTongTien(dsSanPham) << endl;
        } 
        else if (dh->getTypeId() == 2) {

            WholesaleOrder* wo = (WholesaleOrder*) dh;
            
            cout << "Tong tien (sau chiet khau): " << wo->tinhTongTien(dsSanPham) << endl;
        }
        cout << endl;
    }
}
#include "OrderManager.h"
#include <iostream>
#include <iomanip>

using namespace std;


OrderManager::OrderManager() {}

OrderManager::~OrderManager() {
    for (int i = 0; i < (int)dsSanPham.size(); i++) {

        delete dsSanPham[i];

    }
    for (int i = 0; i < (int)dsDonHang.size(); i++) {

        delete dsDonHang[i];

    }
    dsSanPham.clear();

    dsDonHang.clear();
}

void OrderManager::themSanPham() {
    cout << "\n====THEM SAN PHAM MOI====" << endl;
    cout << "1. San pham thong thuong (Co thue VAT)" << endl;
    cout << "2. San pham khuyen mai (Co muc giam)" << endl;
    
    int loai;
    while (true) {
        try {
            cout << "Lua chon loai san pham: ";

            if (!(cin >> loai)) {

                throw "Loi: Luan chon phai la so 1 hoac 2!";

            }
            if (loai != 1 && loai != 2) {

                throw "Loi: Chon sai chuc nang! Chi duoc nhap 1 hoac 2.";

            }
            
            cin.ignore();
            break;
        } 
        catch (const char* msg) {
            cout << msg << " Vui long nhap lai.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    Product* sanPhamMoi = nullptr;
    if (loai == 1) {

        sanPhamMoi = new NormalProduct();

    } 
    else if (loai == 2) {

        sanPhamMoi = new PromoProduct();

    } 
    else {

        cout << "Loai san pham khong hop le!" << endl;

        return;
    }

    sanPhamMoi->nhapThongTin();

    for (int i = 0; i < (int)dsSanPham.size(); i++) {

        if (dsSanPham[i]->getMaSp() == sanPhamMoi->getMaSp()) {

            cout << "Loi: Ma san pham nay da ton tai trong he thong!" << endl;

            delete sanPhamMoi; 

            return;
        }
    }

    
    dsSanPham.push_back(sanPhamMoi);

    cout << "Them san pham thanh cong!" << endl;
}


void OrderManager::suaSanPham() {
    cout << "\n====SUA THONG TIN SAN PHAM====" << endl;
    cout << "Nhap ma san pham can sua: ";
    string ma;
    cin >> ma;


    for (int i = 0; i < (int)dsSanPham.size(); i++) {
        if (dsSanPham[i]->getMaSp() == ma) {

            cout << "Tim thay: " << dsSanPham[i]->getTenSp()
                 << " (Gia goc hien tai: " << dsSanPham[i]->getGiaGoc() << ")" << endl;

            string tenMoi;

            double giaMoi;

            cout << "Nhap ten moi: ";

            cin.ignore();

            getline(cin, tenMoi);

            cout << "Nhap gia goc moi: ";

            cin >> giaMoi;

            dsSanPham[i]->setTenSp(tenMoi);

            dsSanPham[i]->setGiaGoc(giaMoi);

            cout << "Cap nhat san pham thanh cong!" << endl;

            return;
        }
    }
    cout << "Khong tim thay san pham voi ma tren!" << endl;
}

void OrderManager::xoaSanPham() {
    cout << "\n====XOA SAN PHAM====" << endl;
    cout << "Nhap ma san pham can xoa: ";
    string ma;
    cin >> ma;

    
    for (int i = 0; i < (int)dsDonHang.size(); i++) {

        vector<OrderDetail>& dsChiTiet = dsDonHang[i]->getDsChiTiet();

        for (int j = 0; j < (int)dsChiTiet.size(); j++) {

            if (dsChiTiet[j].getMaSp() == ma) {

                cout << "LOI: Khong the xoa! San pham dang co trong don hang: " << dsDonHang[i]->getMaDon() << endl;

                return;
            }
        }
    }


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
    cout << "\n====TAO DON HANG MOI====" << endl;
    cout << "1. Don hang Ban Le (Retail Order)" << endl;
    cout << "2. Don hang Dai Ly/Ban Buon (Wholesale Order)" << endl;
    
    int loai;
    while (true) {
        try {

            cout << "Lua chon loai don hang: ";

            if (!(cin >> loai)) {

                throw "Loi: Lua chon phai la so nguyen 1 hoac 2!";

            }
            if (loai != 1 && loai != 2) {

                throw "Loi: Chi duoc chon 1 (Le) hoac 2 (Buon)!";

            }

            cin.ignore();
            break; 
        } 
        catch (const char* msg) {
            cout << msg << " Vui long nhap lai.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

   
    Order* donHangMoi = nullptr;
    if (loai == 1) {

        donHangMoi = new RetailOrder();

    } 
    else if (loai == 2) {

        double chietKhau;

        cout << "Nhap ty le chiet khau (vi du 0.05 cho 5%): ";

        cin >> chietKhau;

        donHangMoi = new WholesaleOrder("", chietKhau);

    } 
    else {
        cout << "Loai don hang khong hop le!" << endl;
        return;
    }

    
    string maDon;
    cout << "Nhap ma don hang moi: ";
    cin >> maDon;

    for (int i = 0; i < (int)dsDonHang.size(); i++) {

        if (dsDonHang[i]->getMaDon() == maDon) {

            cout << "Loi: Ma don hang da ton tai!" << endl;

            delete donHangMoi; 

            return;
        }
    }

    donHangMoi->setMaDon(maDon);


    char tiepTuc = 'y';
    while (tiepTuc == 'y' || tiepTuc == 'Y') {
        cout << "Nhap ma san pham muon mua: ";
        string maSP;
        cin >> maSP;

       
        bool timThay = false;
        for (int i = 0; i < (int)dsSanPham.size(); i++) {

            if (dsSanPham[i]->getMaSp() == maSP) {

                timThay = true;

                break;
            }
        }

        if (timThay == false) {

            cout << "San pham khong ton tai trong kho!" << endl;

        } 
        else {
            int soLuong;
            cout << "Nhap so luong mua: ";
            cin >> soLuong;
            if (soLuong <= 0) {

                cout << "So luong phai lon hon 0!" << endl;

            } 
            else {
                
                OrderDetail chiTiet(maSP, soLuong);

                donHangMoi->themSanPhamVaoDon(chiTiet);

            }
        }

        cout << "Tiep tuc them san pham vao don nay? (y/n): ";
        cin >> tiepTuc;
    }


    dsDonHang.push_back(donHangMoi);
    cout << "Tao don hang thanh cong!" << endl;
}


void OrderManager::suaDonHang() {
    cout << "\n====SUA THONG TIN DON HANG====" << endl;
    cout << "Nhap ma don hang can sua: ";
    string maDon;
    cin >> maDon;


    Order* donHang = nullptr;
    for (int i = 0; i < (int)dsDonHang.size(); i++) {

        if (dsDonHang[i]->getMaDon() == maDon) {

            donHang = dsDonHang[i];

            break;
        }
    }


    if (donHang == nullptr) {

        cout << "Khong tim thay don hang!" << endl;

        return;
    }

    
    int luaChon;
    do {
        cout << "\n==== MENU CHINH SUA DON HANG " << maDon << " ====" << endl;
        cout << "1. Them san pham vao don" << endl;
        cout << "2. Sua so luong san pham trong don" << endl;
        cout << "3. Xoa san pham khoi don" << endl;
        cout << "4. Quay lai Menu chinh" << endl;
        cout << "Nhap lua chon (1-4): ";
        cin >> luaChon;

        string maSP;
        int soLuong;

        if (luaChon == 1) {
            
            cout << "Nhap ma san pham muon them: ";
            cin >> maSP;
           
            bool hopLe = false;
            for (int i = 0; i < (int)dsSanPham.size(); i++) {

                if (dsSanPham[i]->getMaSp() == maSP) {

                    hopLe = true;

                    break;
                }
            }
            if (hopLe == false) {

                cout << "Ma san pham khong ton tai trong kho!" << endl;

            } 
            else {
                cout << "Nhap so luong: ";
                cin >> soLuong;

                if (soLuong <= 0) {

                    cout << "So luong phai lon hon 0!" << endl;

                }
                else{

                    OrderDetail chiTiet(maSP, soLuong);
    
                    donHang->themSanPhamVaoDon(chiTiet);
    
                    cout << "Da them san pham vao don!" << endl;
                }

            }

        } 
        else if (luaChon == 2) {
            
            cout << "Nhap ma san pham can sua so luong: ";
            cin >> maSP;
            while (true){

                cout << "Nhap so luong moi: ";

                cin >> soLuong;

                if (soLuong <= 0) {
                   
                    cout << "So luong phai lon hon 0! Vui long nhap lai." << endl;

                }
                else {
                    break;
                }
            }
            
            donHang->suaSoLuongSanPham(maSP, soLuong);
            cout << "Da cap nhat so luong!" << endl;

        } 
        else if (luaChon == 3) {
            
            cout << "Nhap ma san pham can xoa khoi don: ";
            cin >> maSP;

            donHang->xoaSanPhamKhoiDon(maSP);
            cout << "Da xoa san pham khoi don!" << endl;

        } 
        else if (luaChon == 4) {
            cout << "Quay lai menu tong." << endl;

        } 
        else {
            cout << "Lua chon khong hop le!" << endl;
        }

    } while (luaChon != 4);
}


void OrderManager::xoaDonHang() {
    cout << "\n====XOA DON HANG====" << endl;
    cout << "Nhap ma don hang can xoa: ";
    string ma;
    cin >> ma;

    
    for (auto it = dsDonHang.begin(); it != dsDonHang.end(); ++it) {

        if ((*it)->getMaDon() == ma) {

            delete *it;     
                 
            dsDonHang.erase(it); 
         
            cout << "Xoa don hang thanh cong!" << endl;
            return;
        }
    }
    cout << "Khong tim thay don hang can xoa!" << endl;
}


void OrderManager::lietKeSanPham() const {
    cout << "\n=================== DANH SACH SAN PHAM TRONG KHO ===================" << endl;

    for (int i = 0; i < (int)dsSanPham.size(); i++) {

        dsSanPham[i]->xuatThongTin();

    }
}


void OrderManager::lietKeDonHang() const {
    cout << "\n=================== TOAN BO DON HANG HE THONG ===================" << endl;

   
    if (dsDonHang.empty()) {
        cout << "Hien chua co don hang nao duoc tao" << endl;
        return;
    }

    cout << fixed << setprecision(2);
    for (int i = 0; i < (int)dsDonHang.size(); i++) {
        dsDonHang[i]->xuatThongTin();
        cout << "Tong tien don hang: " << dsDonHang[i]->tinhTongTien(dsSanPham) << endl;
        cout << endl;
    }
}
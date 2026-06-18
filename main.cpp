#include <iostream>
#include "OrderManager.h"

using namespace std;

int main() {
    OrderManager manager;
    
    
    int luaChon;
    do {
        cout << "\n=================================================" << endl;
        cout << "=====HE THONG QUAN LY DON HANG=====" << endl;
        cout << "=================================================" << endl;
        cout << "1. Nhap them san pham vao kho" << endl;
        cout << "2. Sua thong tin san pham" << endl;
        cout << "3. Xoa san pham (Kiem tra rang buoc don hang)" << endl;
        cout << "4. Nhap thong tin don hang (Tao don moi)" << endl;
        cout << "5. Sua thong tin don hang (Menu con a-b-c)" << endl;
        cout << "6. Xoa don hang khoi he thong" << endl;
        cout << "7. Liet ke toan bo san pham trong kho" << endl;
        cout << "8. Liet ke toan bo don hang kem chi tiet" << endl;
        cout << "9. Thoat he thong" << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "Nhap lua chon cua ban (1-9): ";
        cin >> luaChon;
        
        switch(luaChon) {
            case 1: manager.themSanPham(); break;
            case 2: manager.suaSanPham(); break;
            case 3: manager.xoaSanPham(); break;
            case 4: manager.taoDonHang(); break;
            case 5: manager.suaDonHang(); break;
            case 6: manager.xoaDonHang(); break;
            case 7: manager.lietKeSanPham(); break;
            case 8: manager.lietKeDonHang(); break;
            case 9: 
                cout << "Thank you for using our system!" << endl; 
                break;
            default: 
                cout << "Lua chon sai! Vui long chon tu 1 den 9." << endl;
        }
    } while (luaChon != 9);
    
    return 0;
}

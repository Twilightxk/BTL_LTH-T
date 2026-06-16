#ifndef ORDERDETAIL_H
#define ORDERDETAIL_H
#include <string>
#include <iostream>
using namespace std;
class OrderDetail{
    private:
        string maSp;
        int soLuong;
    public:
        OrderDetail();

        OrderDetail(string maSp, int soLuong);

        string getMaSp() const;

        int getSoLuong() const;

        void setMaSp(string maSp);

        void setSoLuong(int soLuong);

        void input();
        
        void output();

};

#endif
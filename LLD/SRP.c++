#include<bits/stdc++.h>
using namespace std;
class Marker {
    public:
        string name, color;
        int price, year;
        Marker(){}
        Marker(string name, string color, int price, int year){
            this->name = name;
            this->color = color;
            this->price = price;
            this->year = year;
        }
};
class Invoice {
    private:
        Marker marker;
        int quantity, total;
    public:
        Invoice(){}
        Invoice(Marker marker, int quantity){
            this->marker = marker;
            this->quantity = quantity;
        }
        void calculateTotal(){
            cout<<"Calculating total..."<<endl;
            this->total = this->marker.price * this->quantity;
        }
};
class invoiceDao {
    public:
        Invoice invoice;
        invoiceDao(Invoice invoice){
            this->invoice = invoice;
        }
        void saveToDB(){
            cout<<"Saving to DB..."<<endl;
        }
};
class invoicePrinter {
    private:
        Invoice invoice;
    public:
        invoicePrinter(Invoice invoice){
            this->invoice = invoice;
        }
        void printInvoice(){
            cout<<"Printing invoice..."<<endl;
        }
};
int main(){
    Invoice invoice(Marker("name", "color", 10, 2020), 10);
    invoiceDao invoicedao(invoice);
    invoicePrinter invoiceprinter(invoice);
    invoice.calculateTotal();
    invoicedao.saveToDB();
    invoiceprinter.printInvoice();
    return 0;
}
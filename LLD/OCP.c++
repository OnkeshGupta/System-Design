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
        virtual void save() const = 0;
};
class databaseInvoice : public invoiceDao {
    private:
        Invoice invoice;
    public:
        databaseInvoice(Invoice invoice){
            this->invoice = invoice;
        }
        void save() const override {
            cout<<"Saving database information..."<<endl;
        }
};
class fileInvoice : public invoiceDao {
    private:
        Invoice invoice;
    public:
        fileInvoice(Invoice Invoice){
            this->invoice = invoice;
        }
        void save() const override {
            cout<<"Saving file information..."<<endl;
        }
};
int main(){
    Invoice invoice(Marker("name", "color", 20, 2020), 10);
    invoice.calculateTotal();
    databaseInvoice database(invoice);
    database.save();
    fileInvoice fileinvoice(invoice);
    fileinvoice.save();
    return 0;
}
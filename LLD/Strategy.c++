#include<bits/stdc++.h>
using namespace std;
class PaymentStrategy {
    public:
        virtual void pay(double amount) = 0;
};
class CreditCardPayment : public PaymentStrategy {
    private:
        string cardNumber;
    public:
        CreditCardPayment(string cardNumber){
            this->cardNumber = cardNumber;
        }
        void pay(double amount){
            cout<<"Paid $"<<amount<<" using credit card ending in "<<cardNumber.substr(cardNumber.length() - 4)<<endl;
        }
};
class PayPalPayment : public PaymentStrategy {
    private:
        string email;
    public:
        PayPalPayment(string email){
            this->email = email;
        }
        void pay(double amount){
            cout<<"Paid $"<<amount<<" using paypal account "<<email<<endl;
        }
};
class UPIPayment : public PaymentStrategy {
    private:
        string upiId;
    public:
        UPIPayment(string upiId){
            this->upiId = upiId;
        }
        void pay(double amount){
            cout<<"Paid $"<<amount<<" using UPI ID "<<upiId<<endl;
        }
};
class ShoppingCart {
    private:
        PaymentStrategy* paymentStrategy;
    public:
        void setPaymentStrategy(PaymentStrategy* strategy){
            this->paymentStrategy = strategy;
        }
        void checkout(double amount){
            cout<<"Checking out amount: $"<<amount<<endl;
            paymentStrategy->pay(amount);
        }
};
int main(){
    ShoppingCart cart;
    cart.setPaymentStrategy(new CreditCardPayment("1234-5678-9876-5432"));
    cart.checkout(100.0);
    cart.setPaymentStrategy(new PayPalPayment("xyz@gmail.com"));
    cart.checkout(200.57);
    cart.setPaymentStrategy(new UPIPayment("user@upi"));
    cart.checkout(500.57);
    return 0;
}
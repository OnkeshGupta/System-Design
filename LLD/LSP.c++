#include<bits/stdc++.h>
using namespace std;
class Bike {
    public:
        virtual void accelerate() = 0;
        virtual void applyBrakes() = 0;
};
class Engine {
    public:
        virtual void turnOnEngine() = 0;
        virtual void turnOffEngine() = 0;
};
class Motorcycle : public Bike, public Engine {
    private:
        string company;
        bool isEngineOn;
        int speed;
    public:
        Motorcycle(string company, int speed){
            this->company = company;
            this->speed = speed;
        }
        void turnOnEngine(){
            this->isEngineOn = true;
            cout<<"Engine is ON..."<<endl;
        }
        void turnOffEngine(){
            this->isEngineOn = false;
            cout<<"Engine is OFF..."<<endl;
        }
        void accelerate(){
            this->speed = this->speed + 10;
            cout<<"Motorcycle Speed: "<<this->speed<<endl;
        }
        void applyBrakes(){
            this->speed = this->speed - 10;
            cout<<"Motorcycle Speed: "<<this->speed<<endl;
        }
};
class Bicycle : public Bike {
    public:
        string brand;
        bool hasGears;
        int speed;
        Bicycle(string brand, bool hasGears, int speed){
            this->brand = brand;
            this->hasGears = hasGears;
            this->speed = speed;
        }
        void accelerate(){
            this->speed = this->speed + 10;
            cout<<"Bicycle Speed: "<<this->speed<<endl;
        }
        void applyBrakes(){
            this->speed = this->speed - 10;
            cout<<"Bicycle Speed: "<<this->speed<<endl;
        }
};
int main(){
    Motorcycle motorcycle("Honda", 250);
    Bicycle bicycle("Mogambo", true, 100);
    motorcycle.turnOnEngine();
    motorcycle.accelerate();
    motorcycle.applyBrakes();
    motorcycle.turnOffEngine();
    bicycle.accelerate();
    bicycle.applyBrakes();
    return 0;
}
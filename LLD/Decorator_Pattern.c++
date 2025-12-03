#include<bits/stdc++.h>
using namespace std;
class basePizza {
    public:
        virtual ~basePizza() = default;
        virtual string getDescription() const = 0;
        virtual double getCost() const = 0;
};
class plainPizza : public basePizza {
    public:
        string getDescription() const override {
            return "Plain Pizza";
        }
        double getCost() const override {
            return 200.0;
        }
};
class farmHouse : public basePizza {
    public:
        string getDescription() const override {
            return "FarmHouse Pizza";
        }
        double getCost() const override {
            return 300.0;
        }
};
class tandooriPaneerDelight : public basePizza {
    public:
        string getDescription() const override {
            return "Tandoori Paneer Delight Pizza";
        }
        double getCost() const override {
            return 400.0;
        }
};
class chickenDominator : public basePizza {
    public:
        string getDescription() const override {
            return "Chicken Dominator Pizza";
        }
        double getCost() const override {
            return 500.0;
        }
};
class toppingDecorator : public basePizza {
    protected:
        shared_ptr<basePizza> pizza_;
    public:
        explicit toppingDecorator(shared_ptr<basePizza> pizza) : pizza_(move(pizza)) {}
};
class extraCheeseTopping : public toppingDecorator {
    public:
        explicit extraCheeseTopping(shared_ptr<basePizza> pizza) : toppingDecorator(move(pizza)){}
        string getDescription() const override {
            return pizza_->getDescription() + " + Extra Cheese";
        }
        double getCost() const override {
            return pizza_->getCost() + 20.0;
        }
};
class veggiesTopping : public toppingDecorator {
    public:
        explicit veggiesTopping(shared_ptr<basePizza> pizza) : toppingDecorator(move(pizza)){}
        string getDescription() const override {
            return pizza_->getDescription() + " + Veggies";
        }
        double getCost() const override {
            return pizza_->getCost() + 30.0;
        }
};
class mushroomTopping : public toppingDecorator {
    public:
        explicit mushroomTopping(shared_ptr<basePizza> pizza) : toppingDecorator(move(pizza)){}
        string getDescription() const override {
            return pizza_->getDescription() + " + Mushroom";
        }
        double getCost() const override {
            return pizza_->getCost() + 40.0;
        }
};
class pepperoniTopping : public toppingDecorator {
    public:
        explicit pepperoniTopping(shared_ptr<basePizza> pizza) : toppingDecorator(move(pizza)){}
        string getDescription() const override {
            return pizza_->getDescription() + " + Pepperoni";
        }
        double getCost() const override {
            return pizza_->getCost() + 50.0;
        }
};
int main(){
    cout << "======= Decorator Design Pattern ======\n";
    shared_ptr<basePizza> pizza1 = make_shared<plainPizza>();
    cout<<"Order 1: "<<pizza1->getDescription()<<" = Rs."<<pizza1->getCost()<<endl;
    shared_ptr<basePizza> pizza2 = make_shared<extraCheeseTopping>(make_shared<plainPizza>());
    cout<<"Order 2: "<<pizza2->getDescription()<<" = Rs."<<pizza2->getCost()<<endl;
    shared_ptr<basePizza> pizza3 = make_shared<veggiesTopping>(make_shared<extraCheeseTopping>(make_shared<plainPizza>()));
    cout<<"Order 3: "<<pizza3->getDescription()<<" = Rs."<<pizza3->getCost()<<endl;
    return 0;
};
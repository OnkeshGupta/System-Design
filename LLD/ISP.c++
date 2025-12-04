#include<bits/stdc++.h>
using namespace std;
class ChefTasks {
    public:
        virtual void prepareFood() = 0;
        virtual void decideMenu() = 0;
};
class WaiterTasks {
    public:
        virtual void serveFood() = 0;
        virtual void takeOrder() = 0;
};
class Chef : public ChefTasks {
    public:
        void prepareFood(){
            cout<<"Preparing food..."<<endl;
        }
        void decideMenu(){
            cout<<"Deciding menu..."<<endl;
        }
};
class Waiter : public WaiterTasks {
    public:
        void serveFood(){
            cout<<"Serving food..."<<endl;
        }
        void takeOrder(){
            cout<<"Taking order..."<<endl;
        }
};
int main(){
    Chef chef;
    Waiter waiter;
    chef.decideMenu();
    chef.prepareFood();
    waiter.serveFood();
    waiter.takeOrder();
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// ===================== Observer interface =====================
class StockNotificationObserver {
public:
    virtual void update() = 0;
    virtual string getNotificationMethod() const = 0;
    virtual string getUserId() const = 0;

    virtual ~StockNotificationObserver() = default;
};

// ===================== Observable interface =====================
class StockAvailabilityObservable {
public:
    virtual void addStockObserver(StockNotificationObserver* observer) = 0;
    virtual void removeStockObserver(StockNotificationObserver* observer) = 0;
    virtual void notifyStockObservers() = 0;

    virtual bool purchase(int quantity) = 0;
    virtual void restock(int quantity) = 0;

    virtual ~StockAvailabilityObservable() = default;
};

// ===================== Concrete Observable =====================
class IphoneProductObservable : public StockAvailabilityObservable {
private:
    string productId;
    string productName;
    double price;
    vector<StockNotificationObserver*> stockObservers;
    int stockQuantity;

public:
    IphoneProductObservable(const string& productId,
                            const string& productName,
                            double price,
                            int stockQuantity)
        : productId(productId),
          productName(productName),
          price(price),
          stockQuantity(stockQuantity) {}

    void addStockObserver(StockNotificationObserver* observer) override {
        stockObservers.push_back(observer);
        cout << "[+] " << observer->getUserId()
             << " subscribed for notifications on " << productName << "\n";
    }

    void removeStockObserver(StockNotificationObserver* observer) override {
        stockObservers.erase(
            remove(stockObservers.begin(), stockObservers.end(), observer),
            stockObservers.end()
        );
        cout << "[-] " << observer->getUserId()
             << " unsubscribed for notifications on " << productName << "\n";
    }

    void notifyStockObservers() override {
        if (stockQuantity > 0 && !stockObservers.empty()) {
            cout << "Notifying " << stockObservers.size() << " subscribers...\n";

            // Create a copy to avoid modification while iterating
            vector<StockNotificationObserver*> observersToNotify = stockObservers;

            for (auto* observer : observersToNotify) {
                observer->update();
            }
        }
    }

    void restock(int quantity) override {
        bool wasOutOfStock = (stockQuantity == 0);
        stockQuantity += quantity;
        cout << "RESTOCKED: " << productName
             << " - Added " << quantity
             << " items | Current stock: " << stockQuantity << "\n";

        // Only notify if product was previously out of stock
        if (wasOutOfStock && stockQuantity > 0) {
            notifyStockObservers();
        }
    }

    bool purchase(int quantity) override {
        if (stockQuantity >= quantity) {
            stockQuantity -= quantity;
            cout << "PURCHASE SUCCESS: " << quantity << " units of "
                 << productName << " | Remaining stock: "
                 << stockQuantity << "\n";
            return true;
        } else {
            cout << "PURCHASE FAILED: " << productName
                 << " is out of stock! | Available Quantity: "
                 << stockQuantity << "\n";
            return false;
        }
    }

    // Getters
    string getProductId() const { return productId; }
    string getProductName() const { return productName; }
    double getPrice() const { return price; }
    int getStockQuantity() const { return stockQuantity; }
};

// ===================== Concrete Observer: Email =====================
class EmailNotificationObserver : public StockNotificationObserver {
private:
    string userId;
    string emailAddress;

public:
    EmailNotificationObserver(const string& userId,
                              const string& emailAddress)
        : userId(userId), emailAddress(emailAddress) {}

    void update() override {
        sendEmail();
    }

    void sendEmail() {
        cout << "!! EMAIL SENT to: " << emailAddress
             << " - Product is back in stock! Hurry Up!!\n";
    }

    string getNotificationMethod() const override {
        return "Email";
    }

    string getUserId() const override {
        return userId;
    }
};

// ===================== Concrete Observer: Push Notification =====================
class PushNotificationObserver : public StockNotificationObserver {
private:
    string userId;
    string deviceToken;

public:
    PushNotificationObserver(const string& userId,
                             const string& deviceToken)
        : userId(userId), deviceToken(deviceToken) {}

    void update() override {
        sendPushNotification();
    }

    void sendPushNotification() {
        cout << "!! PUSH NOTIFICATION SENT to: " << deviceToken
             << " - Product is back in stock! Hurry Up!!\n";
    }

    string getNotificationMethod() const override {
        return "Push Notification";
    }

    string getUserId() const override {
        return userId;
    }
};

// ===================== Client Code (main) =====================
int main() {
    cout << "------------------------------------------------------------\n";
    cout << "###### E-commerce Store - Stock Availability Notification Feature Demo ######\n";

    // Create an iPhone product - stock available = 10 units
    IphoneProductObservable iphoneProduct("ip15", "iPhone 15", 1250.0, 10);
    StockAvailabilityObservable& product = iphoneProduct;

    // Create observers
    PushNotificationObserver John_PUSH("John123", "JohnDeviceP1");
    PushNotificationObserver Katy_PUSH("Katy678", "KatyDeviceP2");
    EmailNotificationObserver Jane_EMAIL("Jane783", "jane783@gmail.com");
    EmailNotificationObserver George_EMAIL("George993", "george993@gmail.com");

    // Black Friday Sale - Purchase all 10 units
    product.purchase(10);

    // Stock unavailability leads to users subscribing to notifications
    bool success = product.purchase(1); // Failed purchase
    if (!success) {
        // Register observers - John, Katy, Jane, George subscribe for notifications
        product.addStockObserver(&John_PUSH);    // John
        product.addStockObserver(&Katy_PUSH);    // Katy
        product.addStockObserver(&Jane_EMAIL);   // Jane
        product.addStockObserver(&George_EMAIL); // George
    }

    // Restock 20 units of iPhone 15 (all 4 observers are notified)
    product.restock(20);

    // Users purchase upon receiving notifications
    product.purchase(1); // John purchases 1 unit
    product.purchase(1); // Katy purchases 1 unit

    // John & Katy unsubscribe from notifications
    product.removeStockObserver(&John_PUSH);
    product.removeStockObserver(&Katy_PUSH);

    // NYE Sale - All 18 units sold
    product.purchase(18);

    // Restock 5 units - Only Jane & George are notified
    product.restock(5);

    product.purchase(1); // Jane purchases 1 unit
    product.purchase(1); // George purchases 1 unit

    // Jane & George unsubscribe from notifications
    product.removeStockObserver(&Jane_EMAIL);
    product.removeStockObserver(&George_EMAIL);

    return 0;
}
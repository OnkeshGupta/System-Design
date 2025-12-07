#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

// ================= Observable (Subject) interface =================
class WeatherObserver;  // forward declaration

class WeatherObservable {
public:
    virtual void addObserver(WeatherObserver* observer) = 0;
    virtual void removeObserver(WeatherObserver* observer) = 0;
    virtual void notifyObservers() = 0;

    virtual void setWeatherReadings(float temperature, float humidity, float pressure) = 0;

    // For printing weather data (similar to toString in Java)
    virtual string toString() const = 0;

    virtual ~WeatherObservable() = default;
};

// ================= Observer interface =================
class WeatherObserver {
public:
    virtual void update() = 0;
    virtual ~WeatherObserver() = default;
};

// ================= Concrete Observable (WeatherStation) =================
class WeatherStation : public WeatherObservable {
private:
    vector<WeatherObserver*> observers;
    float temperature;
    float humidity;
    float pressure;

public:
    WeatherStation() : temperature(0), humidity(0), pressure(0) {}

    void addObserver(WeatherObserver* observer) override {
        observers.push_back(observer);
        cout << "[+] Observer registered." << endl;
    }

    void removeObserver(WeatherObserver* observer) override {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
        cout << "[-] Observer removed." << endl;
    }

    void notifyObservers() override {
        for (auto* observer : observers) {
            observer->update();
        }
    }

    void setWeatherReadings(float temperature, float humidity, float pressure) override {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        notifyObservers();
    }

    // Getters
    float getTemperature() const { return temperature; }
    float getHumidity() const { return humidity; }
    float getPressure() const { return pressure; }

    string toString() const override {
        stringstream ss;
        ss << "WeatherStation{temperature=" << temperature
           << ", humidity=" << humidity
           << ", pressure=" << pressure << "}";
        return ss.str();
    }
};

// ================= Concrete Observer 1 - CurrentConditionsDisplay =================
class CurrentConditionsDisplay : public WeatherObserver {
private:
    WeatherObservable& weatherStation;

public:
    CurrentConditionsDisplay(WeatherObservable& ws) : weatherStation(ws) {
        weatherStation.addObserver(this);
    }

    void update() override {
        cout << "Saving weather data... " << endl;
        display();
    }

    void display() {
        cout << "Current Weather Conditions: " << weatherStation.toString() << endl;
    }
};

// ================= Concrete Observer 2 - ForecastDisplay =================
class ForecastDisplay : public WeatherObserver {
private:
    WeatherObservable& weatherStation;

public:
    ForecastDisplay(WeatherObservable& ws) : weatherStation(ws) {
        weatherStation.addObserver(this);
    }

    void update() override {
        cout << "Updating weather data to do some analytics: "
             << weatherStation.toString() << endl;
        display();
    }

    void display() {
        cout << "Forecast Details: Displaying information about Rain, "
             << "Temperature Trends, Significant Weather Events and other phenomenon..."
             << endl;
    }
};

// ================= Client Code =================
int main() {
    cout << "###### Observer Design Pattern (C++) ######" << endl;

    // Create the weather station (observable/subject)
    WeatherStation ws;
    WeatherObservable& weatherStation = ws;

    // Create displays (observers)
    CurrentConditionsDisplay currentDisplay(weatherStation);
    ForecastDisplay forecastDisplay(weatherStation);

    cout << "===>>> Initial Weather Update" << endl;
    weatherStation.setWeatherReadings(80, 65, 30.4f);

    cout << "===>>> Second Weather Update" << endl;
    weatherStation.setWeatherReadings(82, 70, 29.2f);

    // Remove forecast display
    weatherStation.removeObserver(&forecastDisplay);

    cout << "===>>> Third Weather Update" << endl;
    weatherStation.setWeatherReadings(70, 21, 29.2f);
    // Forecast display will not be notified

    return 0;
}
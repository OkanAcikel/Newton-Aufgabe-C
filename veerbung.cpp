#include <iostream>
#include <string>

// Basisklasse: beschreibt allgemeine Eigenschaften eines Fahrzeugs
class Vehicle {
public:
    Vehicle(const std::string& brand)
        : brand_(brand) {}

    void honk() const {
        std::cout << "Tuut, tuut!\n";
    }

    void info() const {
        std::cout << "Fahrzeug der Marke " << brand_ << "\n";
    }

protected:
    // protected: abgeleitete Klassen koennen darauf zugreifen
    std::string brand_;
};

// Abgeleitete Klasse: ein Auto IST EIN Vehicle und erbt dessen Verhalten
class Car : public Vehicle {
public:
    // Konstruktor ruft zuerst den Basisklassen-Konstruktor auf
    Car(const std::string& brand, const std::string& model)
        : Vehicle(brand), model_(model) {}

    // Neue Methode, die es in Vehicle nicht gibt
    void drive() const {
        std::cout << "Das Auto " << brand_ << " " << model_
                  << " faehrt los.\n";
    }

    // Ueberschreibt die info()-Methode (optional)
    void info() const {
        std::cout << "Auto: " << brand_ << " " << model_ << "\n";
    }

private:
    std::string model_;
};

int main() {
    Car myCar("Toyota", "Corolla");

    // Methoden aus der Basisklasse
    myCar.honk();   // geerbt von Vehicle
    // myCar.Vehicle::info();   // so koenntest du explizit die Basisversion rufen

    // Ueberschriebene Methode der abgeleiteten Klasse
    myCar.info();

    // Eigene Methode der abgeleiteten Klasse
    myCar.drive();

    return 0;
}

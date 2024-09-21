#include <iostream>
using namespace std;

// Base class Vehicle
class Vehicle {
protected:
    string brand;
    int year;
    string fuelType;

public:
    // Constructor for Vehicle
    Vehicle(string b, int y, string f) : brand(b), year(y), fuelType(f) {}

    // Display vehicle details
    virtual void displayDetails() {
        cout << "Brand: " << brand << endl;
        cout << "Year: " << year << endl;
        cout << "Fuel Type: " << fuelType << endl;
    }
    // Virtual destructor
    virtual ~Vehicle() {}

    // Virtual method to get the model (only for derived classes)
    virtual string getModel() const {
        return "";
    }
};

// Derived class Car from Vehicle
class Car : public Vehicle {
    string model;
    int numberOfDoors;

public:
    // Constructor for Car
    Car(string b, int y, string f, string m, int doors)
        : Vehicle(b, y, f), model(m), numberOfDoors(doors) {}

    // Display car details
    void displayDetails() override {
        Vehicle::displayDetails();
        cout << "Model: " << model << endl;
        cout << "Number of Doors: " << numberOfDoors << endl;
    }

    // Override to return the model of the car
    string getModel() const override {
        return model;
    }
};

// Vehicle Management System
class VehicleManager {
    Vehicle* vehicles[10];  // Array of pointers to hold up to 10 vehicles
    int vehicleCount;       // Keep track of how many vehicles are added

public:
    // Constructor
    VehicleManager() : vehicleCount(0) {}

    // Add vehicle to the list
    void addVehicle(Vehicle* v) {
        if (vehicleCount < 10) {
            vehicles[vehicleCount++] = v;
        } else {
            cout << "No more space to add vehicles." << endl;
        }
    }

    // Display all vehicles
    void displayAllVehicles() {
        for (int i = 0; i < vehicleCount; i++) {
            vehicles[i]->displayDetails();
            cout << "------------------" << endl;
        }
    }

    // Search for a vehicle by model
    bool searchVehicleByModel(const string& model) {
        for (int i = 0; i < vehicleCount; i++) {
            if (vehicles[i]->getModel() == model) {
                cout << "Vehicle with model '" << model << "' found!" << endl;
                vehicles[i]->displayDetails();
                return true;
            }
        }
        cout << "Vehicle with model '" << model << "' not found." << endl;
        return false;
    }

    // Destructor to clean up dynamically allocated vehicles
    ~VehicleManager() {
        for (int i = 0; i < vehicleCount; i++) {
            delete vehicles[i];
        }
    }
};

int main() {
    VehicleManager manager;
    int numVehicles;

    // Search option before adding cars
    string searchModel;
    cout << "Do you want to search for a vehicle model before adding new cars? (yes/no): ";
    string searchOption;
    cin >> searchOption;

    if (searchOption == "yes") {
        cout << "Enter a car model to search for: ";
        cin >> searchModel;
        manager.searchVehicleByModel(searchModel);
    }

    cout << "How many vehicles would you like to add? (max 10): ";
    cin >> numVehicles;

    if (numVehicles > 10) numVehicles = 10;

    for (int i = 0; i < numVehicles; i++) {
        string brand, fuelType, model;
        int year, doors;

        cout << "\nEnter details for vehicle " << i + 1 << ":\n";
        cout << "Brand: ";
        cin >> brand;
        cout << "Year: ";
        cin >> year;
        cout << "Fuel Type: ";
        cin >> fuelType;
        cout << "Model: ";
        cin >> model;
        cout << "Number of Doors: ";
        cin >> doors;

        // Add car to the system
        manager.addVehicle(new Car(brand, year, fuelType, model, doors));
    }

    // Display all vehicles
    cout << "\nVehicle Inventory:\n";
    manager.displayAllVehicles();

char choice;
do {
    cout << "\nEnter a car model to search for: ";
    cin >> searchModel;

    bool found = manager.searchVehicleByModel(searchModel);

    // If not found, ask if the user wants to search again
    if (!found) {
        cout << "\nDo you want to search for another model? (y/n): ";
        cin >> choice;
    } else {
        // Exit loop if the vehicle is found
        break;
    }

} while (choice == 'y' || choice == 'Y');

    return 0;
}

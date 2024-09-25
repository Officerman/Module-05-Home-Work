#include <iostream>
#include <memory>
#include <string>


class IVehicle {
public:
    virtual void Drive() = 0;  // Чисто виртуальный метод для движения
    virtual void Refuel() = 0; // Для заправки
    virtual ~IVehicle() {}
};


class Car : public IVehicle {
    std::string make, model, fuelType;

public:
    Car(const std::string& make, const std::string& model, const std::string& fuelType)
        : make(make), model(model), fuelType(fuelType) {}

    void Drive() override {
        std::cout << "Driving a car (" << make << " " << model << ") running on " << fuelType << "." << std::endl;
    }

    void Refuel() override {
        std::cout << "Refueling car with " << fuelType << "." << std::endl;
    }
};


class Motorcycle : public IVehicle {
    std::string type;
    int engineCapacity;

public:
    Motorcycle(const std::string& type, int engineCapacity)
        : type(type), engineCapacity(engineCapacity) {}

    void Drive() override {
        std::cout << "Riding a " << type << " motorcycle with " << engineCapacity << "cc engine." << std::endl;
    }

    void Refuel() override {
        std::cout << "Refueling motorcycle with petrol." << std::endl;
    }
};


class Truck : public IVehicle {
    int loadCapacity, numberOfAxles;

public:
    Truck(int loadCapacity, int numberOfAxles)
        : loadCapacity(loadCapacity), numberOfAxles(numberOfAxles) {}

    void Drive() override {
        std::cout << "Driving a truck with " << loadCapacity << " tons capacity and " << numberOfAxles << " axles." << std::endl;
    }

    void Refuel() override {
        std::cout << "Refueling truck with diesel." << std::endl;
    }
};


class Bus : public IVehicle {
    int passengerCapacity;

public:
    Bus(int passengerCapacity) : passengerCapacity(passengerCapacity) {}

    void Drive() override {
        std::cout << "Driving a bus with capacity of " << passengerCapacity << " passengers." << std::endl;
    }

    void Refuel() override {
        std::cout << "Refueling bus with diesel." << std::endl;
    }
};


class VehicleFactory {
public:
    virtual std::unique_ptr<IVehicle> CreateVehicle() = 0; // Фабричный метод
    virtual ~VehicleFactory() {}
};


class CarFactory : public VehicleFactory {
    std::string make, model, fuelType;

public:
    CarFactory(const std::string& make, const std::string& model, const std::string& fuelType)
        : make(make), model(model), fuelType(fuelType) {}

    std::unique_ptr<IVehicle> CreateVehicle() override {
        return std::make_unique<Car>(make, model, fuelType);
    }
};


class MotorcycleFactory : public VehicleFactory {
    std::string type;
    int engineCapacity;

public:
    MotorcycleFactory(const std::string& type, int engineCapacity)
        : type(type), engineCapacity(engineCapacity) {}

    std::unique_ptr<IVehicle> CreateVehicle() override {
        return std::make_unique<Motorcycle>(type, engineCapacity);
    }
};


class TruckFactory : public VehicleFactory {
    int loadCapacity, numberOfAxles;

public:
    TruckFactory(int loadCapacity, int numberOfAxles)
        : loadCapacity(loadCapacity), numberOfAxles(numberOfAxles) {}

    std::unique_ptr<IVehicle> CreateVehicle() override {
        return std::make_unique<Truck>(loadCapacity, numberOfAxles);
    }
};


class BusFactory : public VehicleFactory {
    int passengerCapacity;

public:
    BusFactory(int passengerCapacity) : passengerCapacity(passengerCapacity) {}

    std::unique_ptr<IVehicle> CreateVehicle() override {
        return std::make_unique<Bus>(passengerCapacity);
    }
};


void CreateVehicleByUserInput() {
    std::string vehicleType;
    std::cout << "Enter vehicle type (Car, Motorcycle, Truck, Bus): ";
    std::cin >> vehicleType;

    std::unique_ptr<VehicleFactory> factory;

    if (vehicleType == "Car") {
        std::string make, model, fuelType;
        std::cout << "Enter make: ";
        std::cin >> make;
        std::cout << "Enter model: ";
        std::cin >> model;
        std::cout << "Enter fuel type: ";
        std::cin >> fuelType;
        factory = std::make_unique<CarFactory>(make, model, fuelType);

    } else if (vehicleType == "Motorcycle") {
        std::string type;
        int engineCapacity;
        std::cout << "Enter motorcycle type (sport, touring): ";
        std::cin >> type;
        std::cout << "Enter engine capacity: ";
        std::cin >> engineCapacity;
        factory = std::make_unique<MotorcycleFactory>(type, engineCapacity);

    } else if (vehicleType == "Truck") {
        int loadCapacity, numberOfAxles;
        std::cout << "Enter load capacity in tons: ";
        std::cin >> loadCapacity;
        std::cout << "Enter number of axles: ";
        std::cin >> numberOfAxles;
        factory = std::make_unique<TruckFactory>(loadCapacity, numberOfAxles);

    } else if (vehicleType == "Bus") {
        int passengerCapacity;
        std::cout << "Enter passenger capacity: ";
        std::cin >> passengerCapacity;
        factory = std::make_unique<BusFactory>(passengerCapacity);

    } else {
        std::cout << "Unknown vehicle type!" << std::endl;
        return;
    }

    auto vehicle = factory->CreateVehicle();
    vehicle->Drive();
    vehicle->Refuel();
}

int main() {
    CreateVehicleByUserInput();
    return 0;
}

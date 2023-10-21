#include <jsoncpp/json/json.h>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream> 
#include <iomanip> 
#include <time.h>
#include <stdint.h>
#include <stdio.h>

using namespace std;

Json::Value getCarRecords() {
    ifstream ifs("cars.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);
    return obj;
}

int getNumRecords() {
    Json::Value carRecords = getCarRecords();
    int numCars = carRecords.size();
    return numCars;
}

void setCarRecords(Json::Value val) {
    ofstream ofile;
    ofile.open("cars.json");
    ofile << val;
    ofile.close();
}

void addCar() {
    string carNumber, id, model, name, rentPrice;

    id = to_string(getNumRecords());
    carNumber = "C1";
    for (int i = 3; i > id.size(); i--) {
        carNumber += "0";
    }
    carNumber += id;

    cout << carNumber;
    cout << endl;
    cout << "----- Enter Car Details -----" << endl;
    cout << "Enter Brand Name: ";
    cin >> name;
    cout << "Enter Model: ";
    cin >> model;
    cout << "Enter Rent Price: ";
    cin >> rentPrice;

    Json::Value newRecord;
    newRecord["carNumber"] = carNumber;
    newRecord["id"] = id;
    newRecord["model"] = model;
    newRecord["name"] = name;
    newRecord["rentPrice"] = rentPrice;

    Json::Value records = getCarRecords();
    records.append(newRecord);
    setCarRecords(records);

    cout << endl;
    cout << "Car added" << endl;
}

void updateCarDetails() {
    string carNumber;
    cout << "Enter car number to change: ";
    cin >> carNumber;

    Json::Value records = getCarRecords();
    int numRecords = getNumRecords();
    carNumber.erase(0, 2);
    int carNum = stoi(carNumber);
    
    string name, model, rentPrice;
    cout << "New Name: ";
    cin >> name;
    cout << "New Model: ";
    cin >> model;
    cout << "New Rent Price: ";
    cin >> rentPrice;

    records[carNum]["name"] = name;
    records[carNum]["model"] = model;
    records[carNum]["rentPrice"] = rentPrice;

    setCarRecords(records);
}

void fixCarNums() {
    Json::Value records = getCarRecords();
    int numRecords = getNumRecords();

    Json::Value newRecords;

    for (int i = 0; i < numRecords; i++) {
        string id = to_string(i);
        records[i]["id"] = id;
        string carNumber = "C1";
        for (int i = 3; i > id.size(); i--) {
            carNumber += "0";
        }
        carNumber += id;
        records[i]["carNumber"] = carNumber;
        newRecords.append(records[i]);
    }

    setCarRecords(newRecords);
}

void removeCar() {
    string carNumber;
    cout << "Enter car number to remove: ";
    cin >> carNumber;

    Json::Value records = getCarRecords();
    int numRecords = getNumRecords();

    Json::Value newRecords;
    for (int i = 0; i < numRecords; i++) {
        if (records[i]["carNumber"] != carNumber) {
            newRecords.append(records[i]);
        }
    }

    setCarRecords(newRecords);
}

Json::Value getRentRecords() {
    ifstream ifs("rents.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);
    return obj;
}

int getNumRents() {
    Json::Value rentRecords = getRentRecords();
    int numRents = rentRecords.size();
    return numRents;
}

void setRentRecords(Json::Value val) {
    ofstream ofile;
    ofile.open("rents.json");
    ofile << val;
    ofile.close();
}

string getCurrentDate() {
    auto r = chrono::system_clock::now();
    auto in_time_t = chrono::system_clock::to_time_t(r);
    stringstream ss;
    ss << put_time(localtime(&in_time_t), "%d-%m-%Y");
    cout << ss.str() << endl;
    return ss.str();
}

void rentCar() {
    Json::Value car, renter;
    string carNumber;
    int id = getNumRents();
    string startDate = getCurrentDate();
    string endDate;
    string address, name, phone;
    Json::Value records = getRentRecords();

    cout << endl;
    cout << "----- Rent Car -----" << endl;
    cout << "Enter car number: ";
    cin >> carNumber;
    cout << "Enter return date: ";
    cin >> endDate;
    cout << "Enter city: ";
    cin >> address;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter phone number: ";
    cin >> phone;

    Json::Value newRecord;
    car["carNumber"] = carNumber;
    renter["address"] = address;
    renter["name"] = name;
    renter["phone"] = phone;

    newRecord["car"] = car;
    newRecord["id"] = id;
    newRecord["rentEndDate"] = endDate;
    newRecord["rentStartDate"] = startDate;
    newRecord["renter"] = renter;

    records.append(newRecord);
    setRentRecords(records);
}

void callFunction(int i) {
    cout << endl;
    switch (i) {
        case 1:
        cout << getCarRecords();
        break;
        case 2:
        addCar();
        break;
        case 3:
        updateCarDetails();
        break;
        case 4:
        removeCar();
        break;
        case 5:
        rentCar();
        break;
    }
}

void CLI() {
    cout << endl;
    cout << "----- Car Rental System -----" << endl;
    cout << "1. List all cars" << endl;
    cout << "2. Add car" << endl;
    cout << "3. Update car details" << endl;
    cout << "4. Remove car" << endl;
    cout << "5. Rent car" << endl;
}

// Main function
int main() {
    rentCar();
}

#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class ParkingSlot {
private:
    int slotNumber;
    bool isOccupied;
    string vehicleNumber;
    string vehicleType;

public:
    ParkingSlot(int number) {
        slotNumber = number;
        isOccupied = false;
        vehicleNumber = "";
        vehicleType = "";
    }

    void parkVehicle(const string& vNumber, const string& vType) {
        isOccupied = true;
        vehicleNumber = vNumber;
        vehicleType = vType;
    }

    void removeVehicle() {
        isOccupied = false;
        vehicleNumber = "";
        vehicleType = "";
    }

    bool getOccupiedStatus() const {
        return isOccupied;
    }

    int getSlotNumber() const {
        return slotNumber;
    }

    string getVehicleNumber() const {
        return vehicleNumber;
    }

    string getVehicleType() const {
        return vehicleType;
    }

    void displaySlotInfo() const {
        cout << "Slot " << slotNumber << ": ";
        if (isOccupied) {
            cout << "Occupied by " << vehicleType << " (" << vehicleNumber << ")";
        } else {
            cout << "Available";
        }
        cout << endl;
    }
};

class ParkingLot {
private:
    vector<ParkingSlot> slots;
    int totalSlots;
    int availableSlots;

public:
    ParkingLot(int total) {
        totalSlots = total;
        availableSlots = total;
       
        for (int i = 1; i <= totalSlots; i++) {
            slots.push_back(ParkingSlot(i));
        }
    }

    int findAvailableSlot() {
        for (const auto& slot : slots) {
            if (!slot.getOccupiedStatus()) {
                return slot.getSlotNumber();
            }
        }
        return -1;
    }

    bool parkVehicle(const string& vehicleNumber, const string& vehicleType) {
        if (availableSlots == 0) {
            cout << "Sorry, parking lot is full!" << endl;
            return false;
        }

        int slotNumber = findAvailableSlot();
        if (slotNumber != -1) {
            slots[slotNumber - 1].parkVehicle(vehicleNumber, vehicleType);
            availableSlots--;
            cout << "Vehicle parked successfully at slot " << slotNumber << endl;
            return true;
        }
        return false;
    }

    bool removeVehicle(int slotNumber) {
        if (slotNumber < 1 || slotNumber > totalSlots) {
            cout << "Invalid slot number!" << endl;
            return false;
        }

        if (!slots[slotNumber - 1].getOccupiedStatus()) {
            cout << "Slot " << slotNumber << " is already empty!" << endl;
            return false;
        }

        cout << "Vehicle " << slots[slotNumber - 1].getVehicleNumber()
             << " removed from slot " << slotNumber << endl;
        slots[slotNumber - 1].removeVehicle();
        availableSlots++;
        return true;
    }

    bool removeVehicle(const string& vehicleNumber) {
        for (auto& slot : slots) {
            if (slot.getOccupiedStatus() && slot.getVehicleNumber() == vehicleNumber) {
                cout << "Vehicle " << vehicleNumber << " removed from slot "
                     << slot.getSlotNumber() << endl;
                slot.removeVehicle();
                availableSlots++;
                return true;
            }
        }
        cout << "Vehicle " << vehicleNumber << " not found in parking lot!" << endl;
        return false;
    }

    void displayParkingStatus() {
        cout << "\n=== PARKING LOT STATUS ===" << endl;
        cout << "Total Slots: " << totalSlots << endl;
        cout << "Available Slots: " << availableSlots << endl;
        cout << "Occupied Slots: " << (totalSlots - availableSlots) << endl;
        cout << "\nSlot Details:" << endl;
       
        for (const auto& slot : slots) {
            slot.displaySlotInfo();
        }
        cout << "==========================\n" << endl;
    }

    void displayAvailableSlots() {
        cout << "\n=== AVAILABLE SLOTS ===" << endl;
        bool found = false;
        for (const auto& slot : slots) {
            if (!slot.getOccupiedStatus()) {
                cout << "Slot " << slot.getSlotNumber() << " is available" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No available slots!" << endl;
        }
        cout << "=======================\n" << endl;
    }

    void displayOccupiedSlots() {
        cout << "\n=== OCCUPIED SLOTS ===" << endl;
        bool found = false;
        for (const auto& slot : slots) {
            if (slot.getOccupiedStatus()) {
                cout << "Slot " << slot.getSlotNumber() << ": "
                     << slot.getVehicleType() << " (" << slot.getVehicleNumber() << ")" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No occupied slots!" << endl;
        }
        cout << "======================\n" << endl;
    }
};

string getInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayMenu() {
    cout << "\n=== PARKING ALLOCATOR SYSTEM ===" << endl;
    cout << "1. Park Vehicle" << endl;
    cout << "2. Remove Vehicle by Slot Number" << endl;
    cout << "3. Remove Vehicle by Vehicle Number" << endl;
    cout << "4. Display Parking Status" << endl;
    cout << "5. Display Available Slots" << endl;
    cout << "6. Display Occupied Slots" << endl;
    cout << "7. Clear All Vehicles" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice (1-8): ";
}

int main() {
    int totalSlots;
    cout << "=== WELCOME TO PARKING ALLOCATOR SYSTEM ===" << endl;
    cout << "Enter total number of parking slots: ";
    cin >> totalSlots;
    clearInputBuffer();

    ParkingLot parkingLot(totalSlots);
    int choice;
    string vehicleNumber, vehicleType;
    int slotNumber;

    do {
        displayMenu();
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 1:
                vehicleNumber = getInput("Enter vehicle number: ");
                vehicleType = getInput("Enter vehicle type (Car/Bike/Truck): ");
                parkingLot.parkVehicle(vehicleNumber, vehicleType);
                break;

            case 2:
                cout << "Enter slot number to remove vehicle from: ";
                cin >> slotNumber;
                clearInputBuffer();
                parkingLot.removeVehicle(slotNumber);
                break;

            case 3:
                vehicleNumber = getInput("Enter vehicle number to remove: ");
                parkingLot.removeVehicle(vehicleNumber);
                break;

            case 4:
                parkingLot.displayParkingStatus();
                break;

            case 5:
                parkingLot.displayAvailableSlots();
                break;

            case 6:
                parkingLot.displayOccupiedSlots();
                break;

            case 7:
             
                {
                    ParkingLot newLot(totalSlots);
                    parkingLot = newLot;
                    cout << "All vehicles cleared from parking lot!" << endl;
                }
                break;

            case 8:
                cout << "Thank you for using Parking Allocator System. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }

    } while (choice != 8);

    return 0;
} tell me what can I write about this projects of Parking Allocater System for my CV in best way

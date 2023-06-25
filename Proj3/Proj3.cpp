/*********************************************************
/* File: Proj3.cpp
/* Name: Elijah Harris
/* Date: 6/18/23
/* Description: This C++ code reads an input file containing a list of purchased items,
allows the user to search for specific items and view their frequencies, and provides
options to print the frequency list and a text-based histogram. It also saves the
frequency data to a backup file upon program exit.
//*********************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <map>

class ItemTracker {
private:
    std::map<std::string, int> frequencyData;  // Private member variable to store item-frequency pairs

public:
    // Function to read data file and populate frequencyData
    void readDataFile(const std::string& filename) {
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            std::string item;
            while (inFile >> item) {
                ++frequencyData[item];
            }
            inFile.close();
            std::cout << "Data file loaded successfully." << std::endl;
        }
        else {
            std::cout << "Unable to open data file. Exiting program." << std::endl;
            exit(1);
        }
    }

    // Function to search for an item and return its frequency
    int searchItem(const std::string& item) {
        auto it = frequencyData.find(item);
        if (it != frequencyData.end()) {
            return it->second;
        }
        return 0;
    }

    // Function to print the frequency list
    void printFrequencyList() {
        for (const auto& pair : frequencyData) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    }

    // Function to print the histogram
    void printHistogram() {
        for (const auto& pair : frequencyData) {
            std::cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                std::cout << "*";
            }
            std::cout << std::endl;
        }
    }

    // Function to save frequency data to backup file
    void saveBackupData() {
        std::ofstream outFile("frequency.dat");
        if (outFile.is_open()) {
            for (const auto& pair : frequencyData) {
                outFile << pair.first << " " << pair.second << std::endl;
            }
            outFile.close();
            std::cout << "Frequency data saved to backup file: frequency.dat" << std::endl;
        }
        else {
            std::cout << "Unable to create backup file." << std::endl;
        }
    }
};

int main() {
    ItemTracker tracker;
    tracker.readDataFile("CS210_Project_Three_Input_File.txt");  // Read data file and populate frequencyData

    int choice;
    while (true) {
        std::cout << "\n--- Menu ---" << std::endl;
        std::cout << "1. Search for an item" << std::endl;
        std::cout << "2. Print frequency list" << std::endl;
        std::cout << "3. Print histogram" << std::endl;
        std::cout << "4. Exit and save data" << std::endl;

        std::cout << "\nEnter your choice (1-4): ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string searchItem;
            std::cout << "Enter the item to search: ";
            std::cin >> searchItem;
            int frequency = tracker.searchItem(searchItem);  // Search for item and get its frequency
            std::cout << "Frequency of " << searchItem << ": " << frequency << std::endl;
            break;
        }
        case 2:
            std::cout << "\n--- Frequency List ---" << std::endl;
            tracker.printFrequencyList();  // Print the frequency list
            break;
        case 3:
            std::cout << "\n--- Histogram ---" << std::endl;
            tracker.printHistogram();  // Print the histogram
            break;
        case 4:
            tracker.saveBackupData();  // Save frequency data to backup file
            std::cout << "Exiting program." << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Try again." << std::endl;
        }
    }

    return 0;
}

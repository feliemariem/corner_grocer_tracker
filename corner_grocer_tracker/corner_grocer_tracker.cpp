/*
 * corner_grocer_tracker.cpp
 *
 *  Date: 12/15/2024
 *  Author: Felie Marie Magbanua
 */

#include <iostream>  // Include iostream for input/output operations
#include <fstream>   // Include fstream for file reading and writing
#include <map>       // Include map to store and track item frequencies
#include <string>    // Include string to handle text data
#include <iomanip>   // Include iomanip for formatted output
using namespace std;

/**
 * Class to track the frequency of grocery items.
 * Provides functionalities to:
 * - Read item data from a file
 * - Search for item frequency
 * - Display all frequencies
 * - Generate a histogram
 * - Write item frequencies to a backup file
 */
class ItemTracker {
private:
    map<string, int> itemFrequency; // Map to store item names and their counts

public:
    /**
     * Constructor: Reads input data from the specified file and populates the item frequency map.
     * Also creates a backup file 'frequency.dat' with the same data.
     * Parameter: inputFile - A string representing the input file name.
     */
    ItemTracker(const string& inputFile) {
        ifstream inFile(inputFile);  // Input file stream to read item data
        string item;                 // Variable to store each item read from the file

        // Check if the input file can be opened successfully
        if (!inFile.is_open()) {
            cerr << "Error: Could not open file " << inputFile << endl;
            exit(1); // Exit the program with error code 1
        }

        // Read items from the input file and update their frequencies in the map
        while (inFile >> item) {
            itemFrequency[item]++; // Increment the count for each item
        }
        inFile.close(); // Close the input file

        // Write data to a backup file
        WriteToBackupFile("frequency.dat");
    }

    /**
     * Function to get the frequency of a specific item.
     * Parameter: item - A string representing the item name.
     * Return: An integer representing the frequency of the item.
     */
    int GetItemFrequency(const string& item) {
        if (itemFrequency.find(item) != itemFrequency.end()) {
            return itemFrequency[item];
        }
        return 0; // Return 0 if the item is not found
    }

    /**
     * Function to display all items and their frequencies.
     */
    void DisplayAllFrequencies() {
        cout << "Item Frequencies:" << endl;
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl; // Output item and frequency
        }
    }

    /**
     * Function to display a histogram of item frequencies.
     * Each item is followed by '*' characters corresponding to its frequency.
     */
    void DisplayHistogram() {
        cout << "\nHistogram:\n";
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " "; // Print item name
            for (int i = 0; i < pair.second; ++i) {
                cout << "*"; // Print '*' for each count
            }
            cout << endl;
        }
    }

    /**
     * Function to write item frequencies to a backup file.
     * Parameter: backupFile - A string representing the backup file name.
     */
    void WriteToBackupFile(const string& backupFile) {
        ofstream outFile(backupFile); // Output file stream to write data to a file
        if (!outFile.is_open()) {
            cerr << "Error: Could not open backup file." << endl;
            exit(1); // Exit the program with error code 1
        }

        // Write each item and its frequency to the file
        for (const auto& pair : itemFrequency) {
            outFile << pair.first << " " << pair.second << endl;
        }
        outFile.close(); // Close the output file
    }
};

int main() {
    // Create an ItemTracker object and load data from the input file
    ItemTracker tracker("grocery_items_input.txt");
    int choice;       // Variable to store user's menu choice
    string itemName;  // Variable to store user input for item name

    // Display the menu and process user input
    do {
        cout << "\n--- Corner Grocer Menu ---\n";
        cout << "1. Search for an item\n";
        cout << "2. Display all item frequencies\n";
        cout << "3. Display histogram of item frequencies\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; // Read user choice

        switch (choice) {
        case 1:
            cin.ignore(); // Clear the input buffer
            cout << "Enter item name: ";
            getline(cin, itemName); // Get the item name from the user
            cout << "Frequency of " << itemName << ": "
                << tracker.GetItemFrequency(itemName) << endl; // Display item frequency
            break;

        case 2:
            tracker.DisplayAllFrequencies(); // Display all item frequencies
            break;

        case 3:
            tracker.DisplayHistogram(); // Display histogram of item frequencies
            break;

        case 4:
            cout << "Exiting the program. Goodbye!" << endl; // Exit message
            break;

        default:
            cout << "Invalid choice. Please try again." << endl; // Handle invalid menu choice
            break;
        }
    } while (choice != 4); // Continue until the user chooses to exit

    return 0; // Return 0 to indicate successful program execution
}

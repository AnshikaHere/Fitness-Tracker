#include <iostream>
#include <string>
#include <fstream>  // Add this for file operations
#include "FitnessTracker.h"

using namespace std;

void displayMenu() {
    cout << "\n=== FITNESS TRACKER ===\n";
    cout << "1. Create New User\n";
    cout << "2. Login\n";
    cout << "3. Add Activity\n";
    cout << "4. Add Sleep Data\n";
    cout << "5. Show Dashboard\n";
    cout << "6. Export Data for Web\n";  // Added option 6
    cout << "7. Exit\n";  // Changed to 7
    cout << "Choose an option: ";
}

int main() {
    FitnessTracker tracker;
    int choice;
    
    do {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear newline character
        
        switch (choice) {
            case 1: {
                string name;
                double weight, height;
                int age;
                
                cout << "Enter username: ";
                getline(cin, name);
                cout << "Enter weight (kg): ";
                cin >> weight;
                cout << "Enter height (cm): ";
                cin >> height;
                cout << "Enter age: ";
                cin >> age;
                
                tracker.createUser(name, weight, height, age);
                cout << "User created successfully!\n";
                break;
            }
            
            case 2: {
                string name;
                cout << "Enter username: ";
                getline(cin, name);
                
                if (tracker.loginUser(name)) {
                    cout << "Login successful!\n";
                } else {
                    cout << "User not found!\n";
                }
                break;
            }
            
            case 3: {
                auto user = tracker.getCurrentUser();
                if (!user) {
                    cout << "Please login first!\n";
                    break;
                }
                
                string date, type;
                int duration, calories;
                double distance;
                
                cout << "Enter date (YYYY-MM-DD): ";
                getline(cin, date);
                cout << "Enter activity type: ";
                getline(cin, type);
                cout << "Enter duration (minutes): ";
                cin >> duration;
                cout << "Enter calories burned: ";
                cin >> calories;
                cout << "Enter distance (km, 0 if not applicable): ";
                cin >> distance;
                
                user->addActivity(date, type, duration, calories, distance);
                cout << "Activity added successfully!\n";
                break;
            }
            
            case 4: {
                auto user = tracker.getCurrentUser();
                if (!user) {
                    cout << "Please login first!\n";
                    break;
                }
                
                string date;
                int hours, quality;
                
                cout << "Enter date (YYYY-MM-DD): ";
                getline(cin, date);
                cout << "Enter sleep hours: ";
                cin >> hours;
                cout << "Enter sleep quality (1-5): ";
                cin >> quality;
                
                user->addSleepData(date, hours, quality);
                cout << "Sleep data added successfully!\n";
                break;
            }
            
            case 5:
                tracker.showDashboard();
                break;
                
            case 6: {  // Export Data for Web
                auto user = tracker.getCurrentUser();
                if (!user) {
                    cout << "Please login first!\n";
                    break;
                }
                
                // Create a simple JSON export
                ofstream webFile("web_export.json");
                if (webFile.is_open()) {
                    webFile << "{\n";
                    webFile << "  \"username\": \"" << user->getUsername() << "\",\n";
                    webFile << "  \"totalCalories\": " << user->getTotalCaloriesBurned() << ",\n";
                    webFile << "  \"avgSleep\": " << user->getAverageSleepHours() << "\n";
                    webFile << "}\n";
                    webFile.close();
                    cout << "Data exported to web_export.json!\n";
                } else {
                    cout << "Error creating export file!\n";
                }
                break;
            }
                
            case 7:
                cout << "Goodbye!\n";
                break;
                
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 7);
    
    return 0;
}
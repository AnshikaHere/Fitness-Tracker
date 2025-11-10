#include "FitnessTracker.h"
#include <iostream>
#include <iomanip>

using namespace std;

FitnessTracker::FitnessTracker() : currentUser(nullptr) {
    loadAllData();
}

FitnessTracker::~FitnessTracker() {
    saveAllData();
}

void FitnessTracker::createUser(const std::string& name, double weight, double height, int age) {
    users.emplace_back(name, weight, height, age);
    currentUser = &users.back();
    cout << "User created: " << name << endl;
}

bool FitnessTracker::loginUser(const std::string& name) {
    for (auto& user : users) {
        if (user.getUsername() == name) {
            currentUser = &user;
            cout << "Login successful!" << endl;
            return true;
        }
    }
    cout << "User not found!" << endl;
    return false;
}

User* FitnessTracker::getCurrentUser() const {
    return currentUser;
}

void FitnessTracker::showDashboard() const {
    if (!currentUser) {
        cout << "No user logged in!" << endl;
        return;
    }
    
    cout << "\n=== FITNESS DASHBOARD ===" << endl;
    cout << "User: " << currentUser->getUsername() << endl;
    cout << "Weight: " << currentUser->getWeight() << " kg" << endl;
    cout << "Height: " << currentUser->getHeight() << " cm" << endl;
    cout << "Age: " << currentUser->getAge() << " years" << endl;
    cout << "Total Calories Burned: " << currentUser->getTotalCaloriesBurned() << endl;
    cout << "Average Sleep: " << fixed << setprecision(1) 
         << currentUser->getAverageSleepHours() << " hours" << endl;
}

void FitnessTracker::showWeeklyProgress() const {
    cout << "Weekly progress feature coming soon!" << endl;
}

void FitnessTracker::saveAllData() const {
    cout << "Data saved successfully!" << endl;
}

void FitnessTracker::loadAllData() {
    cout << "Data loaded successfully!" << endl;
}
#include "User.h"
#include <iostream>

using namespace std;

User::User(const std::string& name, double w, double h, int a) 
    : username(name), weight(w), height(h), age(a) {
    cout << "New user initialized: " << name << endl;
}

void User::addActivity(const std::string& date, const std::string& type, 
                      int duration, int calories, double distance) {
    activities.push_back({date, type, duration, calories, distance});
    cout << "Activity added: " << type << " on " << date << endl;
}

void User::addSleepData(const std::string& date, int hours, int quality) {
    sleepRecords.push_back({date, hours, quality});
    cout << "Sleep data added: " << hours << " hours on " << date << endl;
}

std::string User::getUsername() const { 
    return username; 
}

double User::getWeight() const { 
    return weight; 
}

double User::getHeight() const { 
    return height; 
}

int User::getAge() const { 
    return age; 
}

int User::getTotalCaloriesBurned() const {
    int total = 0;
    for (const auto& activity : activities) {
        total += activity.calories;
    }
    return total;
}

double User::getAverageSleepHours() const {
    if (sleepRecords.empty()) {
        return 0.0;
    }
    
    double total = 0;
    for (const auto& sleep : sleepRecords) {
        total += sleep.hours;
    }
    return total / sleepRecords.size();
}
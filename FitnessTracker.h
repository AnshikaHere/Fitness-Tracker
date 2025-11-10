#ifndef FITNESS_TRACKER_H
#define FITNESS_TRACKER_H

#include "User.h"
#include <vector>
#include <string>

class FitnessTracker {
private:
    std::vector<User> users;
    User* currentUser;

public:
    FitnessTracker();
    ~FitnessTracker();
    
    void createUser(const std::string& name, double weight, double height, int age);
    bool loginUser(const std::string& name);
    User* getCurrentUser() const;
    
    void showDashboard() const;
    void showWeeklyProgress() const;
    
    void saveAllData() const;
    void loadAllData();
};

#endif
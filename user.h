#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

struct Activity {
    std::string date;
    std::string type;
    int duration;
    int calories;
    double distance;
};

struct SleepData {
    std::string date;
    int hours;
    int quality;
};

class User {
private:
    std::string username;
    std::vector<Activity> activities;
    std::vector<SleepData> sleepRecords;
    double weight;
    double height;
    int age;

public:
    User(const std::string& name, double w, double h, int a);
    
    void addActivity(const std::string& date, const std::string& type, 
                    int duration, int calories, double distance = 0);
    void addSleepData(const std::string& date, int hours, int quality);
    
    std::string getUsername() const;
    double getWeight() const;
    double getHeight() const;
    int getAge() const;
    
    int getTotalCaloriesBurned() const;
    double getAverageSleepHours() const;
};

#endif
//
// Created by vladg on 6/2/2025.
//

#ifndef OBSERVER_H
#define OBSERVER_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Forward declaration of Subject
class Subject;

// Observer interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& eventMessage) = 0; // A simple update method
    virtual const std::string& getName() const = 0; // To identify the observer
};

// Subject class (Observable)
class Subject {
private:
    std::vector<Observer*> observers;

public:
    virtual ~Subject() = default;

    void attach(Observer* observer) {
        if (observer) {
            observers.push_back(observer);
        }
    }

    void detach(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify(const std::string& eventMessage) {
        for (Observer* observer : observers) {
            if (observer) {
                observer->update(eventMessage);
            }
        }
    }
};
#endif //OBSERVER_H

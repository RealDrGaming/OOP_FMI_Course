#pragma once
#include <string>

class Device
{
private:
    std::string name;
    double power;
    bool isOn;
    
public:
    Device(const std::string& name, double power);
    
    std::string getName() const;
    double getPower() const;
    bool isTurnedOn() const;
    
    void turnOn();
    void turnOff();
    
    void print() const;
};

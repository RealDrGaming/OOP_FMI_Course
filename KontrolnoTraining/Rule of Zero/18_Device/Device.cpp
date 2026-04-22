#include "Device.h"

#include <iostream>
#include <ostream>

Device::Device(const std::string& _name, double _power) : name(_name), power(_power), isOn(false)
{
    
}

std::string Device::getName() const
{
    return name;
}

double Device::getPower() const
{
    return power;
}

bool Device::isTurnedOn() const
{
    return isOn;
}

void Device::turnOn()
{
    isOn = true;
}

void Device::turnOff()
{
    isOn = false;
}

void Device::print() const
{
    std::cout << "Device: " << name << " | Power: " << power << "W | Status: " << isOn << std::endl;
}
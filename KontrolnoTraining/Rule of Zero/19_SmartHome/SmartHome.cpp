#include "SmartHome.h"

#include <algorithm>

void SmartHome::addDevice(const std::string& name, double power)
{
    devices.emplace_back(std::move(std::make_unique<Device>(name, power)));
}

bool SmartHome::turnOnDevice(const std::string& targetName)
{
    auto it = std::find_if(devices.begin(), devices.end(), 
        [&targetName](const std::unique_ptr<Device>& device)
        {
            return device->getName() == targetName;
        });
    
    if (it != devices.end()) 
    {
        (*it)->turnOn();
        return true;
    }
    
    return false;
}

size_t SmartHome::countActiveDevices() const
{
    auto it = std::count_if(devices.begin(), devices.end(), [](const std::unique_ptr<Device>& device)
    {
       return device->isTurnedOn(); 
    });
    
    return it;
}

void SmartHome::removePowerHogs(double limit)
{
    devices.erase(std::remove_if(std::begin(devices), std::end(devices), 
        [&limit](const std::unique_ptr<Device>& device)
    {
        return device->getPower() >= limit;
    }), 
    devices.end());
}

void SmartHome::printAll() const
{
    for (const auto& device : devices)
    {
        device->print();
    }
}
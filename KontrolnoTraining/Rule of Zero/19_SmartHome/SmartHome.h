#pragma once
#include <memory>
#include <vector>

#include "../18_Device/Device.h";

class SmartHome
{
private:
    std::vector<std::unique_ptr<Device>> devices;
    
public:
    void addDevice(const std::string& name, double power);
    bool turnOnDevice(const std::string& targetName);
    size_t countActiveDevices() const;
    void removePowerHogs(double limit);
    void printAll() const;
};

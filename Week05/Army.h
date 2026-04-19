#pragma once
#include "Soldier.h"

class Army
{
private:
    Soldier* soldiers;
    size_t count;
    size_t capacity;

    void resize(size_t newCapacity);

public:
    ~Army();
    Army(const Army& other);
    Army& operator=(const Army& other);
    Army(Army&& other) noexcept;
    Army& operator=(Army&& other) noexcept;

    
    Army();
    explicit Army(size_t size);
    Army(size_t size, const Soldier& prototype);
    
    size_t getSize() const;
    Soldier& getSoldier(size_t index);
    const Soldier& getSoldier(size_t index) const;
    void addSoldier(const Soldier& soldier);
    void removeSoldierByIndex(size_t index);
    void removeSoldierByReference(const Soldier& soldier);
};
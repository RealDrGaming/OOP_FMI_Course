#include "Army.h"

void Army::resize(size_t newCapacity)
{
    // 1. Allocate a new, larger array
    Soldier* temp = new Soldier[newCapacity];
    
    // 2. Copy the existing soldiers over
    for (size_t i = 0; i < count; ++i) {
        temp[i] = soldiers[i];
    }
    
    // 3. Delete the old, smaller array to prevent memory leaks
    delete[] soldiers;
    
    // 4. Point to the new array and update capacity
    soldiers = temp;
    capacity = newCapacity;
}

// 1. Destructor
Army::~Army()
{
    delete[] soldiers;
}

// 2. Copy Constructor (Deep Copy)
Army::Army(const Army& other) : count(other.count), capacity(other.capacity)
{
    soldiers = new Soldier[capacity];
    for (size_t i = 0; i < count; ++i) {
        soldiers[i] = other.soldiers[i];
    }
}

// 3. Copy Assignment Operator
Army& Army::operator=(const Army& other)
{
    if (this != &other) { // Prevent self-assignment (e.g., army1 = army1)
        // Allocate first to provide strong exception guarantee
        Soldier* temp = new Soldier[other.capacity];
        for (size_t i = 0; i < other.count; ++i) {
            temp[i] = other.soldiers[i];
        }
        
        delete[] soldiers; // Clear old memory
        
        soldiers = temp;
        count = other.count;
        capacity = other.capacity;
    }
    return *this;
}

// 4. Move Constructor (Steal resources instead of copying)
Army::Army(Army&& other) noexcept : soldiers(other.soldiers), count(other.count), capacity(other.capacity)
{
    // Nullify the other object so its destructor doesn't delete our stolen memory
    other.soldiers = nullptr;
    other.count = 0;
    other.capacity = 0;
}

// 5. Move Assignment Operator
Army& Army::operator=(Army&& other) noexcept
{
    if (this != &other) {
        delete[] soldiers; // Clear our existing memory
        
        // Steal resources
        soldiers = other.soldiers;
        count = other.count;
        capacity = other.capacity;
        
        // Nullify the other object
        other.soldiers = nullptr;
        other.count = 0;
        other.capacity = 0;
    }
    return *this;
}

// Конструктор по подразбиране
Army::Army() : count(0), capacity(2) // Start with a small capacity
{
    soldiers = new Soldier[capacity];
}

// Конструктор, който приема големина
Army::Army(size_t size) : count(size), capacity(size > 0 ? size : 2)
{
    soldiers = new Soldier[capacity]; // Calls Soldier's default constructor
}

// Конструктор, който приема големина и образец (Prototype)
Army::Army(size_t size, const Soldier& prototype) : count(size), capacity(size > 0 ? size : 2)
{
    soldiers = new Soldier[capacity];
    for (size_t i = 0; i < count; ++i) {
        soldiers[i] = prototype;
    }
}

// Връща големината на армията
size_t Army::getSize() const
{
    return count;
}

// Достъп до войник по номер (неконстантен)
Soldier& Army::getSoldier(size_t index)
{
    if (index >= count) {
    }
    return soldiers[index];
}

// Достъп до войник по номер (константен)
const Soldier& Army::getSoldier(size_t index) const
{
    if (index >= count) {
    }
    return soldiers[index];
}

// Добавяне на войник
void Army::addSoldier(const Soldier& soldier)
{
    if (count == capacity) {
        // Double the capacity if we run out of room
        resize(capacity == 0 ? 2 : capacity * 2); 
    }
    soldiers[count] = soldier;
    count++;
}

// Премахване на войник по номер
void Army::removeSoldierByIndex(size_t index)
{
    if (index >= count) return; // Do nothing if index is invalid

    // Shift all elements to the left to overwrite the removed soldier
    for (size_t i = index; i < count - 1; ++i) {
        soldiers[i] = soldiers[i + 1];
    }
    count--;
}

// Премахване на войник по подаден войник
void Army::removeSoldierByReference(const Soldier& soldier)
{
    for (size_t i = 0; i < count; ++i) {
        // Compare memory addresses to ensure it's the exact same object
        if (&soldiers[i] == &soldier) {
            removeSoldierByIndex(i);
            return; // Exit after removing the first match
        }
    }
}
#pragma once

class Order
{
private:
    char* client;
    double* prices;
    size_t count;
    size_t capacity;
    
    void freeMemory();
    void copyFrom(const Order& other);
    void moveFrom(Order&& other);
    
    void resize(size_t newCapacity);
    
public:
    ~Order();
    Order(const Order& other);
    Order& operator=(const Order& other);
    Order(Order&& other) noexcept;
    Order& operator=(Order&& other) noexcept;
    
    Order();
    Order(const char* clientName);
    
    void addPrice(double priceToAdd);
    const Order& operator[](size_t index);
    bool operator>(const Order& other);
    Order operator+(const Order& other);
    void print() const;
};

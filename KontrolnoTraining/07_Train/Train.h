#pragma once

class Train
{
private:
    struct Wagon
    {
        char* cargo;
        Wagon* next;
    };
    Wagon* head;
    Wagon* tail;
    
    void freeMemory();
    void copyFrom(const Train& other);
    void moveFrom(Train&& other);
    
public:
    ~Train();
    Train(const Train& train);
    Train& operator=(const Train& other);
    Train(Train&& other) noexcept;
    Train& operator=(Train&& other) noexcept;
    
    Train();
    void print() const;
    
    Train& operator+=(const char* newCargo);
    Train operator+(const Train& other) const;
};

#pragma once

#include "../09_Polynomial/Polynomial.h"

class MathEngine
{
private:
    Polynomial* polys;
    size_t count;
    size_t capacity;
    
    void freeMemory();
    void copyFrom(const MathEngine& other);
    void moveFrom(MathEngine&& other);
    
    void resize(size_t newCapacity);
    
public:
    ~MathEngine();
    MathEngine(const MathEngine& other);
    MathEngine& operator=(const MathEngine& other);
    MathEngine(MathEngine&& other) noexcept;
    MathEngine& operator=(MathEngine&& other) noexcept;
    
    MathEngine();
    void addPolynomial(const Polynomial& polynomial);
    Polynomial sumAll() const;
    void evaluateAll(int x) const;
};

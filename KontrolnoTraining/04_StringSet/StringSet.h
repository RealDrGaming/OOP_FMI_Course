#pragma once

class StringSet
{
private:
    char** words;
    size_t count;
    size_t capacity;
    
    void freeMemory();
    void copyFrom(const StringSet& other);
    void moveFrom(StringSet&& other);
    void resize(size_t newCapacity);
public:
    ~StringSet();
    StringSet(const StringSet& other);
    StringSet& operator=(const StringSet& other);
    StringSet(StringSet&& other) noexcept;
    StringSet& operator=(StringSet&& other) noexcept;
    
    StringSet();
    bool contains(const char* word) const;
    void add(const char* word);
    
    StringSet& operator+=(const char* word);
    StringSet operator+(const StringSet& other) const;
    
    void print() const;
};

#pragma once

class Dictionary
{
private:
    struct WordPair
    {
        char* word;
        char* translation;
    };
    
    WordPair* entries;
    size_t size;
    size_t capacity;
    
    void freeMemory();
    void copyFrom(const Dictionary& other);
    void moveFrom(Dictionary&& other);
    
    void resize(size_t newCapacity);
    
public:
    ~Dictionary();
    Dictionary(const Dictionary& other);
    Dictionary& operator=(const Dictionary& other);
    Dictionary(Dictionary&& other) noexcept;
    Dictionary& operator=(Dictionary&& other) noexcept;
    
    Dictionary();
    void add(const char* word, const char* translation);
    const char* operator[](const char* word) const;
    Dictionary operator+(const Dictionary& other) const;
    void print() const;
};

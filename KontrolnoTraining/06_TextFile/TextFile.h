#pragma once

class TextFile
{
private:
    char** lines;
    size_t count;
    size_t capacity;
    
    void freeMemory();
    void copyFrom(const TextFile& other);
    void moveFrom(TextFile&& other);
    
    void resize(size_t newCapacity);
    
public:
    ~TextFile();
    TextFile(const TextFile& other);
    TextFile& operator=(const TextFile& other);
    TextFile(TextFile&& other) noexcept;
    TextFile& operator=(TextFile&& other) noexcept;
    
    TextFile();
    void appendLine(const char* line);
    void print() const;
    
    TextFile& operator+=(const char* text);
    TextFile operator+(const TextFile& other) const;
};

#pragma once

class TextDocument
{
private:
    char* title;
    char** paragraphs;
    size_t count;
    size_t capacity;
    
    void resize(size_t newCapacity);
    void freeMemory();
    void copyFrom(const TextDocument& other);
    void moveFrom(TextDocument&& other);
    
public:
    ~TextDocument();
    TextDocument(const TextDocument& other);
    TextDocument& operator=(const TextDocument& other);
    TextDocument(TextDocument&& other) noexcept;
    TextDocument& operator=(TextDocument&& other) noexcept;
    
    TextDocument(const char* title);
    void addParagraph(const char* paragraph);
    void print() const;
};
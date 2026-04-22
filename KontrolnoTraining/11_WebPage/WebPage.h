#pragma once

class WebPage
{
private:
    char* url;
    char** links;
    size_t count;
    size_t capacity;
    
    void freeMemory();
    void copyFrom(const WebPage& other);
    void moveFrom(WebPage&& other);
    
    void resize(size_t newCapacity);

public:
    ~WebPage();
    WebPage(const WebPage& other);
    WebPage& operator=(const WebPage& other);
    WebPage(WebPage&& other) noexcept;
    WebPage& operator=(WebPage&& other) noexcept;
    
    WebPage();
    WebPage(const char* pageUrl);
    
    WebPage& operator+=(const char* newLink);
    bool operator==(const WebPage& other) const;
    const char* operator[](size_t index) const;
    void print() const;
};

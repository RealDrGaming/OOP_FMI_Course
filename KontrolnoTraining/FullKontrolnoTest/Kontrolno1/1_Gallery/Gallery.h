#pragma once

class Gallery
{
private:
    struct Painting
    {
        char* paintingName;
        double price;
    };
    
    char* galleryName;
    Painting* paintings;
    size_t count;
    size_t capacity;
    
    void freeMemory();
    void copyFrom(const Gallery& other);
    void moveFrom(Gallery&& other);
    
    void resize(size_t newCapacity);
    
public: 
    ~Gallery();
    Gallery(const Gallery& other);
    Gallery& operator=(const Gallery& other);
    Gallery(Gallery&& other) noexcept;
    Gallery& operator=(Gallery&& other) noexcept;
    
    Gallery();
    Gallery(const char* name);
    
    void addPainting(const char* paintingName, double paintingPrice);
    double operator[](size_t index) const;
    bool operator==(const Gallery& other) const;
    void sellPainting(const char* paintingName);
    void print() const;
};

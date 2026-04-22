#pragma once
#include <string>

class VideoGame
{
private:
    std::string title;
    double price;
    double rating;
    
public:
    VideoGame(const std::string& title, double price, double rating);
    std::string getTitle() const;
    double getPrice() const;
    double getRating() const;
    void print() const;
};
#include "VideoGame.h"

#include <iostream>
#include <ostream>

VideoGame::VideoGame(const std::string& title, double price, double rating) : title(title), price(price), rating(rating)
{
    
}

std::string VideoGame::getTitle() const
{
    return this->title;
}

double VideoGame::getPrice() const
{
    return this->price;
}

double VideoGame::getRating() const
{
    return this->rating;
}

void VideoGame::print() const
{
    std::cout << "Title: " << this->title << " | " << this->price << "$ | Rating: " << this->rating << std::endl;
}
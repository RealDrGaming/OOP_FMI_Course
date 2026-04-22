#pragma once
#include <memory>
#include <vector>

#include "../16_VideoGame/VideoGame.h"

class GameLibrary
{
private:
    std::vector<std::unique_ptr<VideoGame>> games;
    
public:
    void addGame(const std::string& title, double price, double rating);
    void printAll() const;
    bool hasGame(const std::string& title) const;
    void sortByRating();
};

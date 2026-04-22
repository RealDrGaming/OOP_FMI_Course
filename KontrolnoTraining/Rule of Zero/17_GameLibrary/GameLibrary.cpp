#include "GameLibrary.h"

#include <algorithm>

void GameLibrary::addGame(const std::string& title, double price, double rating)
{
    games.emplace_back(std::move(std::make_unique<VideoGame>(title, price, rating)));
}

void GameLibrary::printAll() const
{
    for (const auto& game : games)
    {
        game->print();
    }
}

bool GameLibrary::hasGame(const std::string& title) const
{
    auto it = std::find_if(games.begin(), games.end(),
        [&title](const std::unique_ptr<VideoGame>& game) { return game->getTitle() == title;}); // Сравняваме директно, std::string го може!
    
    return it != games.end();
}

void GameLibrary::sortByRating()
{
    std::sort(games.begin(), games.end(), 
        [](const std::unique_ptr<VideoGame>& a, const std::unique_ptr<VideoGame>& b)
        {
            // Връщаме true, ако първата игра трябва да е ПРЕДИ втората
            return a->getRating() > b->getRating();
        });
}
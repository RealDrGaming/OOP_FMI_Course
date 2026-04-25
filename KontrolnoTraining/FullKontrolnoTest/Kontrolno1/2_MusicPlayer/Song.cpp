#include "Song.h"

#include <iostream>
#include <ostream>

Song::Song(const std::string& _title, const std::string& _artist, int _duration)
    : title(_title), artist(_artist), duration(_duration), isLiked(false) { }

const std::string& Song::getTitle() const
{
    return title;
}

const std::string& Song::getArtist() const
{
    return artist;
}

int Song::getDuration() const
{
    return duration;
}

bool Song::isSongLiked() const
{
    return isLiked;
}

void Song::like()
{
    isLiked = true;
}

void Song::print() const
{
    std::cout << title << " by " << artist << " (" << duration << ") " << (isLiked ? " [LIKED]" : "") << std::endl;
}
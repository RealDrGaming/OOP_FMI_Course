#pragma once
#include <string>

class Song
{
private:
    std::string title;
    std::string artist;
    int duration;
    bool isLiked;
    
public:
    Song(const std::string& title, const std::string& artist, int duration);
    const std::string& getTitle() const;
    const std::string& getArtist() const;
    int getDuration() const;
    bool isSongLiked() const;
    
    void like();
    void print() const;
};
#pragma once
#include <memory>
#include <vector>

#include "Song.h"

class MusicPlayer
{
private:
    std::vector<std::unique_ptr<Song>> playlist;

public:
    void addSong(const std::string& title, const std::string& artist, int duration);
    bool likeSong(const std::string& title);
    int countLiked();
    void removeShortSongs(int limit);
    void sortPlaylist();
    void print() const;
};
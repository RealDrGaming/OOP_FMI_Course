#include "MusicPlayer.h"

#include <algorithm>

void MusicPlayer::addSong(const std::string& title, const std::string& artist, int duration)
{
    playlist.emplace_back(std::make_unique<Song>(title, artist, duration));
}

bool MusicPlayer::likeSong(const std::string& title)
{
    auto it = std::find_if(playlist.begin(), playlist.end(), 
        [&title](const std::unique_ptr<Song>& song)
        {
            return song->getTitle() == title;
        });

    if (it != playlist.end())
    {
        (*it)->like();
        return true;
    }
    return false;
}

int MusicPlayer::countLiked()
{
    auto it = std::count_if(playlist.begin(), playlist.end(), [](const std::unique_ptr<Song>& song)
    {
        return song->isSongLiked();
    });
    
    return it;
}

void MusicPlayer::removeShortSongs(int limit)
{
    playlist.erase(
        std::remove_if(playlist.begin(), playlist.end(), [&limit](const std::unique_ptr<Song>& song)
    {
        return song->getDuration() < limit;
    }), playlist.end());
}

void MusicPlayer::sortPlaylist()
{
    std::sort(playlist.begin(), playlist.end(), 
        [](const std::unique_ptr<Song>& song1, const std::unique_ptr<Song>& song2)
        {
            if (song1->getArtist() == song2->getArtist())
            {
                return song1->getDuration() > song2->getDuration();
            }
            
            return song1->getArtist() < song2->getArtist();
        });
}

void MusicPlayer::print() const
{
    for (const auto& song : playlist)
    {
        song->print();
    }
}
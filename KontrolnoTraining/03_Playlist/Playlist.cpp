#include "Playlist.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ostream>

void Playlist::freeMemory()
{
    delete[] playlistName;
    
    for (size_t i = 0; i < count; ++i)
    {
        delete[] tracks[i].trackName;
    }
    
    delete[] tracks;
    
    capacity = 0;
    count = 0;
}

void Playlist::copyFrom(const Playlist& other) noexcept
{
    this->capacity = other.capacity;
    this->count = other.count;
    
    this->playlistName = new char[strlen(other.playlistName) + 1];
    strcpy(this->playlistName, other.playlistName);
    
    this->tracks = new Track[this->capacity];
    
    for (size_t i = 0; i < this->count; ++i)
    {
        this->tracks[i].trackName = new char[strlen(other.tracks[i].trackName) + 1];
        strcpy(this->tracks[i].trackName, other.tracks[i].trackName);
        this->tracks[i].duration = other.tracks[i].duration;
    }
}

void Playlist::moveFrom(Playlist&& other) noexcept
{
    this->tracks = other.tracks;
    this->playlistName = other.playlistName;
    this->capacity = other.capacity;
    this->count = other.count;
    
    other.tracks = nullptr;
    other.playlistName = nullptr;
    other.count = 0;
    other.capacity = 0;
}

void Playlist::resize(size_t newCapacity)
{
    if (newCapacity <= capacity) return;
    
    Track* tempTracks = new Track[newCapacity];

    for (size_t i = 0; i < count; ++i)
    {
        tempTracks[i] = tracks[i]; 
    }
        
    delete[] tracks;
    tracks = tempTracks;
    capacity = newCapacity;
}

Playlist::~Playlist()
{
    freeMemory();
}

Playlist::Playlist(const Playlist& other)
{
    copyFrom(other);
}

Playlist& Playlist::operator=(const Playlist& other)
{
    if (this != &other)
    {
        freeMemory();
        copyFrom(other);
    }
    return *this;
}

Playlist::Playlist(Playlist&& other)
{
    moveFrom(std::move(other));
}

Playlist& Playlist::operator=(Playlist&& other)
{
    if (this != &other)
    {
        freeMemory();
        moveFrom(std::move(other));
    }
    return *this;
}

Playlist::Playlist(const char* playlistName) : count(0), capacity(2)
{
    this->playlistName = new char[strlen(playlistName) + 1];
    strcpy(this->playlistName, playlistName);
    
    this->tracks = new Track[this->capacity];
}

void Playlist::addTrack(const char* trackName, int duration)
{
    if (count == capacity)
    {
        resize(capacity * 2);
    }
    
    tracks[count].trackName = new char[strlen(trackName) + 1];
    strcpy(tracks[count].trackName, trackName);
    tracks[count].duration = duration;
    
    count++;
}

void Playlist::print() const
{
    std::cout << playlistName << std::endl;
    
    for (size_t i = 0; i < count; i++)
    {
        std::cout << tracks[i].trackName << " - " << tracks[i].duration << std::endl;
    }
}

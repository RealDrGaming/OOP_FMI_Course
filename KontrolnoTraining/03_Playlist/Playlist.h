#pragma once

class Playlist
{
private:
    struct Track
    {
        char* trackName;
        int duration;
    };
    
    char* playlistName;
    Track* tracks;
    size_t count;
    size_t capacity;
    
    void freeMemory();
    void copyFrom(const Playlist& other);
    void moveFrom(Playlist&& other);
    void resize(size_t newCapacity);
    
public:
    ~Playlist();
    Playlist(const Playlist& other);
    Playlist& operator=(const Playlist& other);
    Playlist(Playlist&& other) noexcept; 
    Playlist& operator=(Playlist&& other) noexcept;

    Playlist(const char* playlistName);
    void addTrack(const char* trackName, int duration);
    void print() const;
};
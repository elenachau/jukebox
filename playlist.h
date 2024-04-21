#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "song.h"

class Playlist{
    Song *firstSong, *lastSong;
    int numberSongsLoaded;
    string name;
    bool isAlreadyInPlaylist(Song);
    void addNewSong(const Song);
    void deleteSong(int);
    void deleteSong();

    public:
        Playlist();
        Playlist(Song*, Song*, int, string);
        Playlist(const Playlist& rhs);

        Song* getFirstSong();
        Song* getLastSong();
        int getNumSongsLoaded() const;
        string getName() const;
        Song* getSongAtIndex(int) const;

        void setFirstSong(Song*);
        void setLastSong(Song*);
        void setNumSongsLoaded(int);
        void setName(string);
        
        void addNewSong(Song, int);

        void displayLoadedSongs(bool=true) const;
        ~Playlist();
        Playlist& operator=(const Playlist&);

        friend ostream& operator<<(ostream &out, const Playlist &p);
        void operator+(Song a);
        void operator-(int);

};

#endif
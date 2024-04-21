#ifndef SONG_H
#define SONG_H

#include <iostream>
using namespace std;

class Song{
    string title, artist;
    Song* nextSong;

    public:
        Song();
        Song(string, string, Song*);
        Song(const Song&);
        ~Song();

        void setTitle(const string);
        void setNextSong(Song*);
        void setArtist(const string);

        string getTitle() const;
        Song* getNextSong();
        string getArtist() const;
        Song& operator=(const Song&);

        friend ostream& operator<<(ostream &, const Song &);
};

#endif

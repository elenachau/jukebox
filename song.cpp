#include "song.h"

Song::Song(){
    nextSong = nullptr;
    title = "none";
    artist = "none";
}

Song::Song(string t, string a, Song* n){
    nextSong = nullptr;
    artist = a;
    title = t;
}

Song::Song(const Song& rhs){
    nextSong = nullptr;
    artist = rhs.artist;
    title = rhs.title;
}

void Song::setTitle(const string t){
    title = t;
}

void Song::setNextSong(Song* n){
    nextSong = n;
}

void Song::setArtist(const string a){
    artist = a;
}

string Song::getTitle() const{
    return title;
}

Song* Song::getNextSong(){
    return nextSong;
}

string Song::getArtist() const{
    return artist;
}

Song& Song::operator=(const Song& rhs){
    nextSong = rhs.nextSong;
    artist = rhs.artist;
    title = rhs.title;
    return *this;
}

Song::~Song(){
    //handled by playlist class
}
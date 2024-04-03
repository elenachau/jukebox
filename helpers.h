#ifndef HELPERS_H
#define HELPERS_H

#include "playlist.h"
#include <fstream>
#include <dirent.h> //functions for directory streams


void getUserEntry(int&);
void getUserEntry(char&);
void getUserEntry(float&);
void getUserEntry(string&);

void displayMainMenu();
void promptSongSelection();
void writePlaylistToFile(Playlist&);
void readData(ifstream&, Playlist&);
bool createNewPlaylist(const Playlist&, Playlist&);
bool playlistExists(string);
bool manageExistingPlaylists(const Playlist&, Playlist&);
int getExistingPlaylists(string*);
void promptPlaylistSelection(string*, int);
bool modifyPlaylist(Playlist&, const Playlist&);
bool addSongToPlaylist(Playlist&, const Playlist&);
bool deleteSongFromPlaylist(Playlist&);
bool deletePlaylist(Playlist&);

#endif
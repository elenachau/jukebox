#include "helpers.h"

void getUserEntry(int& val){
    string temp;
    getline(cin, temp);
    val = stoi(temp);
}

void getUserEntry(char& val){
    string temp;
    getline(cin, temp);
    val = (temp[0]); //get first char of str
}

void getUserEntry(float& val){
    string temp;
    getline(cin, temp);
    val = stof(temp);
}

void getUserEntry(string&){

}

void displayMainMenu(){

}

void promptSongSelection(Playlist allSongs){
    cout << allSongs;
    cout << allSongs.getNumSongsLoaded()+1 << ". Exit Program" << endl;
    cout << "Please enter the number of the song to be added to your playlist: ";
}

void writePlaylistToFile(Playlist&){

}

void readData(ifstream&, Playlist&){

}

bool createNewPlaylist(const Playlist&, Playlist&){

}

bool playlistExists(string){

}

bool manageExistingPlaylists(const Playlist&, Playlist&){

}

int getExistingPlaylists(string*){

}

void promptPlaylistSelection(string*, int){

}

bool modifyPlaylist(Playlist&, const Playlist&){

}

bool addSongToPlaylist(Playlist&, const Playlist&){

}

bool deleteSongFromPlaylist(Playlist&){

}

bool deletePlaylist(Playlist&){

}

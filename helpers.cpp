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

void getUserEntry(string& val){
    getline(cin, val);
}

void displayMainMenu(){
    cout <<endl<< "Welcome to SongStoreSupreme!" <<endl;
    cout << "1. Load an existing playlist."<<endl;
    cout << "2. Create a new playlist." <<endl;
    cout << "3. Exit SongStoreSupreme." <<endl;
}

void promptSongSelection(Playlist allSongs){
    cout << allSongs;
    cout << allSongs.getNumSongsLoaded()+1 << ". Exit Program" << endl;
    cout << "Please enter the number of the song to be added to your playlist: ";
}

void writePlaylistToFile(Playlist& playlist){
    ofstream outStream(playlist.getName()+".txt");
    int numSongs = playlist.getNumSongsLoaded();
    
    for(int i = 0; i < (numSongs-1); i++){
        outStream << playlist.getSongAtIndex(i+1)->getTitle() + "-" + playlist.getSongAtIndex(i+1)->getArtist() << endl;
    }
    outStream << playlist.getSongAtIndex(numSongs)->getTitle() + "-" + playlist.getSongAtIndex(numSongs)->getArtist();
    outStream.close();
}

void readData(ifstream& inFile, Playlist& allSongs){
    string temp;
    int numSongsTotal = 0;
    while(!inFile.eof()){
        Song newSong;
        getline(inFile, temp, '-');
        newSong.setTitle(temp);
        getline(inFile, temp);
        newSong.setArtist(temp);
        allSongs + newSong;
        numSongsTotal++;
    }
}

bool createNewPlaylist(const Playlist&, Playlist&){

}

bool playlistExists(string newPlaylist){
    newPlaylist += ".txt";
    ifstream inStream(newPlaylist);
    if(inStream.is_open()){
        return true;
    }
    return false;
}

bool manageExistingPlaylists(const Playlist&, Playlist&){

}

int getExistingPlaylists(string*){

}

void promptPlaylistSelection(string* existingPlaylists, int numPlaylists){
    cout << endl;
    cout << "The following playlists are currently available: " << endl;
    for(int i = 0; i < numPlaylists; i++){
        cout << i+1 << ". " << existingPlaylists[i] << endl;
    }
}

bool modifyPlaylist(Playlist&, const Playlist&){

}

bool addSongToPlaylist(Playlist&, const Playlist&){

}

bool deleteSongFromPlaylist(Playlist&){

}

bool deletePlaylist(Playlist&){

}

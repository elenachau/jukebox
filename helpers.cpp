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

bool deleteSongFromPlaylist(Playlist& playlist){
    int* selections = new int[playlist.getNumSongsLoaded()];
    int songChoice, count = 0;
    char cont;
    int numSongs = playlist.getNumSongsLoaded();
    cout << "====" << playlist.getName() << "====" << endl;
    cout << playlist;

    cout << playlist.getNumSongsLoaded() + 1 << ". ";
    if(playlist.getNumSongsLoaded() + 1 < 10) {
        cout << "  ";
    }
    else if(playlist.getNumSongsLoaded() + 1 < 100) {
        cout << " ";
    }
    cout << "Return to Playlist Options Menu." << endl;

    cout << playlist.getNumSongsLoaded() + 2 << ". ";
    if(playlist.getNumSongsLoaded() + 2 < 10) {
        cout << "  ";
    }
    else if(playlist.getNumSongsLoaded() + 2 < 100) {
        cout << " ";
    }
    cout << "Exit Program." << endl;

    do{
        cout << "Select a song: ";
        getUserEntry(songChoice);
        bool alreadyDeleted = false;
        
        for(int i = 0; i < count; i++){
            if(songChoice == selections[i]){
                alreadyDeleted = true;
            }
        }
        if(!alreadyDeleted && songChoice <= numSongs){
            selections[count] = songChoice;
            count+=1;
        }
    }while(songChoice != numSongs + 1 && songChoice != numSongs + 2 && count != numSongs); //check is count != numSongs because 0-based index

    if(count > 1) {
        for(int i = 0; i < count; i++){
            for(int j = 0; j < count - i - 1; j++){
                if(selections[j] < selections[j+1]){
                    int temp = selections[j];
                    selections[j] = selections[j+1];
                    selections[j+1] = temp;
                }
            }
        }

        //other implementation, not as effective
        // for(int i = 0; i < count; i++){
        //     for(int j = 0; j < count; j++){
        //         if(selections[j] < selections[j+1]){
        //             int temp = selections[j];
        //             selections[j] = selections[j+1];
        //             selections[j+1] = temp;
        //         }
        //     }
        // }
    }

    for(int i = 0; i < count; i++){
        playlist - selections[i];
    }
    
    if(playlist.getNumSongsLoaded() == 0){
        cout << "All songs are deleted. Removing playlist." << endl;
        string fileToRemove = playlist.getName() + ".txt";
        remove(fileToRemove.c_str()); //delete playlist; must cast expected parameter of const char* with c_str() to turn obj to C-style str
        // delete &playlist;
        cout << "Return to main menu (y/n)?";
        getUserEntry(cont);
        if(cont == 'n' || cont == 'N'){
            return true;
        }
        return false;
    }

    writePlaylistToFile(playlist);
    if(songChoice == numSongs + 2){
        return true;
    }
    return false;
}

bool deletePlaylist(Playlist&){

}

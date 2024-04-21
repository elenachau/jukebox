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

bool createNewPlaylist(const Playlist& allSongs, Playlist& newPlaylist){
    bool entryMade = false;
    int numPrompts = 0;
    string playlistName;

    do{
        if(numPrompts > 0){
            cout << "Another playlist already exists with that name." << endl;
        }
        cout << endl << "Playlist name: ";
        getUserEntry(playlistName);
        numPrompts++;
    }while(playlistExists(playlistName));
    newPlaylist.setName(playlistName);

    cout << "Displaying Available Songs: " << endl;
    cout << allSongs;
    cout << allSongs.getNumSongsLoaded()+1 << ". ";
    if(allSongs.getNumSongsLoaded() + 1 < 10) {
        cout << "  ";
    }
    else if(allSongs.getNumSongsLoaded() + 1 < 100) {
        cout << " ";
    }
    cout << "Finalize List." << endl;

    cout << allSongs.getNumSongsLoaded() + 2 << ". ";
    if(allSongs.getNumSongsLoaded() + 2 < 10) {
        cout << "  ";
    }
    else if(allSongs.getNumSongsLoaded() + 2 < 100) {
        cout << " ";
    }
    cout << "Exit Program." << endl;

    int userSongChoice;
    do{
        cout << "Make a selection: ";
        getUserEntry(userSongChoice);
        if(userSongChoice == allSongs.getNumSongsLoaded()+1){
            if(newPlaylist.getNumSongsLoaded() > 0){
                writePlaylistToFile(newPlaylist);
            }
            return false;
        }
        else if(userSongChoice > 0 && userSongChoice < allSongs.getNumSongsLoaded()){
            entryMade = true;
            newPlaylist + *allSongs.getSongAtIndex(userSongChoice);
        }
        else{
            char save;
            if(entryMade){
                do{
                    cout << "Would you like to save (y/n): ";
                    getUserEntry(save);
                }while(save != 'y' && save != 'n');
                if(save == 'y'){
                    writePlaylistToFile(newPlaylist);
                }
            }
            return true;
        }
    }while((userSongChoice != allSongs.getNumSongsLoaded() + 1) && (userSongChoice != allSongs.getNumSongsLoaded() + 2));
    writePlaylistToFile(newPlaylist);
    if(userSongChoice == allSongs.getNumSongsLoaded() + 2){
        return true;
    }
    system("clear");
    return false;

}

bool playlistExists(string newPlaylist){
    newPlaylist += ".txt";
    ifstream inStream(newPlaylist);
    if(inStream.is_open()){
        return true;
    }
    return false;
}

bool manageExistingPlaylists(const Playlist& all, Playlist& selectedPlaylist){
    string* existingPlaylists = new string[100];
    int numPlaylistsExisting = getExistingPlaylists(existingPlaylists);

    promptPlaylistSelection(existingPlaylists, numPlaylistsExisting);
    cout << numPlaylistsExisting+1 << ". Return to Main Menu." << endl;
    cout << numPlaylistsExisting+2 << ". Exit Program." << endl;
    
    int userEntryPlaylist, mods;

    do{
        cout << endl << "Which playlist would you like to load?";
        getUserEntry(userEntryPlaylist);
    }while(userEntryPlaylist < 1 || userEntryPlaylist > numPlaylistsExisting + 2);

    if(userEntryPlaylist == numPlaylistsExisting + 2){
        return true; //exit
    }
    else if(userEntryPlaylist == numPlaylistsExisting + 1){
        return false;
    }

    bool exit = false;
    do{
        ifstream fin(existingPlaylists[userEntryPlaylist-1] + ".txt");
        selectedPlaylist.setName(existingPlaylists[userEntryPlaylist-1]); //set name
        readData(fin, selectedPlaylist); //add songs
        system("clear");
        cout << "========" << selectedPlaylist.getName() << "========" << endl;
        selectedPlaylist.displayLoadedSongs(false);
        cout << endl;

        promptModificationsToExistingPlaylist();
        do{
            cout << "What would you like to do with " << existingPlaylists[userEntryPlaylist-1] << "? ";
            getUserEntry(mods);
        }while(mods > 4 && mods < 1);

        system("clear");
        cout << "========" << selectedPlaylist.getName() << "========" << endl;
        selectedPlaylist.displayLoadedSongs(false);
        cout << endl;
        switch(mods){
            case 1:
                exit = modifyPlaylist(selectedPlaylist, all);
                if(selectedPlaylist.getNumSongsLoaded() == 0){
                    mods = 3; //return to main menu
                }
                else if(exit){
                    mods = 4; //exit program
                }
                break;
            case 2:
                exit = deletePlaylist(selectedPlaylist);
                mods = 3;
                break;
            case 3:
                exit = false;
                break;
            case 4:
                exit = true;
                break;
            default:
                cout << "Invalid Selection." << endl;
        }
    }while(mods != 3 && mods != 4);
    return exit;
}

int getExistingPlaylists(string* existingPlaylists){
    DIR *directoryPtr = opendir("."); //open current directory
    struct dirent *directoryEntry; //ptr to structure representing directory entry
    int numPlaylists = 0;
    if(directoryPtr){ //if directory opened successfully
        while((directoryEntry = readdir(directoryPtr)) != NULL) { //loop through each directory entry
            string filename = directoryEntry->d_name; //extracts current directory; d_name is a member of dirent structure
            string empty = "";
            if(filename != "dbSmall.txt" && filename != "dbLarge.txt"){
                for(int i = filename.size()/sizeof('c')-4; i < filename.size()/sizeof('c'); i++){
                    empty += filename[i]; //gets file extension e.g. .txt
                }
                if(empty == ".txt"){
                    string cleanedFilename = "";
                    for(int i = 0; i < filename.size()/sizeof('a') - 4; i++){
                        cleanedFilename += filename[i];
                    }
                    existingPlaylists[numPlaylists] = cleanedFilename;
                    numPlaylists++;
                }
            }
        }
        closedir(directoryPtr); //close directory
    }

    return numPlaylists;
}

void promptPlaylistSelection(string* existingPlaylists, int numPlaylists){
    cout << endl;
    cout << "The following playlists are currently available: " << endl;
    for(int i = 0; i < numPlaylists; i++){
        cout << i+1 << ". " << existingPlaylists[i] << endl;
    }
}

void promptModificationsToExistingPlaylist(){
    cout << "1. Modify Playlist." <<endl;
    cout << "2. Delete Playlist." << endl;
    cout << "3. Return to Main Menu." <<endl;
    cout << "4. Exit Program." <<endl;
}

void promptTypesModificationSelection(){
    cout << "1. Remove Song(s)." <<endl;
    cout << "2. Add Song(s)." <<endl;
    cout << "3. Return to Playlist Options Menu." <<endl;
    cout << "4. Exit." <<endl;
}

bool modifyPlaylist(Playlist& playlist, const Playlist& all){
    promptTypesModificationSelection();
    bool exit;
    int userModType, songChoice;
    
    do{
        cout << "What would you like to do? ";
        getUserEntry(userModType);
    }while(userModType < 1 || userModType > 4);
    system("clear");

    switch(userModType){
        case 1:
            exit = deleteSongFromPlaylist(playlist);
            break;
        case 2:
            exit = addSongToPlaylist(playlist, all);
            break;
        case 3:
            exit = false;
            break;
        case 4:
            exit = true;
            break;
    }

    if(playlist.getFirstSong() != nullptr){
        writePlaylistToFile(playlist);
    }

    return exit;
}

bool addSongToPlaylist(Playlist& playlist, const Playlist& all){
    int val;

    do{
        cout << all;
        cout << all.getNumSongsLoaded() + 1 << ". Return to Playlist Options Menu." << endl;
        cout << all.getNumSongsLoaded() + 2 << ". Exit Program." << endl;
        cout << "Select a song to add: ";
        getUserEntry(val);
        if(val != all.getNumSongsLoaded() + 1 && val != all.getNumSongsLoaded() + 2){
            char userEntry;
            do{
                cout << "Add song to end of playlist (y/n)? "; //entry at 1 seg faults
                getUserEntry(userEntry);
            }while(userEntry != 'n' && userEntry != 'N' && userEntry != 'y' && userEntry != 'Y');

            if(userEntry == 'y' || userEntry == 'Y'){
                playlist+*all.getSongAtIndex(val);
            }
            else{
                int songInd;
                do{
                    system("clear");
                    cout << "========" << playlist.getName() << "========" << endl;
                    cout << playlist;
                    cout << "Which song would you like to insert before? ";
                    getUserEntry(songInd);
                }while(songInd < 1 && songInd > playlist.getNumSongsLoaded());

                playlist.addNewSong(*all.getSongAtIndex(val), songInd);
            }
        }
    }while(val != all.getNumSongsLoaded() + 1 && val != all.getNumSongsLoaded() + 2);
    system("clear");
    writePlaylistToFile(playlist);
    if(val == all.getNumSongsLoaded() + 2){
        return true; //exit program
    }

    return false;
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

bool deletePlaylist(Playlist& playlist){
    string playlistFile = playlist.getName() + ".txt";
    remove(playlistFile.c_str()); //converts file to a C-style null-terminated string and deletes file
    cout << playlist.getName() << " deleted!" << endl;
    cout << "1. Return to Main Menu." << endl;
    cout << "2. Exit Program." <<endl;

    int userEntry;

    do{
        cout << "What would you like to do? ";
        getUserEntry(userEntry);
    }while(userEntry < 1 && userEntry > 2);

    if(userEntry == 2){
        return true;
    }
    return false;
}

ostream& operator<<(ostream &out, const Song &s){
    out << s.title << endl;
    return out;
}

ostream& operator<<(ostream &out, const Playlist &p){
    if(p.firstSong == nullptr){
        cout << "No songs are currently loaded for play." << endl;
    }
    
    Song* temp = p.firstSong;
    int numDisp = 0;
    while(temp){
        cout << numDisp+1 << ". ";
        if(numDisp+1 < 10){
            cout << "  ";
        }
        else if(numDisp+1 < 100){
            cout << " ";
        }
        cout << *temp;
        temp = temp->getNextSong();
        numDisp+=1;
    }
    return out;
}
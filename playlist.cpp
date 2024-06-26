#include "playlist.h"

Playlist::Playlist(){
    firstSong = lastSong = nullptr; //nothing in queue
    numberSongsLoaded = 0;
    name = "Playlist";
}

Playlist::Playlist(Song* f, Song* l, int n, string nm){
    numberSongsLoaded = n;
    name = nm;
    if(f == nullptr){
        firstSong = lastSong = nullptr;
        return;
    }
    
    Song* temp = f;
    firstSong = lastSong = new Song;
    firstSong->setArtist(temp->getArtist());
    firstSong->setTitle(temp->getTitle());
    firstSong->setNextSong(nullptr);

    temp = temp->getNextSong();
    while(temp != nullptr){
        lastSong->setNextSong(new Song);
        lastSong = lastSong->getNextSong();
        lastSong->setArtist(temp->getArtist());
        lastSong->setTitle(temp->getTitle());
        lastSong->setNextSong(nullptr);
        temp = temp->getNextSong();
    }
}

Playlist::Playlist(const Playlist& rhs){
    numberSongsLoaded = rhs.numberSongsLoaded;
    name = rhs.name;
    if(rhs.firstSong == nullptr){
        firstSong = lastSong = nullptr;
        return;
    }
    
    Song* temp = rhs.firstSong;
    firstSong = lastSong = new Song;
    firstSong->setArtist(temp->getArtist());
    firstSong->setTitle(temp->getTitle());
    firstSong->setNextSong(nullptr);

    temp = temp->getNextSong();
    while(temp != nullptr){
        lastSong->setNextSong(new Song);
        lastSong = lastSong->getNextSong();
        lastSong->setArtist(temp->getArtist());
        lastSong->setTitle(temp->getTitle());
        lastSong->setNextSong(nullptr);
        temp = temp->getNextSong();
    }
}

Song* Playlist::getFirstSong(){
    return firstSong;
}

Song* Playlist::getLastSong(){
    return lastSong;
}

int Playlist::getNumSongsLoaded() const{
    return numberSongsLoaded;
}

string Playlist::getName() const{
    return name;
}

Song* Playlist::getSongAtIndex(int userEntry) const{
    int numNodesVisited = 0;
    Song* current = firstSong;
    while(current){ //not null
        numNodesVisited++;
        if(numNodesVisited == userEntry){
            return current;
        }
        current = current->getNextSong();
    }

    return nullptr;
}

void Playlist::setFirstSong(Song* f){
    firstSong = f;
}

void Playlist::setLastSong(Song* l){
    lastSong = l;
}

void Playlist::setNumSongsLoaded(int n){
    numberSongsLoaded = n;
}

void Playlist::setName(string nm){
    name = nm;
}

bool Playlist::isAlreadyInPlaylist(Song newSong){
    Song* temp = firstSong;
    bool found = false;
    while(temp){
        if(temp->getTitle() == newSong.getTitle()){
            found = true;
            break;
        }
        else{
            temp = temp->getNextSong();
        }
    }
    return found;
}

void Playlist::deleteSong(int entryNumber){
    if(firstSong == nullptr){
        cout << "No songs loaded; cannot delete" << endl;
    }
    if(entryNumber > numberSongsLoaded+2){
        cout << "This is an invalid option. Cannot remove song." << endl;
    }
    if(firstSong == lastSong){
        deleteSong();
    }
    else{
        Song* current = firstSong;
        Song* previous = nullptr;
        int numNodesVisited = 0;
        while(numNodesVisited < entryNumber){
            if(numNodesVisited != entryNumber-1){
                previous = current;
                current = current->getNextSong();
            }
            else{
                if(entryNumber == 1){
                    deleteSong();
                }
                else{
                    previous->setNextSong(current->getNextSong());
                    delete current;
                    current = previous->getNextSong();
                    numberSongsLoaded-=1;
                }
            }
            numNodesVisited++;
        }
    }
}

void Playlist::deleteSong(){
    if(firstSong == nullptr){
        cout << "No songs loaded; cannot delete" << endl;
    }
    if(firstSong == lastSong){
        Song* temp = firstSong;
        firstSong = lastSong = nullptr;
        delete temp;
        numberSongsLoaded -= 1;
    }
    else{
        Song* temp = firstSong;
        firstSong = firstSong->getNextSong();
        delete temp;
        numberSongsLoaded -= 1;
    }
}

void Playlist::addNewSong(const Song s){
    if(!isAlreadyInPlaylist(s)){
        Song* newSong = new Song;
        newSong->setTitle(s.getTitle());
        newSong->setArtist(s.getArtist());

        if(firstSong == nullptr){
            firstSong = lastSong = newSong;
        }
        else{
            lastSong->setNextSong(newSong);
        }
        lastSong = newSong;
        numberSongsLoaded+=1;
    }
}


void Playlist::addNewSong(Song s, int index){
    Song* temp = new Song;
    if(temp == nullptr){ //if memory allocation fails
        cout << "Unable to load playlist" << endl;
    }
    Song *current = firstSong;
    Song *previous = nullptr;
    int numNodesVisited = 0;

    if(!isAlreadyInPlaylist(s)){
        temp->setTitle(s.getTitle());
        temp->setArtist(s.getArtist());
        while(numNodesVisited < index){
            if(numNodesVisited != index-1){
                previous = current;
                current = current->getNextSong();
            }
            else{
                if(index == numberSongsLoaded || firstSong == nullptr){
                    addNewSong(s);
                }
                else if(index == 1){
                    temp->setNextSong(current);
                    firstSong = temp;
                    numberSongsLoaded++;
                }
                else{
                    temp->setNextSong(current);
                    previous->setNextSong(temp);
                    numberSongsLoaded++;
                }
            }
            numNodesVisited++;
        }
    }
}

void Playlist::displayLoadedSongs(bool displayNumbers) const{
    if(firstSong == nullptr){
        cout << "No songs are currently loaded for play." << endl;
    }
    Song *temp = firstSong;
    int numDisp = 0;
    while(temp){
        if(displayNumbers){
            cout << numDisp + 1 << ". ";
            if(numDisp + 1 < 10){
                cout << "  ";
            }
            else if(numDisp + 1 < 100){
                cout << " ";
            }
        }
        cout << temp->getTitle() << endl;
        temp = temp->getNextSong();
        numDisp+=1;
    }
}

Playlist::~Playlist(){
    Song* temp = firstSong;
    while(temp != nullptr){
        // Song* icky = firstSong;
        firstSong = firstSong->getNextSong();
        delete temp;
        temp = firstSong;
    }

    lastSong = nullptr;
    firstSong = nullptr;
}

Playlist& Playlist::operator=(const Playlist& rhs){
    numberSongsLoaded = rhs.numberSongsLoaded;
    name = rhs.name;
    if(rhs.firstSong == nullptr){
        firstSong = lastSong = nullptr;
    }
    else{
        Song* temp = rhs.firstSong;
        firstSong = lastSong = new Song;
        firstSong->setArtist(temp->getArtist());
        firstSong->setTitle(temp->getTitle());
        firstSong->setNextSong(nullptr);

        temp = temp->getNextSong();
        while(temp != nullptr){
            lastSong->setNextSong(new Song);
            lastSong = lastSong->getNextSong();
            lastSong->setArtist(temp->getArtist());
            lastSong->setTitle(temp->getTitle());
            lastSong->setNextSong(nullptr);
            temp = temp->getNextSong();
        }
    }

    return *this;
}

void Playlist::operator+(Song newSong){
    addNewSong(newSong);
}

void Playlist::operator-(int songInd){
    deleteSong(songInd);
}

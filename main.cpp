#include "helpers.h"

int main(){
    Playlist *all = new Playlist;
    all->setName("dbSmall");
    ifstream inFile("dbSmall.txt");
    readData(inFile, *all);

    int userEntry;
    bool exitProgram;

    do{
        Playlist* newest = new Playlist;
        Playlist* selectedPlaylist = new Playlist;
        system("clear");
        displayMainMenu();
        
        do{
            cout << "Make a selection" << endl;
            getUserEntry(userEntry);
        }while(userEntry < 1 && userEntry > 3);

        system("clear");

        switch(userEntry){
            case 1:
                exitProgram = manageExistingPlaylists(*all, *newest);
                if(exitProgram){
                    return 0;
                }
                break;
            case 2:
                exitProgram = createNewPlaylist(*all, *newest);
                if(exitProgram){
                    return 0;
                }
                break;
            case 3:
                exitProgram = true;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }while(userEntry != 3 && !exitProgram);

    return 0;
}
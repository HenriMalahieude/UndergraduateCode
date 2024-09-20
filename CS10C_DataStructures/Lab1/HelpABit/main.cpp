//Collaboration between Hsiangwei Hsiao (dropped the class) and Henri Malahieude
#include <iostream>
#include "Playlist.h"

using namespace std;

int PrintMenu(string title);
Playlist* playlist;

int main(){
    string title;

    cout << "Enter playlist's title:" << endl << endl;
    getline(cin, title);

    playlist = new Playlist();
    int cont = PrintMenu(title);

    while (cont == 1){
        cont = PrintMenu(title);
    }

    return 0;
}

int PrintMenu(string title){

    cout << title << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << endl;
    cout << "Choose an option:";
    cout << endl;

    string userinput;
    getline(cin, userinput);

    //Add song
    if(userinput == "a"){
        string ID;
        string name;
        string artist;
        int length;

        cout << "ADD SONG" << endl;
        cout << "Enter song's unique ID:" << endl;
        getline(cin, ID);
        cout << "Enter song's name:" << endl;
        getline(cin, name);
        cout << "Enter artist's name:" << endl;
        getline(cin, artist);
        cout << "Enter song's length (in seconds):" << endl;
        cin >> length;
        cin.ignore();

        PlaylistNode* newNode = new PlaylistNode(ID, name, artist, length);
        playlist->push_back(newNode);
        cout << endl;
    }else if (userinput == "d"){ //Remove song
        string ID;
        
        cout << "REMOVE SONG" << endl;
        cout << "Enter song's unique ID:" << endl;
        getline(cin, ID);

        //remove function
        PlaylistNode* remove_node = playlist->remove(ID);
        if (remove_node != 0 && remove_node != nullptr){
            cout << '"' << remove_node->GetSongName() << '"' << " removed." << endl;
            
            delete remove_node;
            remove_node = nullptr;
        }else{
            cout << "Song with unique ID " << ID << " not found!" << endl;
        }
        cout << endl;
    }else if (userinput == "c"){ //Change position of song
        int cur_pos;
        int new_pos;

        cout << "CHANGE POSITION OF SONG" << endl;
        cout << "Enter song's current position:" << endl;
        cin >> cur_pos;
        cout << "Enter new position for song:" << endl;
        cin >> new_pos;

        cin.clear();
        cin.ignore(1);

         if(new_pos < 1){
            new_pos = 1;
        }
        
        PlaylistNode *song = playlist->changePos(cur_pos, new_pos);

        if (song != nullptr){
            cout << '"' << song->GetSongName() << '"' << " moved to position " << new_pos << endl << endl;
        }else{
            cout << "Could not locate song" << endl;
        }
    }else if (userinput == "s"){ //Output songs by specific artist
        string artist = "";
        
        cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
        cout << "Enter artist's name:" << endl << endl;
        getline(cin, artist);

        playlist->printByArtist(artist);
    }else if (userinput == "t"){ //Output total time of playlist (in seconds)
        cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
        cout << "Total time: " << playlist->totalTimeSeconds() << " seconds" << endl;
        cout << endl;
    }else if (userinput == "o"){ //Output full playlist
        playlist->print(title);
    }else if (userinput == "q"){ //Quit
        return 0;
    }else{ //If user input invalid option
        cout << "Invalid selection." << endl;
    }

    return 1;
}
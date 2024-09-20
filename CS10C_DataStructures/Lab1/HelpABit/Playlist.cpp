//Created by Henri Malahieude
#include <iostream>
#include "Playlist.h"

PlaylistNode::PlaylistNode(){
    uniqueId = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = 0;
}

PlaylistNode::PlaylistNode(string id, string name, string artist, int length){
    uniqueId = id;
    songName = name;
    artistName = artist;
    songLength = length;
    nextNodePtr = 0;
}

void PlaylistNode::SetNext(PlaylistNode* next){
    nextNodePtr = next;
}

void PlaylistNode::InsertAfter(PlaylistNode* after){ //this
    PlaylistNode* temp = this->nextNodePtr;
    this->nextNodePtr = after;
    after->SetNext(temp); //this -> after -> original next node
}

string PlaylistNode::GetID() const{
    return uniqueId;
}

string PlaylistNode::GetSongName() const{
    return songName;
}

string PlaylistNode::GetArtistName() const{
    return artistName;
}

int PlaylistNode::GetSongLength() const{
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() const{
    return nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() const{
    cout << "Unique ID: " << uniqueId << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}


//Create another class function for linked list
Playlist::Playlist() : head(nullptr), tail(nullptr){ }

//Add song helper function
void Playlist::push_back(PlaylistNode* add_node){
    if (head == nullptr){
        head = add_node;
        tail = add_node;
    }
    else{
        tail->SetNext(add_node);
        tail = add_node;
    }
}

//Remove song helper function and the goal is to find the remove_node
PlaylistNode* Playlist::remove(string ID){
    PlaylistNode* prevPtr = nullptr;
    PlaylistNode* currPtr = head;

    //Check if the node has the same ID
    while (currPtr!=nullptr && currPtr->GetID() != ID){
        prevPtr = currPtr;
        currPtr = currPtr->GetNext();
    }

    if (currPtr != nullptr){
        if (prevPtr != nullptr){
            prevPtr->SetNext(currPtr->GetNext()); //pre->next = cur->next
        }
        else{
            head = currPtr->GetNext();
        }

        if (currPtr->GetNext() == nullptr){
            tail = prevPtr;
        }

        return currPtr;
    }
    else{
        return nullptr;
    }
}


//Change position helper function
PlaylistNode* Playlist::changePos(int cur_pos, int new_pos){
    int pos = 1;

    PlaylistNode *prev = nullptr;
    PlaylistNode *cur = head;
    while (cur != nullptr && pos < cur_pos){ //Get Song We want
        prev = cur;
        cur = cur->GetNext();
        pos++;
    }

    if (cur == nullptr){
        return nullptr;
    }else if (prev == nullptr){
        head = head->GetNext(); //Splice it (special case)
    }else{
        prev->SetNext(cur->GetNext()); //Splice it
    }

    pos = 1;
    PlaylistNode *befr = head;
    while (befr != nullptr && pos < (new_pos-1)){ //Get the song we are inserting it after
        befr = befr->GetNext();
        pos++;
    }

    if (new_pos > 1){
        cur->SetNext(befr->GetNext()); //chosen song points to before's song
        befr->SetNext(cur); //before points to chosen
    }else{
        head = cur;
        cur->SetNext(befr);
    }
    

    return cur;
}

void Playlist::print(string title) const
{
    cout << title << " - OUTPUT FULL PLAYLIST" << endl;

    if (head != nullptr){
        PlaylistNode* cur = head;
        int pos = 1;

        while (cur != nullptr){
            cout << pos++ << "." << endl;
            cur->PrintPlaylistNode();
            cout << endl;

            cur = cur->GetNext();
        }
    }else{
        cout << "Playlist is empty" << endl << endl;
    }
}

void Playlist::printByArtist(string artist) const
{
    PlaylistNode* cur = head;
    int pos = 1;

    while (cur != nullptr){
        if (cur->GetArtistName() == artist){
            cout << pos << "." << endl;
            cur->PrintPlaylistNode();
            cout << endl;
        }
        cur = cur->GetNext();
        pos++;
    }
}


//Output total time of playlist helper function
int Playlist::totalTimeSeconds() const{
    int total = 0;
    PlaylistNode* node = head;
    while (node != nullptr){
        total += node->GetSongLength();
        node = node->GetNext();
    }
    return total;
}
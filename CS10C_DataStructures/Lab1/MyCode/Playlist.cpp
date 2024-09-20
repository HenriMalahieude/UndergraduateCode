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

PlaylistNode::PlaylistNode(string id, string name, string artist, int length, PlaylistNode* next){
    uniqueId = id;
    songName = name;
    artistName = artist;
    songLength = length;
    nextNodePtr = next;
}

void PlaylistNode::SetNext(PlaylistNode next){
    this->nextNodePtr = &next;
}

void PlaylistNode::InsertAfter(PlaylistNode after){;
    after.SetNext(*this);
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

PlaylistNode PlaylistNode::GetNext() const{
    return *nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() const{
    cout << "Unique ID: " << uniqueId << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}
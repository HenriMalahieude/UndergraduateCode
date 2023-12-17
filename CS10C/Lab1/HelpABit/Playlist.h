//Created by Henri Malahieude
#include <string>

#ifndef PLAYLISTN_H
#define PLAYLISTN_H

using namespace std;

class PlaylistNode {
    public:
        PlaylistNode();
        PlaylistNode(string, string, string, int);

        void InsertAfter(PlaylistNode*);
        void SetNext(PlaylistNode*);
        
        string GetID() const;
        string GetSongName() const;
        string GetArtistName() const;
        int GetSongLength() const;
        PlaylistNode* GetNext() const;

        void PrintPlaylistNode() const;
    private:
        string uniqueId;
        string songName;
        string artistName;
        int songLength;
        PlaylistNode* nextNodePtr;
};

//Created by Hsiangwei Hsiao
class Playlist{
    public:
        Playlist();

        void push_back(PlaylistNode*);
        PlaylistNode* changePos(int, int);
        PlaylistNode* remove(string);

        void print(string title) const;
        void printByArtist(string) const;
        int totalTimeSeconds() const;
    private:
        PlaylistNode* head;
        PlaylistNode* tail;
};

#endif
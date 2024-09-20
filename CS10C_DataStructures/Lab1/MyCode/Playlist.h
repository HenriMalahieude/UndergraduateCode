//Created by Henri Malahieude
#include <string>

#ifndef PLAYLISTN_H
#define PLAYLISTN_H

using namespace std;

class PlaylistNode {
    public:
        PlaylistNode();
        PlaylistNode(string, string, string, int, PlaylistNode*);

        void InsertAfter(PlaylistNode);
        void SetNext(PlaylistNode);
        
        string GetID() const;
        string GetSongName() const;
        string GetArtistName() const;
        int GetSongLength() const;
        PlaylistNode GetNext() const;

        void PrintPlaylistNode() const;
    private:
        string uniqueId;
        string songName;
        string artistName;
        int songLength;
        PlaylistNode* nextNodePtr;
};

#endif
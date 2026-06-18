#pragma once
#include <string>
#include <vector>

inline int goalRow(char tile){ return (tile - '0') / 3; }
inline int goalCol(char tile){ return (tile - '0') % 3; }

inline int h1_hamming(const std::string& s){
    int count = 0;
    for(int i = 0; i < 9; i++){
        if(s[i] != '0' && s[i] != "012345678"[i])
            count++;
    }
    return count;
}

inline int h2_manhattan(const std::string& s){
    int dist = 0;
    for(int i = 0; i < 9; i++){
        if(s[i] == '0') continue;
        int row = i / 3, col = i % 3;
        dist += abs(row - goalRow(s[i])) + abs(col - goalCol(s[i]));
    }
    return dist;
}

inline int conflictRow(const std::string& s){
    int conflicts = 0;
    for(int row = 0; row < 3; row++){
        std::vector<int> tiles;
        for(int col = 0; col < 3; col++){
            char tile = s[row * 3 + col];
            if(tile == '0') continue;
            if(goalRow(tile) == row)
                tiles.push_back(tile - '0');
        }
        for(int i = 0; i < (int)tiles.size(); i++)
            for(int j = i + 1; j < (int)tiles.size(); j++)
                if(tiles[i] > tiles[j])
                    conflicts++;
    }
    return conflicts;
}

inline int conflictCol(const std::string& s){
    int conflicts = 0;
    for(int col = 0; col < 3; col++){
        std::vector<int> tiles;
        for(int row = 0; row < 3; row++){
            char tile = s[row * 3 + col];
            if(tile == '0') continue;
            if(goalCol(tile) == col)
                tiles.push_back(tile - '0');
        }
        for(int i = 0; i < (int)tiles.size(); i++)
            for(int j = i + 1; j < (int)tiles.size(); j++)
                if(tiles[i] > tiles[j])
                    conflicts++;
    }
    return conflicts;
}

inline int h3_linearConflict(const std::string& s){
    return h2_manhattan(s)
         + 2 * conflictRow(s)
         + 2 * conflictCol(s);
}
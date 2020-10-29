#pragma once

#include <mpegfile.h>
#include <array>
#include <string>
#include <unistd.h>

std::string* strsplit(std::string str, char del, int *len);

bool compareArtist(std::string i, std::string j);
bool compareTitle(std::string i, std::string j);
bool compareAlbum(std::string i, std::string j);
bool compareGenre(std::string i, std::string j);

class MP3File {
public:
    MP3File(std::string file);
    ~MP3File();

    std::string getName();
    std::string getPath();

    std::array <std::string, 4> readTags();
    int writeTags(std::array <std::string, 4> tags);
    int fileErrors(int mode);

private:
    std::string m_name;
    std::string m_path;
};

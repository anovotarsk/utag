#include <tags.h>

/*
0 - Artist
1 - Title
2 - Album
3 - Genre
*/

int fileErrors(std::string mp3file) {
    int error = (access(mp3file.c_str(), 2)) ? errno : 0;

    errno = 0;
    return error;
}

std::array <std::string, 4> readTags(std::string mp3file) {
    std::array <std::string, 4> tags;
    TagLib::MPEG::File file(mp3file.c_str(), false);

    tags[0] = file.tag()->artist().toCString();
    tags[1] = file.tag()->title().toCString();
    tags[2] = file.tag()->album().toCString();
    tags[3] = file.tag()->genre().toCString();

    errno = 0;

    return tags;
}

int writeTags(std::string mp3file, std::array <std::string, 4> tags) {
    int error = (access(mp3file.c_str(), 2)) ? errno : 0;

    if (error == 0) {
        TagLib::MPEG::File file(mp3file.c_str(), false);

        if (!file.isWritable(mp3file.c_str()))
            return 13;
        file.tag()->setArtist(tags[0]);
        file.tag()->setTitle(tags[1]);
        file.tag()->setAlbum(tags[2]);
        file.tag()->setGenre(tags[3]);

        file.save();
        error = errno;
    }
    errno = 0;
    return error;
}

#include <tags.h>

/*
0 - Artist
1 - Title
2 - Album
3 - Genre
*/

MP3File::MP3File(std::string file) : m_path(file) {
    int len;
    std::string *s = strsplit(file, '/', &len);

    m_name = s[len - 1];
    delete [] s;
}

MP3File::~MP3File() {
}

std::string MP3File::getName() {
    return m_name;
}

std::string MP3File::getPath() {
    return m_path;
}

int MP3File::fileErrors() {
    int error = (access(m_path.c_str(), 2)) ? errno : 0;
    errno = 0;
    return error;
}

std::array <std::string, 4> MP3File::readTags() {
    std::array <std::string, 4> tags;
    TagLib::MPEG::File file(m_path.c_str(), false);

    tags[0] = file.tag()->artist().toCString();
    tags[1] = file.tag()->title().toCString();
    tags[2] = file.tag()->album().toCString();
    tags[3] = file.tag()->genre().toCString();

    errno = 0;

    return tags;
}

int MP3File::writeTags(std::array <std::string, 4> tags) {
    int error = (access(m_path.c_str(), 2)) ? errno : 0;

    if (error == 0) {
        TagLib::MPEG::File file(m_path.c_str(), false);

        if (!file.isWritable(m_path.c_str()))
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

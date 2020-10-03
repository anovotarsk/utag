#include <tags.h>

std::array <std::string, 4> readTags(std::string mp3file) {
    std::array <std::string, 4> tags;
    TagLib::MPEG::File file(mp3file.c_str(), false);


    tags[0] = file.tag()->artist().toCString();
    tags[1] = file.tag()->title().toCString();
    tags[2] = file.tag()->album().toCString();
    tags[3] = file.tag()->genre().toCString();

    return tags;
}

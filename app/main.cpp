#include <iostream>
#include <tag.h>
#include <mpegfile.h>
#include <id3v1tag.h>
#include <textidentificationframe.h>
#include <tstring.h>

int main(int argc, char *argv[]) {
    TagLib::MPEG::File file(argv[1]);
    file.tag()->setArtist("LOL");
    file.save();
}

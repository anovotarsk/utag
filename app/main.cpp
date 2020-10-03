#include <iostream>
#include <tags.h>

int main(int argc, char *argv[]) {
    auto tags = readTags(argv[1]);

    std::cout << "Artist - " << tags[0] << std::endl;
    std::cout << "Title  - " << tags[1] << std::endl;
    std::cout << "Album  - " << tags[2] << std::endl;
    std::cout << "Gentre - " << tags[3] << std::endl;
    std::cout << "\nErrno - " << errno << std::endl;
    std::cout << strerror(errno) << std::endl;

    errno = 0;
    TagLib::MPEG::File file(argv[1], false);
    file.tag()->setArtist("Artist");
    std::cout << "\nErrno - " << errno << std::endl;
    std::cout << "\nErrno - " << errno << std::endl;
    std::cout << strerror(errno) << std::endl;

    file.save();
    std::cout << "\nErrno - " << errno << std::endl;
    std::cout << strerror(errno) << std::endl;
}

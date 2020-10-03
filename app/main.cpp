#include <iostream>
#include <tags.h>

int main(int argc, char *argv[]) {
    auto tags = readTags(argv[1]);

    std::cout << "Artist - " << tags[0] << std::endl;
    std::cout << "Title  - " << tags[1] << std::endl;
    std::cout << "Album  - " << tags[2] << std::endl;
    std::cout << "Genre  - " << tags[3] << std::endl;

    std::cout << std::endl << "Errno - " << errno << std::endl;
    std::cout << strerror(errno) << std::endl;

    std::array <std::string, 4> set {"Artist", "Title", "Album", "Genre"};

    int result = writeTags(argv[1], set);
    std::cout << std::endl << "Error - " << result << std::endl;
    std::cout << strerror(result) << std::endl;
}

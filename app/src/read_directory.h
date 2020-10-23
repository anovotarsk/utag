#ifndef READ_DIRECTORY_H
#define READ_DIRECTORY_H

#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <utility>
#include <algorithm>


std::vector<std::pair<std::string, std::string>> read_directory(const char *dirr);
bool is_MP3(std::string file);

#endif //READ_DIRECTORY_H

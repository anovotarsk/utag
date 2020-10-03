#pragma once

#include <mpegfile.h>
#include <array>
#include <string>
#include <unistd.h>

std::array <std::string, 4> readTags(std::string mp3file);
int writeTags(std::string mp3file, std::array <std::string, 4> tags);
int fileErrors(std::string mp3file);

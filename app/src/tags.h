#pragma once

#include <mpegfile.h>
#include <array>
#include <string>

std::array <std::string, 4> readTags(std::string mp3file);

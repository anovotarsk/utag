#include "read_directory.h"

std::vector<std::pair<std::string, std::string>> recursive_open(std::vector<std::pair<std::string, std::string>>  base, const char *dirr, std::vector<std::string> *buff) {
    std::vector<std::pair<std::string, std::string>>  files = base;
    std::string str_dirr(dirr);
    int counter = 1;
    const char * char_path;
    std::string tmp_name;
    std::pair<std::string, std::string> path_and_name;
    struct dirent *tmp;
    DIR *dir;
    DIR *tmp_dir;

    dir = opendir(dirr);
    if (dir != NULL) {
        while ((tmp = readdir(dir)) != NULL) {
            tmp_name = tmp->d_name;
            while (std::find(buff->begin(), buff->end(), tmp_name) != buff->end()) {
                tmp_name = tmp->d_name + ("(" + std::to_string(counter) + ")");
                counter++;
            }
            path_and_name = std::make_pair((str_dirr + '/' + tmp->d_name), tmp_name);
            char_path = path_and_name.first.c_str();
            tmp_dir = opendir(char_path);
            if (tmp_dir != NULL) {
                if (strcmp(tmp->d_name, ".") != 0 && strcmp(tmp->d_name, "..") != 0)
                    files = recursive_open(files, char_path, buff);
                closedir(tmp_dir);
            }
            else if (is_MP3(tmp->d_name)) {
                    buff->push_back(tmp_name);
                    files.push_back(path_and_name);
            }
            
        }
    }
    closedir(dir);
    return files;
}

std::vector<std::pair<std::string, std::string>>  read_directory(const char *dirr) {
    std::vector<std::pair<std::string, std::string>> files;
    std::vector<std::string> buff;
    DIR *dir;

    dir = opendir(dirr);
    if (!dir) {
        std::cerr << strerror(errno);
        exit(1);
    }
    closedir(dir);
    return recursive_open(files, dirr, &buff);;
}

bool is_MP3(std::string file) {
    int len = file.size();
    if (len - file.find("mp3") == 3) {
        return true;
    }
    return false;
}

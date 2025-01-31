#pragma once

#include <sys/stat.h>
#include <dirent.h>

inline bool file_exists(const std::string& fname) {
    struct stat buffer{};
    return (stat (fname.c_str(), &buffer) == 0);
}

inline bool is_dir(char* p) {
    DIR* filetest = opendir(p);
    if (filetest == nullptr) {
        return false;
    } else {
        closedir(filetest);
        return true;
    }
}